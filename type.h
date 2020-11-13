/*
  HUGUES Pierre
  DIEVART Cyriaque
  CROCHON Cécile
  M2 TNSI FA
*/

/* structure pour représenter un objet */
typedef struct {
	int p[3];		/* p[0] = p_{3i}, p[1] = p_{3i+1} and p[2] = p_{3i+2} */
	int w[3];		/* w[0] = w_{3i}, w[1] = w_{3i+1} and w[2] = w_{3i+2} */
} Item;

/* fonction de chargement des données du problème depuis le fichier
    input : le chemin du fichier du problème 
    il y a deux formats qui ne diffère que d'une ligne :
    1ère ligne : n
    2ème ligne : b
    3ème ligne : la valeur optimale du pb. (seulement pour les fichiers *2_*.txt)
    Ensuite le fichier contient les valeur de p (il y en a 3 * n), dans l'ordre des groupes
    Et enfin les valeurs de w (il y en a 3 * n), dans l'ordre des groupes
*/
void charge_donnees(char *name);

/* fonction de sauvegarde des données dans un fichier (texte) pour vérification
    input : le chemin du fichier dans lequel écrire (ATTENTION : écrase le contenu)
*/
void sauvegarde_donnees(char *name);