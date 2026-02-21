#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "API_Grille.h"
#include "API_Gene_instance.h"
#include "Entete_Fonctions.h" 
#include "S_Zsg.h"            

#define TAILLE_MAX  100   // on teste jusqu'à 100x100 
#define PAS         5

int main() {
    srand(time(NULL));

    int dim, nbcl = 10, nivdif = 50, graine = 42;
    int **M, **M_copie;
    int i, j;
    
    // variables pour les résultats
    int coups_exo3, coups_exo4;
    clock_t debut, fin;
    double temps_exo3, temps_exo4;

    printf("Comparaison Stratégies : Max-Bordure (Exo 3) vs Max-Bordure-Zone (Exo 4)\n");

    FILE *fic = fopen("donnees_strategies.txt", "w");
    if (fic == NULL) return 1;

    // entête du fichier texte
    fprintf(fic, "# Dim Coups_Exo3 Temps_Exo3 Coups_Exo4 Temps_Exo4\n");

    for (dim = 10; dim <= TAILLE_MAX; dim += PAS) {

        /*allocation */
        M = (int **)malloc(sizeof(int*) * dim);
        M_copie = (int **)malloc(sizeof(int*) * dim);
        for (i = 0; i < dim; i++) {
            M[i] = (int*)malloc(sizeof(int) * dim);
            M_copie[i] = (int*)malloc(sizeof(int) * dim);
        }

    
        Gene_instance_genere_matrice(dim, nbcl, nivdif, graine, M);

        /*copie exacte pour l'exo 4 */
        for(i=0; i<dim; i++)
            for(j=0; j<dim; j++)
                M_copie[i][j] = M[i][j];


        /* test exo 3 (max bordure) */
        debut = clock();
        coups_exo3 = strategie_max_bordure(M, NULL, dim, nbcl, 0); // aff=0 pas d'affichage
        fin = clock();
        temps_exo3 = ((double)(fin - debut)) / CLOCKS_PER_SEC;

        /* test exo 4 (max bordure-zone) */
        debut = clock();
        coups_exo4 = strategie_max_bordure_zone(M_copie, NULL, dim, nbcl, 0); // aff=0 pas d'affichage
        fin = clock();
        temps_exo4 = ((double)(fin - debut)) / CLOCKS_PER_SEC;

        /* écriture des résultats */
        // colonnes : 1=Dim, 2=Coups3, 3=Temps3, 4=Coups4, 5=Temps4
        fprintf(fic, "%d %d %f %d %f\n", dim, coups_exo3, temps_exo3, coups_exo4, temps_exo4);
        
        printf("Dim %d : Exo3 = %d coups, Exo4 = %d coups\n", dim, coups_exo3, coups_exo4); 

        /* libération */
        for (i = 0; i < dim; i++) {
            free(M[i]);
            free(M_copie[i]);
        }
        free(M);
        free(M_copie);
    }

    fclose(fic);
    printf("Terminé. Données dans 'donnees_strategies.txt'\n"); // message  de fin
    return 0;
}