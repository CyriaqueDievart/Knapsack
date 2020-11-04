/*
  HUGUES Pierre - THOMAS Roxanne
  M1 TNSI - Groupe apprentis
*/

// Structure de données représentant le problème du sac à dos
typedef struct {
    int n;     /* Nb objets */
    int W;     /* Poids max du sac à dos */
    int *w;    /* Poids de chaque objet */
    int *x;    /* Objet choisi (1 : oui ; 2 : non) */
    int *c;    /* Valeur de l'objet à vendre */
} SAC;

/* Réservation en mémoire de l'espace nécessaire */
SAC reservation_SAC(int n, int W, int * w, int * c);

SAC init_pb(char *filename);

int algo_glouton(SAC sac, int *taken);

void orderBag(SAC *sac);

int max(int val, int val2);

int dynamique(SAC sac, int *taken);

void freeSac(SAC sac);