#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "API_Grille.h"
#include "API_Gene_instance.h"
#include "Entete_Fonctions.h" /*  récursif (Exo 1) */
#include "S_Zsg.h"            /*  rapide (Exo 2) */

#define TAILLE_MAX_RAPIDE 1000  
#define TAILLE_MAX_REC    300   
#define PAS               50   

/* paramètres pour le test des couleurs */
#define DIM_FIXE          40    // taille fixe petite pour que le récursif tienne le coup
#define COULEUR_MAX       100   // on teste jusqu'à 100 couleurs
#define PAS_COULEUR       10    // on avance de 10 en 10

int main() {
    srand(time(NULL));

    int dim, nbcl, nivdif = 50, graine = 42;
    clock_t debut, fin;
    double temps;
    int **M, **M_copie;
    int i, j;

    /* partie 1 : VARIATION DE LA TAILLE (DIMENSION N)           */
    
    printf("\n=== PARTIE 1 : Variation de la TAILLE (Couleurs fixées à 10) ===\n");
    FILE *fic_rec = fopen("donnees_rec.txt", "w");
    FILE *fic_rapide = fopen("donnees_rapide.txt", "w");
    
    nbcl = 10; // on fixe le nombre de couleurs

    for (dim = 50; dim <= TAILLE_MAX_RAPIDE; dim += PAS) {
        
        //allocation 
        M = (int **)malloc(sizeof(int*) * dim);
        M_copie = (int **)malloc(sizeof(int*) * dim);
        for (i = 0; i < dim; i++) {
            M[i] = (int*)malloc(sizeof(int) * dim);
            M_copie[i] = (int*)malloc(sizeof(int) * dim);
        }

        // génération
        Gene_instance_genere_matrice(dim, nbcl, nivdif, graine, M);
        for(i=0; i<dim; i++) for(j=0; j<dim; j++) M_copie[i][j] = M[i][j];

        // algo récursif
        if (dim <= TAILLE_MAX_REC) {
            debut = clock();
            sequence_aleatoire_rec(M, NULL, dim, nbcl, 0); 
            fin = clock();
            temps = ((double)(fin - debut)) / CLOCKS_PER_SEC;
            fprintf(fic_rec, "%d %f\n", dim, temps);
        }

        // algo rapide
        debut = clock();
        sequence_aleatoire_rapide(M_copie, NULL, dim, nbcl, 0);
        fin = clock();
        temps = ((double)(fin - debut)) / CLOCKS_PER_SEC;
        fprintf(fic_rapide, "%d %f\n", dim, temps);
        
        printf("Taille %d traitée...\n", dim); //message de progression

        /* libération */
        for (i = 0; i < dim; i++) { free(M[i]); free(M_copie[i]); }
        free(M); free(M_copie);
    }

    fclose(fic_rec);
    fclose(fic_rapide);


    /* partie 2 : VARIATION DU NOMBRE DE COULEURS (DIMENSION FIXE)     */

    printf("\n=== PARTIE 2 : Variation des COULEURS (Taille fixée à %d) ===\n", DIM_FIXE);
    
    FILE *fic_rec_col = fopen("donnees_rec_couleurs.txt", "w");
    FILE *fic_rap_col = fopen("donnees_rapide_couleurs.txt", "w");

    dim = DIM_FIXE; // on fixe la dimension
    
    for (nbcl = 10; nbcl <= COULEUR_MAX; nbcl += PAS_COULEUR) {

        //allocation 
        M = (int **)malloc(sizeof(int*) * dim);
        M_copie = (int **)malloc(sizeof(int*) * dim);
        for (i = 0; i < dim; i++) {
            M[i] = (int*)malloc(sizeof(int) * dim);
            M_copie[i] = (int*)malloc(sizeof(int) * dim);
        }

        // génération (on passe nbcl qui change à chaque tour de 10 pas)
        Gene_instance_genere_matrice(dim, nbcl, nivdif, graine, M);
        for(i=0; i<dim; i++) for(j=0; j<dim; j++) M_copie[i][j] = M[i][j];

        // algo récursif
        debut = clock();
        sequence_aleatoire_rec(M, NULL, dim, nbcl, 0);
        fin = clock();
        temps = ((double)(fin - debut)) / CLOCKS_PER_SEC;
        fprintf(fic_rec_col, "%d %f\n", nbcl, temps);

        // algo rapide
        debut = clock();
        sequence_aleatoire_rapide(M_copie, NULL, dim, nbcl, 0);
        fin = clock();
        temps = ((double)(fin - debut)) / CLOCKS_PER_SEC;
        fprintf(fic_rap_col, "%d %f\n", nbcl, temps);

        printf("%d Couleurs traitées...\n", nbcl);

        /* libération */
        for (i = 0; i < dim; i++) { free(M[i]); free(M_copie[i]); }
        free(M); free(M_copie);
    }

    fclose(fic_rec_col);
    fclose(fic_rap_col);

    printf("\nFin totale. 4 fichiers générés.\n");
    return 0;
}