#include "type.h"

/*
  HUGUES Pierre
  DIEVART Cyriaque
  CROCHON Cécile
  M2 TNSI FA
*/

int meta(Item *tab, int n, long int b){
  int objSelect[n]; // Tableau d'entier : 0 si item n°i non sélectionné 1 sinon
  razObjSelect(objSelect, n);
  initialisation(tab, n, b, objSelect);
  int currentOpt = calculOpt(tab, n, objSelect);



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
      if((currentCapacity + tab[i].w) <= b) {
        objSelect[i] = 1;
      }
    }
  }
}

int calculOpt(Item *tab, int n, int *objSelect) {
  int opt = 0;
  for(int i = 0; i < n; i++) {
    if(objSelect[i] == 1) {
      opt = opt + tab[i].p;
    }
  }
  return opt;
}

void selectBestInGroup(Item *tab, int n, long int b, int *objSelect) {
  for(int i = 0; i < n; i++) {
    
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