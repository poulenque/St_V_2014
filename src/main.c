#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <GL/glew.h>
#include "random.h"
#include "constants.h"

#include "game.h"
#include "camera.h"
#include "string3d.h"

int SCREEN_WIDTH=800;
int SCREEN_HEIGHT=600;
int SCREEN_BPP=32;
int STEREOSCOPY=0;


//=====================================================
// "💗💙💚💜💛💘♡ 💓♥💖💔💕❣ ❤💝💞💟❥"
//=====================================================
#define INIT_ULTRA_NECESSARY_TITLE_ANIMATION() \
	int TITLE_frame=0;\
	int TITLE_time=0;\
	const char* TITLE_anim[4];\
	TITLE_anim[0] ="   /   |   \\   -   /   |💗|   \\   -   /   |   \\   ";\
	TITLE_anim[1] ="  |   \\   -   /   |   \\ ♡ /   |   \\   -   /   |  ";\
	TITLE_anim[2] =" \\   -   /   |   \\   -  💗  -   /   |   \\   -   / ";\
	TITLE_anim[3] ="-   /   |   \\   -   /   ♡   \\   -   /   |   \\   -";

#define ULTRA_NECESSARY_TITLE_ANIMATION() \
	TITLE_time+=dt;\
	if(TITLE_time>100){\
		TITLE_frame++;\
		TITLE_time=0;\
		if(TITLE_frame==4){\
			TITLE_frame=0;\
		}\
	}\
	SDL_WM_SetCaption( TITLE_anim[TITLE_frame], NULL )
//=====================================================
//=====================================================

//because absent from stdlib.h for I don't know reason...
int putenv(const char * string);

void printCenter(int n,const char *s){
	printf("///%*s%*s\\\\\\\n",n/2+(int)strlen(s)/2,s,n/2-(int)strlen(s)/2,"");
}

//============================
//ultra smart arg parsing
//============================
int parseArgs(int argc, char *argv[]){
	int ret=0;
	int i=0;
	while(--argc){
		i++;
		if(!strcmp(argv[i],"--help")||!strcmp(argv[i],"-h")){
			printf("-h or --help       : help (prints this message)\n");
			printf("-v or --version    : version\n");
			printf("-d or --duck       : duck ?\n");
			printf("-c or --credits    : credits\n");
			printf("-s or --stereo     : stereoscopic mode (warning: really slow !)\n");
			printf("-r or --resolution : resolution eg 1024 768\n");
			printf("   example : --resolution 1024 768\n");
			printf("wow that was helpful!\n");
			ret=1;
		}
		else if(!strcmp(argv[i],"--stereo")||!strcmp(argv[i],"-s")){
			printf("STEREOSCOPY !!!\n");
			printf("dividing FPS per 2 !!!\n");
			STEREOSCOPY=1;
		}
		else if(!strcmp(argv[i],"--resolution")||!strcmp(argv[i],"-r")){
			//missing argument X and Y
			if(!--argc){
				printf("Must specify x and y resolution : example \'-r 1024 768\'\n");
				ret=1;
				break;
			}
			i++;
			// printf("%s\n",argv[i]);
			SCREEN_WIDTH=atoi(argv[i]);
			//missing argument Y
			if(!--argc){
				printf("Must specify x AND y resolution : example \'-r 1024 768\'\n");
				ret=1;
				break;
			}
			i++;
			// printf("%s\n",argv[i]);
			SCREEN_HEIGHT=atoi(argv[i]);
			printf("RESOLUTION is set to : %ix%i !!!\n",SCREEN_WIDTH,SCREEN_HEIGHT);
		}
		else if(!strcmp(argv[i],"--version")||!strcmp(argv[i],"-v")){
			printf("it's over 9000.0.1\n");
			ret=1;
		}
		else if(!strcmp(argv[i],"--duck")||!strcmp(argv[i],"-d")){
			printf("              ____           \n");
			printf("             /    \\          \n");
			printf("             | O o|____      \n");
			printf("             |     ====)     \n");
			printf("    \\        |    |          \n");
			printf("   \\ \\______/     |          \n");
			printf("   \\ \\___         |          \n");
			printf("      \\__        /           \n");
			printf("       \\________/            \n");
			printf("          |   |              \n");
			printf("          |_  |_             \n");
			ret=1;
		}
		else if(!strcmp(argv[i],"--credits")||!strcmp(argv[i],"-c")){
			printCenter(40,"__________");
			printCenter(40,"");
			printCenter(40,"CODE");
			printCenter(40,"");
			printCenter(40,"Laurent Rohrbasser");
			printCenter(40,"");
			printCenter(40,"__________");
			printCenter(40,"");
			printCenter(40,"GRAPHIC");
			printCenter(40,"");
			printCenter(40,"Laurent Rohrbasser");
			printCenter(40,"");
			printCenter(40,"__________");
			printCenter(40,"");
			printCenter(40,"MUSIC");
			printCenter(40,"");
			printCenter(40,"GOTO80");
			printCenter(40,"");
			printCenter(40,"__________");

			ret=1;
		}
		else{
			printf("wut ?? I didn't get that... try --help or -h instead...\n");
			return 1;
		}
	}
	return ret;
}


int main(int argc, char *argv[]) {
	int parseReturn= parseArgs(argc, argv);
	if(parseReturn==1) return 1;

	//RANDOM INIT
	random_init();

	//SDL INITIALIZATION
	putenv("SDL_VIDEO_CENTERED=1");
	SDL_Init( SDL_INIT_EVERYTHING );
	// SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL | SDL_FULLSCREEN  );
	SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL  );
	glewInit ();
	SDL_EnableUNICODE( SDL_TRUE );
	SDL_WM_GrabInput(SDL_GRAB_ON);


	int mouse_x = 0, mouse_y = 0;
	// int mouse_dx = 0, mouse_dy = 0;
	int quit=0;
	Uint8 *keystate;

	int t_before=SDL_GetTicks();
	int dt=0;


	INIT_ULTRA_NECESSARY_TITLE_ANIMATION();

	SDL_WarpMouse(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
	//well sometimes the mouse does not move immediatly
	usleep(10000);

	SDL_Event event;
	while( SDL_PollEvent( &event ) );
	SDL_ShowCursor( SDL_DISABLE );

	int MOUSE_ON=1;

	unsigned int W_KEY=SDLK_w;
	unsigned int A_KEY=SDLK_a;
	unsigned int S_KEY=SDLK_s;
	unsigned int D_KEY=SDLK_d;

	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	while(1){
		keystate = SDL_GetKeyState(NULL);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		dt=SDL_GetTicks()-t_before;
		t_before = SDL_GetTicks();
		ULTRA_NECESSARY_TITLE_ANIMATION();

		while( SDL_PollEvent( &event ) );

		glClear(GL_DEPTH_BUFFER_BIT);

		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluOrtho2D(-1, 1, -1, 1);

		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();

		glColor4d(0,1,0,.4+.2*sin(SDL_GetTicks()*0.01)+random(0,0.5));
		// glDisable(GL_DEPTH_TEST);
		glPushAttrib(GL_DEPTH_TEST);
		glDisable(GL_DEPTH_TEST);

		glBegin( GL_QUADS );
			glVertex2f(-random(.7,.1), -random(.7,.1) );
			glVertex2f( random(.7,.1), -random(.7,.1) );
			glVertex2f( random(.7,.1),  random(.7,.1) );
			glVertex2f(-random(.7,.1),  random(.7,.1) );

			glVertex2f(-random(.75,.1), -random(.75,.1) );
			glVertex2f( random(.75,.1), -random(.75,.1) );
			glVertex2f( random(.75,.1),  random(.75,.1) );
			glVertex2f(-random(.75,.1),  random(.75,.1) );

			glVertex2f(-random(.8,.1), -random(.8,.1) );
			glVertex2f( random(.8,.1), -random(.8,.1) );
			glVertex2f( random(.8,.1),  random(.8,.1) );
			glVertex2f(-random(.8,.1),  random(.8,.1) );
		glEnd();
		String3d*str=new_string3d();
		str->size=.1;

		// string3d_setTxt(str,"===PRESS===\n=== q to===\n===QUIT !==");
		string3d_setTxt(str,"===AZERTY==\n==KEYBOARD=\n===PRESS===\n===  F  ===");

		glLineWidth(20.0);

		str->dist=.6;
		glTranslated(0,0.05,0);
		glPushMatrix();
			glTranslated(0,.5,str->dist*1.2);
			glRotated(-90+30*sin(SDL_GetTicks()*0.003),1,0,0);
			glRotated(180,0,0,1);
			glScaled(1,.5,1);
			glColor4d(1,1,1,1);
			string3d_draw(str);
			string3d_draw(str);
			string3d_draw(str);
		glPopMatrix();

		string3d_setTxt(str,"===========");

		glPushMatrix();
			glTranslated(0,-.06,str->dist*1.2);
			glRotated(-100,1,0,0);
			glRotated(180,0,0,1);
			glScaled(1,.5,1);
			glColor4d(0,.3,0,.5);
			string3d_draw(str);
			string3d_draw(str);
			string3d_draw(str);
		glPopMatrix();

		string3d_setTxt(str,"===QWERTY==\n==KEYBOARD=\n===PRESS===\n===SPACE===");

		glPushMatrix();
			glTranslated(0,-.3,str->dist*1.2);
			glRotated(-90-30*sin(SDL_GetTicks()*0.003),1,0,0);
			glRotated(180,0,0,1);
			glScaled(1,.5,1);
			glColor4d(0,0,0,1);
			string3d_draw(str);
			string3d_draw(str);
			string3d_draw(str);
		glPopMatrix();


		glPopAttrib();
		free(str);

		glFlush();
		SDL_GL_SwapBuffers();

		if(keystate[SDLK_SPACE]){
			break;
		}
		if(keystate[SDLK_f]){
			W_KEY=SDLK_z;
			A_KEY=SDLK_q;
			S_KEY=SDLK_s;
			D_KEY=SDLK_d;
			break;
		}
		if(keystate[SDLK_ESCAPE]){
			return 0;
		}

	}














	Camera* player = new_Camera();
	Game* game = initGame(player);
	player->game=game;
	game->stereo=STEREOSCOPY;

	Uint32 mouse_buttons;
	int jump_count=0;
	int jump_max=3;
	while(!quit){
		dt=SDL_GetTicks()-t_before;
		t_before = SDL_GetTicks();
		keystate = SDL_GetKeyState(NULL);
		mouse_buttons=SDL_GetMouseState( &mouse_x, &mouse_y );
		// mouse_dx=mouse_x-SCREEN_WIDTH/2;
		// mouse_dy=mouse_y-SCREEN_HEIGHT/2;


		//EventHandler
		//========================
		while( SDL_PollEvent( &event ) )
		{
			switch(event.type){
				case SDL_QUIT:
					quit = 1;
					break;
				case SDL_KEYDOWN:
					if(event.key.keysym.sym ==SDLK_ESCAPE){
						// quit=1;
						MOUSE_ON=!MOUSE_ON;
						if(MOUSE_ON){
							SDL_WM_GrabInput(SDL_GRAB_ON);
							SDL_ShowCursor( SDL_DISABLE );
							game_pause(game,0);
						}else{
							SDL_WM_GrabInput(SDL_GRAB_OFF);
							SDL_ShowCursor( SDL_ENABLE );
							game_pause(game,1);
						}
					}
					else if(event.key.keysym.sym == SDLK_RETURN){
						STEREOSCOPY=!STEREOSCOPY;
						game->stereo=STEREOSCOPY;
					}
					else if(event.key.keysym.sym ==SDLK_SPACE){
						// if(mouse_buttons&SDL_BUTTON(1)||mouse_buttons&SDL_BUTTON(3)){
						// }else{
							if(game->player->z==0){
								jump_count=0;
							}
							jump_count++;
							if(jump_count<=jump_max){
								player->dz=-300;
							}
						// }
					}
					else if(event.key.keysym.sym==SDLK_F12){
						game->color_debug=!game->color_debug;
					}
					else if(event.key.keysym.sym==SDLK_F11){
						game->sorting=!game->sorting;
						if(game->sorting){
							printf("SORTING!\n");
						}else{
							printf("NOT SORTING!\n");
						}
					}
					else if(event.key.keysym.sym==SDLK_F1){
						game->weapon=0;
					}
					else if(event.key.keysym.sym==SDLK_F2){
						if(game->weapon==1){
							game->weapon=4;
						}else{
							game->weapon=1;
						}
					}
					else if(event.key.keysym.sym==SDLK_F3){
						game->weapon=2;
					}
					else if(event.key.keysym.sym==SDLK_F4){
						game->weapon=3;
					}
					else if(event.key.keysym.sym==SDLK_F5){
						clear_arrow(game);
					}

					break;
				case SDL_MOUSEMOTION:
					if(MOUSE_ON){
						if(mouse_buttons&SDL_BUTTON(1)||mouse_buttons&SDL_BUTTON(3)||keystate[SDLK_LCTRL]||keystate[SDLK_LALT]){
							camera_rotate(player,-.5*event.motion.yrel,.5*event.motion.xrel,0);
						}else{
							camera_rotate(player,-2*event.motion.yrel,2*event.motion.xrel,0);
						}
					}
					// camera_rotate(player,0,2*event.motion.xrel,0);
					break;
			}
		}

		double speed=1000;
		if(MOUSE_ON){
			game->fire(game,0);
			game->trigger(game,0);
			if(mouse_buttons&SDL_BUTTON(1)||keystate[SDLK_LCTRL]){
				game->trigger(game,1);
				game->fire(game,1);
				//walk slowly if on ground
				if(game->player->z==0)
					speed=400;
			}
			if(mouse_buttons&SDL_BUTTON(3)||keystate[SDLK_LALT]){
				game->trigger(game,1);
				//walk slowly if on ground
				if(game->player->z==0)
					speed=400;
			}

			if (keystate[A_KEY]){
				camera_move_acc(player,0,-speed,0);
			}
			if (keystate[D_KEY]){
				camera_move_acc(player,0,speed,0);
			}
			// if (keystate[SDLK_w] || keystate[SDLK_UP]){
			// 	camera_move_acc(player,-speed,0,0);			
			// }
			// if (keystate[SDLK_s] || keystate[SDLK_DOWN]){
			// 	camera_move_acc(player,speed,0,0);
			// }
			if (keystate[W_KEY]){
				camera_move_acc(player,-speed,0,0);			
			}
			if (keystate[S_KEY]){
				camera_move_acc(player,speed,0,0);
			}
			// if (keystate[SDLK_e]){
			// 	camera_move_acc(player,0,0,-speed);
			// }
			// if (keystate[SDLK_q]){
			// 	camera_move_acc(player,0,0,speed);
			// }

			// if(keystate[SDLK_LALT]){
			// 	if (keystate[SDLK_LEFT]){
			// 		camera_move_acc(player,0,-speed,0);
			// 	}
			// 	if (keystate[SDLK_RIGHT]){
			// 		camera_move_acc(player,0,speed,0);
			// 	}
			// }
			// else{
				speed=5000;
				if(keystate[SDLK_LCTRL]||keystate[SDLK_LALT])
					speed=1000;
				if (keystate[SDLK_LEFT]){
					camera_rotate_acc(player,0,-speed,0);
				}
				if (keystate[SDLK_RIGHT]){
					camera_rotate_acc(player,0,speed,0);
				}
			// }
			if (keystate[SDLK_UP]){
				camera_rotate_acc(player,speed,0,0);
			}
			if (keystate[SDLK_DOWN]){
				camera_rotate_acc(player,-speed,0,0);
			}
		}


		ULTRA_NECESSARY_TITLE_ANIMATION();

		if(MOUSE_ON){
			game_update(game,dt);
		}

			if(STEREOSCOPY)
				camera_render_stereo(player);
			else
				camera_render(player);


		if(!MOUSE_ON){

			// gluPerspective(c->mFOV, c->mAspectRatio, c->mNearClippingDistance, c->mFarClippingDistance);

			glClear(GL_DEPTH_BUFFER_BIT);

			glMatrixMode( GL_PROJECTION );
			glLoadIdentity();
			gluOrtho2D(-1, 1, -1, 1);

			glMatrixMode( GL_MODELVIEW );
			glLoadIdentity();

			glColor4d(1,0,0,.4+.2*sin(SDL_GetTicks()*0.01)+random(0,0.5));
			// glDisable(GL_DEPTH_TEST);
			glPushAttrib(GL_DEPTH_TEST);
			glDisable(GL_DEPTH_TEST);

			glBegin( GL_QUADS );
				glVertex2f(-random(.7,.1), -random(.7,.1) );
				glVertex2f( random(.7,.1), -random(.7,.1) );
				glVertex2f( random(.7,.1),  random(.7,.1) );
				glVertex2f(-random(.7,.1),  random(.7,.1) );

				glVertex2f(-random(.75,.1), -random(.75,.1) );
				glVertex2f( random(.75,.1), -random(.75,.1) );
				glVertex2f( random(.75,.1),  random(.75,.1) );
				glVertex2f(-random(.75,.1),  random(.75,.1) );

				glVertex2f(-random(.8,.1), -random(.8,.1) );
				glVertex2f( random(.8,.1), -random(.8,.1) );
				glVertex2f( random(.8,.1),  random(.8,.1) );
				glVertex2f(-random(.8,.1),  random(.8,.1) );
			glEnd();
			String3d*str=new_string3d();
			str->size=.1;

			// string3d_setTxt(str,"===PRESS===\n=== q to===\n===QUIT !==");
			string3d_setTxt(str,"===PRESS===\n=== q to===\n===QUIT !==");

			glLineWidth(20.0);

			str->dist=.6;
			glTranslated(0,0.05,0);
			glPushMatrix();
				glTranslated(0,.4,str->dist*1.2);
				glRotated(-90+30*sin(SDL_GetTicks()*0.003),1,0,0);
				glRotated(180,0,0,1);
				glScaled(1,.5,1);
				glColor4d(1,1,1,1);
				string3d_draw(str);
				string3d_draw(str);
				string3d_draw(str);
			glPopMatrix();

			string3d_setTxt(str,"===========");

			glPushMatrix();
				glTranslated(0,-.1,str->dist*1.2);
				glRotated(-100,1,0,0);
				glRotated(180,0,0,1);
				glScaled(1,.5,1);
				glColor4d(.5,.5,.5,1);
				string3d_draw(str);
				string3d_draw(str);
				string3d_draw(str);
			glPopMatrix();

			string3d_setTxt(str,"===PRESS===\n===ESC to==\n=CONTINUE!=");

			glPushMatrix();
				glTranslated(0,-.4,str->dist*1.2);
				glRotated(-90-30*sin(SDL_GetTicks()*0.003),1,0,0);
				glRotated(180,0,0,1);
				glScaled(1,.5,1);
				glColor4d(0,0,0,1);
				string3d_draw(str);
				string3d_draw(str);
				string3d_draw(str);
			glPopMatrix();


			glPopAttrib();
			free(str);


			//TODO
			//PRINT MESSAGE : QUIT ?
			// YES NO 
			// q = QUIT
			if(keystate[SDLK_q]||keystate[SDLK_9])
				quit=1;
		}

	glFlush();
	SDL_GL_SwapBuffers();
		// fixed framerate ?
		// SDL_Delay(40-dt/1000.);

	}
	return 0;
}
