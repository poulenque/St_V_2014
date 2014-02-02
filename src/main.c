#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#include "game.h"
#include "camera.h"
#include "string3d.h"

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
	if(argc>1){
		if(!strcmp(argv[1],"--help")||!strcmp(argv[1],"-h")){
			printf("-h or --help    : help (prints this message)\n");
			printf("-v or --version : version\n");
			printf("-d or --duck    : duck ?\n");
			printf("-c or --credits : credits\n");
			printf("-s or --stereo  : stereoscopic mode (warning: really slow !)\n");
			printf("wow that was helpful!\n");
			return 1;
		}
		if(!strcmp(argv[1],"--stereo")||!strcmp(argv[1],"-s")){
			printf("STEREOSCOPY !!!\n");
			printf("dividing FPS per 2 !!!\n");
			return 2;
		}
		if(!strcmp(argv[1],"--version")||!strcmp(argv[1],"-v")){
			printf("it's over 9000.0.1\n");
			return 1;
		}
		if(!strcmp(argv[1],"--duck")||!strcmp(argv[1],"-d")){
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
			return 1;
		}
		if(!strcmp(argv[1],"--credits")||!strcmp(argv[1],"-c")){
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

			return 1;
		}
		printf("wut ?? I didn't get that... try --help or -h instead...\n");
		return 1;
	}
	return 0;
}


int main(int argc, char *argv[]) {
	int parseReturn= parseArgs(argc, argv);
	int stereo=0;
	if(parseReturn==1) return 1;
	if(parseReturn==2) stereo=1;

	//RANDOM INIT
	srand((unsigned)time(NULL));

	//SDL INITIALIZATION
	putenv("SDL_VIDEO_CENTERED=1");
	int SCREEN_WIDTH=800;
	int SCREEN_HEIGHT=600;
	int SCREEN_BPP=32;
	SDL_Init( SDL_INIT_EVERYTHING );
	SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL );
	SDL_EnableUNICODE( SDL_TRUE );
	SDL_WM_GrabInput(SDL_GRAB_ON);

	int mouse_x = 0, mouse_y = 0;
	// int mouse_dx = 0, mouse_dy = 0;
	int quit=0;
	Uint8 *keystate;

	int t_before=SDL_GetTicks();
	int dt=0;

	Camera* player = new_Camera();
	Game* game = initGame(player);
	player->game=game;

	INIT_ULTRA_NECESSARY_TITLE_ANIMATION();
	
	SDL_Event event;
	while( SDL_PollEvent( &event ) );
	SDL_ShowCursor( SDL_DISABLE );

	while(!quit){
		dt=SDL_GetTicks()-t_before;
		t_before = SDL_GetTicks();
		keystate = SDL_GetKeyState(NULL);
		SDL_GetMouseState( &mouse_x, &mouse_y );
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
					if(event.key.keysym.sym ==SDLK_ESCAPE)
						quit=1;
					break;
				case SDL_MOUSEMOTION:
					camera_rotate(player,0,2*event.motion.xrel,0);
					break;
			}
		}
		//========================
		double speed=1000;
		if (keystate[SDLK_ESCAPE]){
			quit=1;
		}
		if (keystate[SDLK_a]){
			camera_move_acc(player,0,-speed,0);
		}
		if (keystate[SDLK_d]){
			camera_move_acc(player,0,speed,0);
		}
		if (keystate[SDLK_w] || keystate[SDLK_UP]){
			camera_move_acc(player,-speed,0,0);			
		}
		if (keystate[SDLK_s] || keystate[SDLK_DOWN]){
			camera_move_acc(player,speed,0,0);
		}
		// if (keystate[SDLK_e]){
		// 	camera_move_acc(player,0,0,-speed);
		// }
		// if (keystate[SDLK_q]){
		// 	camera_move_acc(player,0,0,speed);
		// }

		if(keystate[SDLK_LALT]){
			if (keystate[SDLK_LEFT]){
				camera_move_acc(player,0,-speed,0);
			}
			if (keystate[SDLK_RIGHT]){
				camera_move_acc(player,0,speed,0);
			}
		}else{
			speed=5000;
			if (keystate[SDLK_LEFT]){
				camera_rotate_acc(player,0,-speed,0);
			}
			if (keystate[SDLK_RIGHT]){
				camera_rotate_acc(player,0,speed,0);
			}
		}
		// if (keystate[SDLK_UP]){
		// 	camera_rotate_acc(player,speed,0,0);
		// }
		// if (keystate[SDLK_DOWN]){
		// 	camera_rotate_acc(player,-speed,0,0);
		// }


		ULTRA_NECESSARY_TITLE_ANIMATION();

		game->update(game,dt);

		if(stereo)
			camera_render_stereo(player);
		else
			camera_render(player);

		// fixed framerate ?
		// SDL_Delay(40-dt/1000.);

	}
	return 0;
}
