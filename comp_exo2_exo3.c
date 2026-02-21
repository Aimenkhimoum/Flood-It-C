#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "API_Grille.h"
#include "API_Gene_instance.h"
#include "Entete_Fonctions.h"

#define TAILLE_MAX      100   // max Bordure 
#define PAS_TAILLE      10
#define COULEUR_FIXE    10   

#define TAILLE_FIXE     40 // taille fixe pour le test de couleur   
#define COULEUR_MAX     50
#define PAS_COULEUR     5 // on avance de 5 couleurs

int main() {
    srand(time(NULL));
    clock_t debut, fin;
    double temps;
    int dim, nbcl;
    int **M, **M_copie;
    int i, j;

    printf("=== COMPARAISON EXO 2 (Aléatoire) vs EXO 3 (Max Bordure) ===\n");

    /*  TEST EN FONCTION DE LA TAILLE (N)*/

    printf("\n--- Test 1 : Variation de la TAILLE (Couleurs = %d) ---\n", COULEUR_FIXE);
    
    FILE *f2_n = fopen("data_exo2_taille.txt", "w");
    FILE *f3_n = fopen("data_exo3_taille.txt", "w");

    nbcl = COULEUR_FIXE;

    for (dim = 20; dim <= TAILLE_MAX; dim += PAS_TAILLE) {
        
        // allocation
        M = (int **)malloc(sizeof(int*) * dim);
        M_copie = (int **)malloc(sizeof(int*) * dim);
        for(i=0; i<dim; i++){
            M[i] = (int*)malloc(sizeof(int)*dim);
            M_copie[i] = (int*)malloc(sizeof(int)*dim);
        }

        // génération de la matrice
        Gene_instance_genere_matrice(dim, nbcl, 50, 42, M);
        // copie  pour que les deux algos affrontent la même grille
        for(i=0; i<dim; i++) for(j=0; j<dim; j++) M_copie[i][j] = M[i][j];

        // EXO 2 : Aléatoire Rapide
        debut = clock();
        sequence_aleatoire_rapide(M, NULL, dim, nbcl, 0); // aff=0  pas d'affichage
        fin = clock();
        temps = ((double)(fin - debut)) / CLOCKS_PER_SEC;
        fprintf(f2_n, "%d %f\n", dim, temps);

        // EXO 3 : Max Bordure
        debut = clock();
        

        strategie_max_bordure(M_copie, NULL, dim, nbcl, 0); 
        fin = clock();
        temps = ((double)(fin - debut)) / CLOCKS_PER_SEC;
        fprintf(f3_n, "%d %f\n", dim, temps);

        printf("Taille %d traitée...\n", dim);

        // désallocation
        for(i=0; i<dim; i++){ free(M[i]); free(M_copie[i]); }
        free(M); free(M_copie);
    }
    fclose(f2_n);
    fclose(f3_n);


    /*  TEST EN FONCTION DES COULEURS (C)*/

    printf("\n--- Test 2 : Variation des COULEURS (Taille = %d) ---\n", TAILLE_FIXE);

    FILE *f2_c = fopen("data_exo2_couleurs.txt", "w");
    FILE *f3_c = fopen("data_exo3_couleurs.txt", "w");

    dim = TAILLE_FIXE;

    for (nbcl = 10; nbcl <= COULEUR_MAX; nbcl += PAS_COULEUR) {
        
        // allocation
        M = (int **)malloc(sizeof(int*) * dim);
        M_copie = (int **)malloc(sizeof(int*) * dim);
        for(i=0; i<dim; i++){
            M[i] = (int*)malloc(sizeof(int)*dim);
            M_copie[i] = (int*)malloc(sizeof(int)*dim);
        }

        // génération de la matrice
        Gene_instance_genere_matrice(dim, nbcl, 50, 42, M);
        for(i=0; i<dim; i++) for(j=0; j<dim; j++) M_copie[i][j] = M[i][j];

        // EXO 2 : aléatoire rapide
        debut = clock();
        sequence_aleatoire_rapide(M, NULL, dim, nbcl, 0);
        fin = clock();
        temps = ((double)(fin - debut)) / CLOCKS_PER_SEC;
        fprintf(f2_c, "%d %f\n", nbcl, temps);
        
        // EXO 3 : max bordure
        debut = clock();
        strategie_max_bordure(M_copie, NULL, dim, nbcl, 0);
        fin = clock();
        temps = ((double)(fin - debut)) / CLOCKS_PER_SEC;
        fprintf(f3_c, "%d %f\n", nbcl, temps);

        printf("Couleurs %d traitées...\n", nbcl);

        // désallocation
        for(i=0; i<dim; i++){ free(M[i]); free(M_copie[i]); }
        free(M); free(M_copie);
    }
    fclose(f2_c);
    fclose(f3_c);

    printf("\nFin des tests. Données générées.\n");
    return 0;
}