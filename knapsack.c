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
  initialisation(tab, n, b, objSelect);
  long int initOpt = calculOpt(tab, n, objSelect);
  printf("initOpt : %ld \n", initOpt);

  razObjSelect(objSelect, n);
  selectBestInGroup(tab, n, b, objSelect);
  long int bestInGroupOpt = calculOpt(tab, n, objSelect);
  printf("bestInGroupOpt : %ld \n", bestInGroupOpt);
  
  return 0;
}

/* Remise à zéro des objets sélectionnés */
void razObjSelect(int *objSelect, int n) {
  for(int i = 0; i < n; i++) {
    objSelect[i] = 0;
  }
 } 

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