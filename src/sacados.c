#include "type.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

/*
  HUGUES Pierre
  DIEVART Cyriaque
  CROCHON Cécile
  M2 TNSI FA
*/

/* Réservation en mémoire de l'espace nécessaire */
SAC reservation_SAC(int n, int W, int * w, int * c) {
    int i;
    SAC sac;

    sac.n = n;
    sac.W = W;
    sac.c = (int * ) calloc(n, sizeof(int));
    assert(sac.c != NULL);
    sac.w = (int * ) calloc(n, sizeof(int));
    assert(sac.w != NULL);
    sac.x = (int * ) calloc(n, sizeof(int));
    assert(sac.x != NULL);
    for (i = 0; i < n; i++) {
        sac.x[i] = 0;
        sac.w[i] = w[i];
        sac.c[i] = c[i];
    }

    return sac;
}

SAC init_pb(char *filename) {
    FILE * file;
    file = fopen(filename, "r");
    char line[256];
    int i = 0;

    int n;
    int W;
    int c[256];
    int w[256];

    if (file) {
        while (fgets(line, sizeof(line), file)) {
            int j = 0;
            char * strToken = strtok(line, " ");
            while (strToken != NULL) {
                if (i == 0) {
                    if (j == 0) {
                        n = atoi(strToken);
                    } else {
                        W = atoi(strToken);
                    }
                } else if (i == 1) {
                    c[j] = atoi(strToken);
                } else if (i == 2) {
                    w[j] = atoi(strToken);
                }
                strToken = strtok(NULL, " ");
                j++;
            }
            i++;
        }
        fclose(file);
    }

    return reservation_SAC(n, W, c, w);
}

int algo_glouton(SAC sac, int *taken) {
    orderBag(&sac);
    int weight_consumed = 0;
    int gain = 0;
    int i;

    for(i = 0 ; i < sac.n ; i++) {
        if(sac.w[i] + weight_consumed <= sac.W) {
            taken[i] = 1;
            weight_consumed += sac.w[i];
            gain += sac.c[i];
        } else {
            taken[i] = 0;
        }
    }

    return gain;
}

void orderBag(SAC *sac) {
    double ratio[sac->n];
    double interA;
    int interB;
    int interC;
    int i, k;

    for(i = 0 ; i < sac->n ; i++) {
        for(k = (sac->n) -1 ; k > i ; k--) {
            interA = 0;
            interB = 0;
            interC = 0;
            if(ratio[k] > ratio[k-1]) {
                interA = ratio[k];
                ratio[k] = ratio[k-1];
                ratio[k-1] = interA;

                interB = sac->c[k];
                sac->c[k] = sac->c[k-1];
                sac->c[k-1] = interB;

                interC = sac->w[k];
                sac->w[k] = sac->w[k-1];
                sac->w[k-1] = interC;
            }
        }
    }
}

int dynamique(SAC sac, int *taken) {
    int i, j;
    int T[sac.n+1][sac.W+1];

    for(i = 0 ; i <= sac.n ; i++) {
        for(j = 0 ; j <= sac.W ; j++) {
            if (i==0 || j==0) {
               T[i][j] = 0;
            }
            else if (sac.w[i-1] <= j) {
                T[i][j] = max(sac.c[i-1] + T[i-1][j-sac.w[i-1]], T[i-1][j]);
            }
            else {
                T[i][j] = T[i-1][j];
            }
        }
    }

    for(i = sac.n, j = sac.W ; i > 0 ; i--) {
        taken[i-1] = T[i][j] != T[i-1][j];
        if(taken[i-1] == 1) {
            j = j - sac.w[i-1];
        }
    }

    return T[sac.n][sac.W];
}

int max(int a, int b) { return (a > b)? a : b; } 

void freeSac(SAC sac) {
    free(sac.c);
    free(sac.w);
    free(sac.x);
}