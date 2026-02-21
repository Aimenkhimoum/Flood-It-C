set terminal png size 1200,800 enhanced font "Arial,12"
set output 'comparaison_strategies.png'

# Configuration pour afficher 2 graphiques côte à côte ou l'un sur l'autre
set multiplot layout 2,1 title "Comparaison Max-Bordure (Exo 3) vs Max-Bordure-Zone (Exo 4)"

# --- GRAPHIQUE 1 : EFFICACITÉ (Nombre de coups) ---
set title "Nombre de coups joués (Plus bas est mieux)"
set xlabel "Dimension (n)"
set ylabel "Nombre d'itérations"
set grid
plot 'donnees_strategies.txt' using 1:2 with linespoints lw 2 lc rgb "red" title 'Exo 3: Max-Bordure', \
     'donnees_strategies.txt' using 1:4 with linespoints lw 2 lc rgb "green" title 'Exo 4: Max-Bordure-Zone'

# --- GRAPHIQUE 2 : VITESSE (Temps de calcul) ---
set title "Temps de calcul CPU (Plus bas est mieux)"
set xlabel "Dimension (n)"
set ylabel "Temps (secondes)"
set grid
plot 'donnees_strategies.txt' using 1:3 with linespoints lw 2 lc rgb "red" title 'Exo 3: Max-Bordure', \
     'donnees_strategies.txt' using 1:5 with linespoints lw 2 lc rgb "green" title 'Exo 4: Max-Bordure-Zone'

unset multiplot
