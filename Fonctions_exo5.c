#include <stdio.h>
#include <stdlib.h>
#include "Entete_Fonctions.h"
#include "S_Zsg.h"

// valeur temporaire pour marquer qu'on a compté cette case dans la simulation (pour la stratégie de l'exo 5 )
#define VISITE_SIMU -9


  //une fonction pour estimer la taille de la zone avec une couleur cl donnée sans modifier M ni Z
int estime_taille_zone(int **M, S_Zsg *Z, int cl) {
    int taille_gain = 0;   // taille du gain avec la couleur cl 
    ListeCase pile;       // liste qu'on va utiliser lors de l'exploration
    ListeCase casesVisitees; // liste pour mémoriser ce qu'on modifie pour le nettoyer après
    int i, j;
    
    // déplacements  bas, haut, droite, gauche (meme strategie proposé précedemment )
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    init_liste(&pile);       //on initialise la pile  
    init_liste(&casesVisitees);   //on initialise la liste des cases visitées

    //on charge la pile avec les cases de la bordure actuelle de cette couleur
    ListeCase p = Z->B[cl];
    while (p != NULL) {  //tant que il y a des cases dans la bordure de couleur cl

        //on vérifie qu'on n'a pas déjà compté cette case 
        if (Z->App[p->i][p->j] != VISITE_SIMU) {
            ajoute_en_tete(&pile, p->i, p->j);
            
            //on marque la case dans App sans toucher M
            Z->App[p->i][p->j] = VISITE_SIMU;
            ajoute_en_tete(&casesVisitees, p->i, p->j); // on empile casesVisitees pour le nettoyage plus tard
            taille_gain++;   // on incrémente la taille du gain
        }
        p = p->suiv;
    }

    // exploration (on compte tout ce qui est connecté avec les cases qui sont dans la pile)
    while (!test_liste_vide(&pile)) {
        enleve_en_tete(&pile, &i, &j);
        //on regarde les 4 voisins
        for (int v = 0; v < 4; v++) {
            int nx = i + dx[v];
            int ny = j + dy[v];

            // verification si on on est dans la grille
            if (nx >= 0 && nx < Z->dim && ny >= 0 && ny < Z->dim) {
                
                // si la case est de la bonne couleur et pas encore comptée et pas déjà dans la Zsg principale
                if (M[nx][ny] == cl && Z->App[nx][ny] != VISITE_SIMU && Z->App[nx][ny] != DANS_ZSG) {
                    
                    // on l'ajoute au gain 
                    Z->App[nx][ny] = VISITE_SIMU;
                    ajoute_en_tete(&pile, nx, ny); // on l'ajoute pour explorer ses voisins plus tard
                    ajoute_en_tete(&casesVisitees, nx, ny);  //on l'ajoute à casesVisitees pour le nettoyage plus tard
                    taille_gain++;
                }
            }
        }
    }

    // la partie du NETTOYAGE, on remet le tableau App dans son état d'origine comme on a la liste casesVisitees
    while (!test_liste_vide(&casesVisitees)) {
        enleve_en_tete(&casesVisitees, &i, &j); //on depile une case 
        
        // si c'était une bordure à l'origine, on remet le code couleur. Sinon -2 car non rencontré
        //une case est une bordure si elle touche la Zsg -1
        int est_bordure = 0;
        for (int v = 0; v < 4; v++) {
            int nx= i + dx[v];
            int ny= j + dy[v];
            if (nx >= 0&& nx < Z->dim && ny >= 0 && ny < Z->dim) {
                if (Z->App[nx][ny] == DANS_ZSG) { //si l'un des voisins est dans la Zsg donc c'est une bordure
                    est_bordure = 1;
                    break;
                }
            }
        }

        if (est_bordure) Z->App[i][j] = cl; //si c'etait une bordure on remet la couleur cl 
        else Z->App[i][j] = NON_RENCONTRE; //si non on marque comme non rencontré
    }

    detruit_liste(&pile); // on détruit la pile 
    return taille_gain;   // on retourne la taille du gain estimé pour cl 
}




/*  La stratégie principale qui compare les zones en utilisant la fonction estime_taille_zone */
int strategie_exo5(int **M, Grille *G, int dim, int nbcl, int aff) {
    int cpt = 0;   // compteur de coups
    int cur_color = M[0][0];  //couleur courante initiale
    int taille = 0;    // taille initiale de la Zsg
    int best_color;   // variable pour la meilleure couleur
    int max_gain;   // variable pour le gain maximal estimé
    
    //initialisation de la Zsg a la case (0,0
    S_Zsg *Z = init_Zsg(dim, nbcl);
    taille = agrandit_Zsg(M, Z, cur_color, 0, 0);


    //meme logique de boucle que les autres stratégies tant que la taille est inférieure à la taille totale de la grille
    while(taille < dim*dim) {
        cpt++;        //on incremente le nombre de coups
        
        max_gain = -1;   // initialisation du gain maximal
        best_color = -1;  // initialisation de la meilleure couleur

        
        // boucle qui essaie toutes les couleurs pour estimer le gain
        for (int c = 0; c < nbcl; c++) {
            if (c == cur_color) continue;   //si c est la couleur courante on passe
            
            // si cette couleur n'a aucune case en bordure alors inutile de simuler
            if (Z->B[c] == NULL) continue; 

            // si non on lance la simulation pour la couleur c
            int gain = estime_taille_zone(M, Z, c);
            
            // on garde le meilleur en comparant avec max_gain
            if (gain > max_gain) {
                max_gain = gain;   //on met a jour le gain maximal
                best_color = c;    //on met a jour la meilleure couleur
            }
        }

        //on joue le coup gagnant trouvé
        cur_color = best_color;

        //on met à jour l'affichage comme précédemment
        ListeCase temp = Z->Lzsg;
        while(temp != NULL) {
            M[temp->i][temp->j] = cur_color;
            if(aff == 1) {
              Grille_attribue_couleur_case(G, temp->i, temp->j, cur_color); //si aff = 1 on met a jour l'affichage
            } 
            temp = temp->suiv;
        }

        ListeCase p = Z->B[cur_color]; // on parcourt la bordure de la couleur jouée
        while(p != NULL) {
            taille += agrandit_Zsg(M, Z, cur_color, p->i, p->j); //on agrandit la Zsg et on met à jour la taille
            p = p->suiv;
        }
        
        detruit_liste(&(Z->B[cur_color])); //on détruit la liste bordure de la couleur jouée car ce n'est plus une bordure

        if(aff == 1){
       Grille_redessine_Grille(G); // on redessine la grille si aff = 1
    }
  }
    detruit_Zsg(Z);
    return cpt;   //on retourne le nombre de coups total
}