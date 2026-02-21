#include <stdio.h>
#include <stdlib.h>
#include "S_Zsg.h"
#include "API_Grille.h"

/*fonction pour initialiser Zsg avec dim comme dimension et nbcl comme nombre de couleurs*/
S_Zsg *init_Zsg(int dim, int nbcl) {
    S_Zsg *S = (S_Zsg *) malloc(sizeof(S_Zsg)); //allocation de la structure
    if (S == NULL) return NULL;

    S->dim = dim;
    S->nbcl = nbcl;
    
    // initialisation de Lzsg avec la fonction de ListeCase 
    init_liste(&(S->Lzsg)); 

    // initialisation de B (tableau de taille==nbcl de listes)
    S->B = (ListeCase *)malloc(sizeof(ListeCase)* nbcl);
    if (S->B ==NULL) { 
        free(S);
         return NULL;
             }
    for (int c = 0; c < nbcl; c++) {
        init_liste(&(S->B[c]));
    }
    
    /* initialisation de App (matrice dim x dim) */
    S->App = (int **) malloc(sizeof(int *) * dim);
    if (S->App == NULL) { 
        free(S->B); 
        free(S); return NULL; }
    for (int i = 0; i < dim; i++){
        S->App[i] = (int *) malloc(sizeof(int) * dim);

        if (S->App[i] == NULL) { 
            /* libération en cas d'erreur */
            for (int k = 0; k <i;k++) {
                free(S->App[k]);
            }
            free(S->App);
            free(S->B);
            free(S);
            return NULL; //tout liberer et retourner NULL
        }
        for (int j = 0; j < dim; j++) {
            S->App[i][j] = NON_RENCONTRE; /* toutes les cases sont initialement non rencontrées == -2 */
        }
    }
    
    return S;
}

/* fonction pour détruire Zsg */
void detruit_Zsg(S_Zsg *S) {
    if (S == NULL) return;

    // destruction de Lzsg d'abord
    detruit_liste(&(S->Lzsg));

    // destruction des listes dans B et du tableau B
    for (int c = 0; c < S->nbcl; c++) {
        detruit_liste(&(S->B[c]));
    }
    free(S->B);

    // libération de la matrice App
    for (int i = 0; i< S->dim;i++) {
         free(S->App[i]);
    }
    free(S->App);

    /* libération de S_Zsg */
    free(S);
}

// fonctions EXO2  O(1) 

/* Q 2.1 - ajoute Zsg , parametre i et j sont les indices de la case */

void ajoute_Zsg(S_Zsg *S,int i, int j) {
    // ajouter la case à Lzsg avec la fonction ajoute_en_tete de ListeCase
    ajoute_en_tete(&(S->Lzsg), i, j);
    
    // marquer la case dans App comme appartenant à la Zsg
    S->App[i][j] = DANS_ZSG;
}

/* Q 2.1 - ajoute Bordure , parametre i et j sont les indices de la case et cl est la couleur */
void ajoute_Bordure(S_Zsg *S, int i, int j, int cl) {
    // ajouter la case à la liste B[cl] avec la fonction ajoute_en_tete de ListeCase
    ajoute_en_tete(&(S->B[cl]), i, j);
    
    // mettre à jour le tableau App avec la couleur de bordure
    S->App[i][j] = cl; // cl est le numéro de la couleur de la bordure
}

/* Q 2.1 - appartient Zsg , parametre i et j sont les indices de la case */
int appartient_Zsg(S_Zsg *S, int i, int j) {
    // vérification dans le tableau App
   
    return (S->App[i][j] == DANS_ZSG);
}

/* Q 2.1 - appartient Bordure , parametre i et j sont les indices de la case et cl est la couleur */
int appartient_Bordure(S_Zsg *S, int i, int j, int cl) {
    // vérification si App[i][j] egale à cl (la couleur de la bordure testée)
   
    return (S->App[i][j]== cl);
}

/* Q 2.2 agrandit_Zsg , parametre M matrice et Z Zsg et cl couleur et k,l indices de la case de départ */
int agrandit_Zsg(int **M, S_Zsg *Z, int cl, int k,int l) {
    ListeCase pile;
    int i, j, nb_ajouts = 0;
    int dx[] = {0, 0, 1, -1}; //déplacements  bas, haut, droite, gauche
    int dy[] = {1, -1, 0, 0}; //tableaux qui aide pour les déplacements dans les 4 voisines 
    
    // initialisation de la pile avec la case de départ
    init_liste(&pile);
    ajoute_en_tete(&pile, k, l);

    // tant qu'il reste des cases à explorer dans la pile , si la pile est vide alors la Zsg est complètement agrandie
    while(!test_liste_vide(&pile)) {
        
        //on récupère la case (i , j) courante qu'on va depiler de la pile
        enleve_en_tete(&pile, &i, &j);

        //si la case est déjà dans la Zsg, on l'ignore  
        if (appartient_Zsg(Z, i, j)) {
            continue; 
        }

        // sinon, on l'ajoute à la Zsg
        ajoute_Zsg(Z, i, j);
         nb_ajouts++; //on incrémente le nombre d'ajouts 

        //exploration des 4 voisins avec les tableaux dx et dy  
        for (int v = 0; v < 4;v++) {
            int nx= i + dx[v]; // indice voisin x
            int ny= j + dy[v]; // indice voisin y

            // vérification que le voisin est dans la grille
            if (nx >= 0 && nx < Z->dim && ny >= 0 && ny < Z->dim) {
                
                // si le voisin est déjà dans la Zsg, on ne fait rien
                if (appartient_Zsg(Z, nx, ny)) {
                    continue;
                }

                //si la couleur du voisin est la même que cl ,on l'ajoute à la pile pour l'explorer plus tard
                if (M[nx][ny]==cl) {
                    // c'est la même couleur : on l'ajoute à la pile pour l'explorer et l'ajouter à Zsg plus tard
                    ajoute_en_tete(&pile, nx, ny);
                } else {
                    // c'est une couleur différente : c'est une bordure
                    // on l'ajoute à la bordure de sa couleur, si elle n'y est pas déjà
                    if (!appartient_Bordure(Z, nx, ny, M[nx][ny])) {
                        ajoute_Bordure(Z, nx, ny, M[nx][ny]);
                    }
                }
              }
        }
    }

    // on détruit la liste pile
         detruit_liste(&pile);
    
    return nb_ajouts; // on retourne le nombre de cases ajoutées à la Zsg
}

/* Q 2.3 sequence_aleatoire_rapide , parametre M matrice , Z Zsg , dim dimension , nbcl nombre de couleurs , aff affichage */
int sequence_aleatoire_rapide(int **M, Grille *G, int dim, int nbcl, int aff) {
    int cpt = 0; // compteur de coups
    int cl;
    int cur_color = M[0][0]; // couleur courante initiale
    
    S_Zsg *Z = init_Zsg(dim, nbcl); // initialisation de la Zsg
    
    
    //pour avoir la taille initiale de la Zsg
    int taille = agrandit_Zsg(M, Z, cur_color, 0, 0);

// tant que la Zsg n'a pas envahi toute la grille
    while(taille < dim*dim) {
        cpt++; // incrémentation du nombre de coups
        
        //choix couleur différente de la couleur courante
        do {
            cl = rand() % nbcl;
        } while (cl == cur_color);
        
        cur_color = cl;
        //COULEUR COURRANTE RECOIT LA NOUVELLE COULEUR

        // mise à jour couleur matrice et affichage

        ListeCase temp = Z->Lzsg; //on parcourt la liste avec temp pour ne pas perdre la tête de la liste
        while(temp != NULL) {
            M[temp->i][temp->j] = cur_color;
           
            if(aff == 1){ //si aff==1 on met à jour l'affichage 
            Grille_attribue_couleur_case(G, temp->i, temp->j, cur_color);}

            temp = temp->suiv;
        }
        
        // agrandissement avec la bordure de la nouvelle couleur
        ListeCase p = Z->B[cl]; // on parcourt la bordure de la nouvelle couleur
        while(p != NULL) {
            taille += agrandit_Zsg(M, Z, cur_color, p->i, p->j);
            p = p->suiv;
        }
        
        detruit_liste(&(Z->B[cl])); //on détruit la liste de la bordure de la couleur jouée car ce n'est plus une bordure maintenant 
        
        if(aff == 1) {
        Grille_redessine_Grille(G); // on redessine la grille si aff = 1
        }
    
    }
    
    detruit_Zsg(Z); //on libère la mémoire allouée pour Zsg
    return cpt; //on retourne le nombre de coups total 
}
