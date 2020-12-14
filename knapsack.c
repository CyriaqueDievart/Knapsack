#include "knapsack.h"

/*
  HUGUES Pierre
  DIEVART Cyriaque
  CROCHON Cécile
  M2 TNSI FA
*/

int meta(Item *tab, int n, long int b) {
  int objSelect[3*n]; // Tableau d'entier : 0 si item n°i non sélectionné 1 sinon
  razObjSelect(objSelect, n);
  printf("Poids sac : %d\n", calculpoids(tab, n, objSelect));
  initialisation(tab, n, b, objSelect);
  long int initOpt = calculOpt(tab, n, objSelect);
  printf("initOpt : %ld \n", initOpt);
  printf("Poids max : %d\n", b);
  printf("Poids sac : %d\n", calculpoids(tab, n, objSelect));

  razObjSelect(objSelect, n);
  printf("Poids sac : %d\n", calculpoids(tab, n, objSelect));
  selectBestInGroup(tab, n, b, objSelect);
  long int bestInGroupOpt = calculOpt(tab, n, objSelect);
  printf("bestInGroupOpt : %ld \n", bestInGroupOpt);
  printf("Poids max : %d\n", b);
  printf("Poids sac : %d\n", calculpoids(tab, n, objSelect));
  
  return 0;
}

/* Remise à zéro des objets sélectionnés */
void razObjSelect(int *objSelect, int n) {
  for(int i = 0; i < (n*3); i++) {
    objSelect[i] = 0;
  }
 } 

/* Sélectionne les 1ers objets d'un groupe tant qu'on ne dépasse pas le poids du sac */
void initialisation(Item *tab, int n, long int b, int *objSelect) {
  long int currentCapacity = 0;
  if(b > 0) {
    for(int i = 0; i < n; i++){
      if((currentCapacity + tab[i].w[0]) <= b) {
        currentCapacity += tab[i].w[0];
        int index = i * 3;
        objSelect[index] = 1;
      }
    }
  }
}

/* Calcule la valeur du sac en fonction des objets sélectionnés */
long int calculOpt(Item *tab, int n, int *objSelect) {
  long int opt = 0;
  for(int i = 0; i < (n * 3); i++) {
    if(objSelect[i] == 1) {
      int groupIndex = i % 3;
      int itemIndex = i - (groupIndex * 3);
      opt += tab[groupIndex].p[itemIndex];
    }
  }
  return opt;
}

/* Sélectionne les objets dont le rapport qualité prix est le plus élevé dans un groupe d'objets sans dépasser la capacité du sac */
void selectBestInGroup(Item *tab, int n, long int b, int *objSelect) {
  long int currentCapacity =  0;
    for(int i = 0; i < n; i++) {
      int best = bestOne(tab[i]);
      if ((currentCapacity + tab[i].w[best]) <= b) {
        currentCapacity += tab[i].w[best];
        int index = best + (i * 3);
        objSelect[index] = 1;
      }
    }
}

/* Retourne l'indice de l'objet qui a le meilleur rapport qualité prix dans le groupe de 3 objets */
int bestOne(Item item) {
  int res = -1;
 if((item.p[0] / item.w[0]) > (item.p[1] / item.w[1])) {
   res = 0;
 } else {
   res = 1;
 }
 if((item.p[res] / item.w[res]) < (item.p[2] / item.w[2])) {
   res = 2;
 }
 return res;
}

/* Calcule le poids d'un sac en fonction des objets qu'on a sélectionné */
int calculpoids(Item *tab, int n, int *objSelect) {
  int weight = 0;
  for(int i = 0; i < (n * 3); i++) {
    if(objSelect[i] == 1) {
      int itemIndex = i % 3;
      int groupIndex = (i - itemIndex) / 3;
      weight += tab[groupIndex].w[itemIndex];
    }
  }
  return weight;
}