set terminal png size 1000,600 enhanced font "Arial,12"
set output 'comparaison_algos.png'

set title "Comparaison Flood-It : Récursif vs Rapide"
set xlabel "Dimension de la grille (n)"
set ylabel "Temps d'exécution (secondes)"
set grid

# Position de la légende
set key left top

# On trace les deux fichiers. 
# Le récursif s'arrêtera plus tôt sur le graphe (car on limite n à 100)
plot 'donnees_rec.txt' using 1:2 with linespoints lw 2 lc rgb "red" title 'Récursif (Exo 1)', \
     'donnees_rapide.txt' using 1:2 with linespoints lw 2 lc rgb "blue" title 'Rapide (Exo 2)'
