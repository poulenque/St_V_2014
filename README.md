St_V_2014
=========

the game

Vous incarnez Cupidon qui tire ses fleches dans son monde torride (oui il vit sur la surface d'un tore) d'un clique gauche precis avec une touche ctrl infaillible, tout en volant gracieusement en battant des ailes avec la touche espace du clavier, grace a ses majestueuses helices de sa casquette a helices. Il se deplace avec wasd (clavier normal) ou zqsd (clavier franco-paranormal), vise et tend son arc grace d'un clique droit sec et rapide (ou d'une touche Alt) afin de toucher avec precision... meme si finalement son vise est en realite assez peu precis, le geste n'etant qu'une vaine tentative de credibilisation dans la societe divine.
Aussi, Cupidon est un personnage un peu sauvage et tire sur tout ce qu'il trouve... si bien qu'il fini par irriter ses ennemis low-polys contre lesquels il ne pourra lutter qu'avec amour, soit en les transpercant de ses fleches tranchantes qui font sa reputation.

TODO
----
musique

synchroniser les pas de marche
synchroniser les mechants

mechant

leveldesign
vaisseaux spaciaux (gros cube gris qui vomissent des ennemis)

ajouter de l'entropie dans game->arrows : si la liste chainee est dans un grand desordre, l'optimisation pour les fleches fera un truc plus joli... faire une fonction desordre et melanger les fleches de facon aleatoires pour "repartir" dans l'espace et detruire l'ordre d'entree.
-> liste chainee dans les deux directions
-> ajouter de l'entropie en partant du debut jusqu'a un certain pourcentage
l'effet sera que les fleches les plus recentes ne disparaitront pas avec le culling

paralleliser la rangement des elements



TRICKS:
poum poum poum
-> arc disparait
-> reapparait avec 3 fleches

-> le fond est blanc, on a tue tout ce qui est noir:
le fond change de couleur et apparaissent les ennemis blanc

needed libraries :
------------------
 - SDL
 - GLEW
 - openAL

