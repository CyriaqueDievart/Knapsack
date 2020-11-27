#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "type.h"
#include "knapsack.c"

int n;				/* nombre de groupes */
long int b;			/* capacité du sac */
Item *tab;			/* tableau d'objets (premier objet en 0) */
int opt_value = 0;	/* différent de 0 après lecture du fichier si la valeur optimale est fournie */

/* fonction de chargement des données du problème depuis le fichier
    input : le chemin du fichier du problème 
    il y a deux formats qui ne diffère que d'une ligne :
    1ère ligne : n
    2ème ligne : b
    3ème ligne : la valeur optimale du pb. (seulement pour les fichiers *2_*.txt)
    Ensuite le fichier contient les valeur de p (il y en a 3 * n), dans l'ordre des groupes
    Et enfin les valeurs de w (il y en a 3 * n), dans l'ordre des groupes
*/
void charge_donnees(char *name)
{
	int i, l, espace;
	long int value;
	char buffer[256];
	FILE *fp;

	fp = fopen(name, "r");
	assert(fp != NULL);
  /* une façon de vérifier si la valeur optimale est fournie : elle est seule sur la troisième ligne */
	fgets(buffer, 256, fp);
    fgets(buffer, 256, fp);
    fgets(buffer, 256, fp);
    l = 0; value = 0;
    for( ; buffer[l] != '\0' && buffer[l] == ' '; l++) ;
	for ( ; buffer[l] != '\0' && value < 2; l++) {
        espace = 0;
		if (buffer[l] == ' ') {
            value++;
            espace = 1;
            while(buffer[l] != '\0' && buffer[l] == ' ') {
                l++; 
            }
		}
	}
    if(espace == 0) value++;
	rewind(fp);
	fscanf(fp, "%d", &n);
	fscanf(fp, "%ld", &b);
	if(value == 1) fscanf(fp, "%d", &opt_value);	
	tab = (Item *)calloc(n, sizeof(Item));
	assert(tab != NULL);
	for (i = 0; i < n; i++) {
		fscanf(fp, "%d%d%d", &tab[i].p[0], &tab[i].p[1], &tab[i].p[2]);
	}
	for (i = 0; i < n; i++) {
		fscanf(fp, "%d%d%d", &tab[i].w[0], &tab[i].w[1], &tab[i].w[2]);
	}
	fclose(fp);
}

/* fonction de sauvegarde des données dans un fichier (texte) pour vérification
    input : le chemin du fichier dans lequel écrire (ATTENTION : écrase le contenu)
*/
void sauvegarde_donnees(char *name)
{
	int i;
	FILE *fp;

	fp = fopen(name, "w");
	assert(fp != NULL);
	fprintf(fp, "%d %ld\n[%d]\n", n, b, opt_value);
	for (i = 0; i < n; i++) {
		fprintf(fp, "%d %d %d\n", tab[i].p[0], tab[i].p[1], tab[i].p[2]);
	}
	fprintf(fp, "\n");
	for (i = 0; i < n; i++) {
		fprintf(fp, "%d %d %d\n", tab[i].w[0], tab[i].w[1], tab[i].w[2]);
	}
	fclose(fp);
}

int main()
{
    charge_donnees("data/idkp1_1.txt");
    sauvegarde_donnees("verif.txt");
	meta(tab, n, b);
    free(tab);

    /* charge_donnees("idkp2_1.txt");
    sauvegarde_donnees("verif2.txt");
    free(tab); */

    return 0;
}
