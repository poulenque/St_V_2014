St_V_2014
=========

the game

needed libraries :
------------------
 - SDL
 - GLEW
 - openAL

TODO
----

bug musique : get_amplitude fait n'importe quoi a la fin dans les transitions de fichiers

synchroniser les pas de marche
synchroniser les mechants

mechant

leveldesign
vaisseaux spaciaux (gros cube rouge et sombre qui vomissent des ennemis)

ajouter de l'entropie dans game->arrows : si la liste chainee est dans un grand desordre, l'optimisation pour les fleches fera un truc plus joli... faire une fonction desordre et melanger les fleches de facon aleatoires pour "repartir" dans l'espace et detruire l'ordre d'entree.
-> liste chainee dans les deux directions
-> ajouter de l'entropie en partant du debut jusqu'a un certain pourcentage
l'effet sera que les fleches les plus recentes ne disparaitront pas avec le culling


boss final

BUG dans la stereoscopie (corrier applyLeftFustrum and applyRightFustrum)



TRICKS:
poum poum poum
-> arc disparait
-> reapparait avec 3 fleches

-> le fond est blanc, on a tue tout ce qui est noir:
le fond change de couleur et apparaissent les ennemis blanc


