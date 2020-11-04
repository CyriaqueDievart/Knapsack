#include "sacados.c"

/*
  HUGUES Pierre - THOMAS Roxanne
  M1 TNSI - Groupe apprentis
*/

int main() 
{
    char filename[255];
    int i;
    printf("---------------------------------------------------\n");
    printf("\t\tChoix du fichier\n");
    printf("---------------------------------------------------\n");
    printf("Filename for the problem :\n> ");
    scanf("%s", filename);
    printf("---------------------------------------------------\n");

    SAC sac = init_pb(filename);

    printf("\t\tListe d'objets\n");
    printf("---------------------------------------------------\n");
    printf("\t| Nombre objets : %d\n\t| Poids sac : %d\n", sac.n, sac.W);
    for(int i = 0 ; i < sac.n ; i++) {
       printf("\t| Objet %d : valant %d et pesant %d\n", i, sac.c[i], sac.w[i]);
    }
    printf("---------------------------------------------------\n");

    printf("\t\tAlgorithme glouton\n");
    int taken[sac.n];
    SAC newSac = reservation_SAC(sac.n, sac.W, sac.w, sac.c);
    int val = algo_glouton(newSac, taken);
    printf("---------------------------------------------------\n");
    printf("\t| Valeur de vente : %d\n", val);
    for(i = 0 ; i < newSac.n ; i++) {
        if(taken[i] == 1) {
            printf("\t| Objet pris : n°%d, valant %d et pesant %d\n", i, newSac.c[i], newSac.w[i]);
        }
    }
    printf("---------------------------------------------------\n");
    freeSac(newSac);

    printf("\t\tProgrammation Dynamique\n");
    int taken2[sac.n];
    int val2 = dynamique(sac, taken2);
    printf("---------------------------------------------------\n");
    printf("\t| Valeur de vente : %d\n", val2);
    for(i = 0 ; i < sac.n ; i++) {
        if(taken2[i] == 1) {
            printf("\t| Objet pris : n°%d, valant %d et pesant %d\n", i, sac.c[i], sac.w[i]);
        }
    }
    printf("---------------------------------------------------\n");

    freeSac(sac);

    return 0;
}