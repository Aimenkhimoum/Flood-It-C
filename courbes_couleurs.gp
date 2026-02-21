set terminal png size 1000,600 enhanced font "Arial,12"
set output 'comparaison_algos_couleurs.png'

set title "Comparaison Flood-It : Temps vs Nombre de Couleurs (Taille fixe)"
set xlabel "Nombre de couleurs"
set ylabel "Temps d'exécution (secondes)"
set grid

# Position de la légende
set key left top

# On trace les deux fichiers pour la variation de couleur
plot 'donnees_rec_couleurs.txt' using 1:2 with linespoints lw 2 lc rgb "red" title 'Récursif (Exo 1)', \
     'donnees_rapide_couleurs.txt' using 1:2 with linespoints lw 2 lc rgb "blue" title 'Rapide (Exo 2)'
