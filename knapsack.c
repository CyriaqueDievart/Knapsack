#include "knapsack.h"
#include "time.h"

/*
  HUGUES Pierre
  DIEVART Cyriaque
  CROCHON Cécile
  M2 TNSI FA
*/

int meta(Item *tab, int n, long int b) {
  clock_t begin = clock();
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
  
  int better[n];
  razObjSelect(objSelect, n);
  greedy(tab,n,b,objSelect,better);
  clock_t end = clock();
  double time_spend = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("%f", time_spend);
  return 0;
}

/* Remise à zéro des objets sélectionnés */
void razObjSelect(int *objSelect, int n) {
  for(int i = 0; i < (n*3); i++) {
    objSelect[i] = 0;
  }
 } 

/* Remise à zéro de better */
void razBetter(int *better, int n) {
  for(int i; i < n; i++) {
    better[i] = 0;
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

/* Sélectionne des objets au hasard */
void selectRandom(Item *tab, int n, long int b, int *objSelect) {
  long int currentCapacity = 0;
  if(b > 0) {
    for(int i = 0; i < n; i++){
      int rd = rand() % 3;
      if((currentCapacity + tab[i].w[rd]) <= b) {
        currentCapacity += tab[i].w[rd];
        int index = (i * 3) + rd;
        objSelect[index] = 1;
      }
    }
  }
}

/* Ordonne les objets en fonction du meilleur rapport poids prix de chaque groupe d'objet */
void orderBetter(Item *tab, int n, int *better) {
  selectBetter(tab, n, better);
  // triSelection(better, n);
  // triBulle(better, n);
  // triPermutation(better,n);
}

/* Sélectionne les meilleurs objets de chaque groupe */
void selectBetter(Item *tab, int n, int *better) {
  for(int i = 0; i < n; i++) {
    int best = bestOne(tab[i]); //On sélectionne le meilleur objet parmis chaque groupe
    better[i] = (i * 3) + best; // Si le meilleur objet du groupe n°1 est le 2eme alors son index est (1 * 3) + 2 = 5
  }
}

/* Tri par sélection */
void triSelection(int *better, int n) {
  for(int i = 0; i < n - 1; i++){
    for(int j = i + 1; j < n; j++) {
      if(rapportPrixPoids(tab, i) < rapportPrixPoids(tab, j)) {
        int c = better[i];
        better[i] = better[j];
        better[j] = c;
      }
    } 
  }
}

/* Tri à bulle */
void triBulle(int *better, int n) {
  for(int j = 1;  j <= n; j++) {
    for(int i = 0; i< n - 1; i++) {
      if(rapportPrixPoids(tab, i) < rapportPrixPoids(tab, i+1)) {
        int c = better[i];
        better[i] = better[i+1];
        better[i+1] = c;
      }
    }
  }
}

/* Tri par permutation */
void triPermutation(int *better, int n) {
  for(int i = 1; i < n; i++) {
    if(rapportPrixPoids(tab, i) > rapportPrixPoids(tab, i-1)) {
      int j = n;
      while(rapportPrixPoids(tab, j) > rapportPrixPoids(tab, i)) j--;
    }
  }
}

/* Retourne le rapport prix-poids d'un objet */
float rapportPrixPoids(Item *tab, int index) {
  return (getPoids(tab,index) / getPrix(tab,index));
}

/* Retourne le quotient d'une division euclidenne */
int quotient(int dividende, int diviseur) {
  int quotient = (dividende - reste(dividende, diviseur)) / diviseur;
  return quotient; 
}

/* Retourne le reste d'une division euclidienne*/
int reste (int dividende, int diviseur) {
  return dividende % diviseur;
}

/* Retourne le poids d'un objet*/
int getPoids(Item *tab, int index){
  int indexObj = reste(index, 3);
  int indexTab = quotient(index, 3);
  return tab[indexTab].w[indexObj];
}

/* Retourne le prix d'un objet */
int getPrix(Item *tab, int index) {
  int indexObj = reste(index, 3);
  int indexTab = quotient(index, 3);
  return tab[indexTab].p[indexObj];
}

/* Algorithme glouton*/
void greedy(Item *tab, int n, long int b, int *objSelect, int *better) {
  orderBetter(tab,n,better);
  long int currentCapacity =  0;
  for(int i = 0; i < n; i++) {
    if(currentCapacity + getPoids(tab,i) <= b) {
      currentCapacity += getPoids(tab,i);
      objSelect[i] = 1;
    }
  }
}