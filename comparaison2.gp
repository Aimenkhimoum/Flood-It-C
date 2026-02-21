# --- GRAPHIQUE 1 : SELON LA TAILLE ---
set terminal png size 1000,600 enhanced font "Arial,12"
set output 'comparaison_2_3_taille.png'

set title "Comparaison Temps : Aléatoire (Exo 2) vs Max-Bordure (Exo 3)"
set xlabel "Taille de la grille (n)"
set ylabel "Temps (secondes)"
set grid
set key left top

plot 'data_exo2_taille.txt' using 1:2 with linespoints lw 2 lc rgb "blue" title 'Exo 2 : Aléatoire', \
     'data_exo3_taille.txt' using 1:2 with linespoints lw 2 lc rgb "green" title 'Exo 3 : Max-Bordure'

# --- GRAPHIQUE 2 : SELON LES COULEURS ---
set output 'comparaison_2_3_couleurs.png'

set title "Impact du nombre de couleurs (Taille fixe)"
set xlabel "Nombre de couleurs"
set ylabel "Temps (secondes)"

plot 'data_exo2_couleurs.txt' using 1:2 with linespoints lw 2 lc rgb "blue" title 'Exo 2 : Aléatoire', \
     'data_exo3_couleurs.txt' using 1:2 with linespoints lw 2 lc rgb "green" title 'Exo 3 : Max-Bordure'
