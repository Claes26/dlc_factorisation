#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>

#define TABLE_SIZE 30

void initializeTable(mpz_t *parametre) {
    int i;
    for (i = 0; i < TABLE_SIZE; i++) {
        mpz_init(parametre[i]);
    }
}

void clearTable(mpz_t *parametre) {
    int i;
    for (i = 0; i < TABLE_SIZE; i++) {
        mpz_clear(parametre[i]);
    }
}

void insertValues(mpz_t *parametre, int i, mpz_t z_number) {
    mpz_set(parametre[i], z_number);
}

void addElement(mpz_t *parametre, mpz_t z_element) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (mpz_cmp_ui(parametre[i], 0) == 0) {
            insertValues(parametre, i, z_element);
            break;
        }
    }
}

int isEmpty(mpz_t *parametre) {
    int entries = 0;
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (mpz_cmp_ui(parametre[i], 0) != 0) {
            entries++;
        }
    }
    if (entries != 0)
        return 1;
    else
        return 0;
}

int size(mpz_t *parametre) {
    int entries = 0;
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (mpz_cmp_ui(parametre[i], 0) != 0) {
            entries++;
        }
    }
    return entries;
}

void print_tableau(mpz_t *parametre) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (mpz_cmp_ui(parametre[i], 0) != 0) {
            gmp_printf("%Zd", parametre[i]);
            int count = 1;

            // Compter la puissance du facteur
            while (i + 1 < TABLE_SIZE && mpz_cmp(parametre[i], parametre[i + 1]) == 0) {
                count++;
                i++;
            }

            if (count > 1) {
                printf("^%d", count);
            }

            printf("\n");
        }
    }
}

void pollard_p_minus_1_iteration(mpz_t a, mpz_t n, unsigned long int i) {
    mpz_t temp;
    mpz_init(temp);
    mpz_ui_pow_ui(temp, i, 2);
    mpz_powm(a, a, temp, n);
    mpz_clear(temp);
}

void pollard_p_minus_1(mpz_t *tableau, mpz_t n, unsigned long int max_iter) {
    mpz_t a, g, factor;
    mpz_init(a);
    mpz_init(g);
    mpz_init(factor);

    // Choisir une valeur aléatoire pour a
    gmp_randstate_t state;
    gmp_randinit_default(state);
    mpz_urandomm(a, state, n);

    // Appliquer l'algorithme de Pollard p-1
    // Appliquer l'algorithme de Pollard p-1
for (unsigned long int i = 2; i <= max_iter; ++i) {
    pollard_p_minus_1_iteration(a, n, i);

    mpz_sub_ui(g, a, 1);
    mpz_gcd(factor, g, n);

    if (mpz_cmp_ui(factor, 1) > 0 && mpz_cmp(factor, n) < 0) {
        addElement(tableau, factor);

        // Diviser n par le facteur trouvé
        mpz_divexact(n, n, factor);

        // Réinitialiser a pour une nouvelle itération
        mpz_urandomm(a, state, n);

        // Réinitialiser i pour une nouvelle itération
        i = 1; // Réinitialiser i
    }
    else if (i == max_iter) {
        // Si c'est la dernière itération et aucun facteur n'a été trouvé, ajouter n
        addElement(tableau, n);
    }
}


    // Ajouter le dernier facteur trouvé, s'il y en a un
    if (mpz_cmp_ui(n, 1) > 0 && mpz_cmp(n, factor) != 0) {
        addElement(tableau, n);
    }

    mpz_clear(a);
    mpz_clear(g);
    mpz_clear(factor);
    gmp_randclear(state);
}

int main() {
    // pour stocker le temps d'exécution du code
    double time_spent = 0.0;

    clock_t begin = clock();

    // faire des trucs ici
    mpz_t tableau[TABLE_SIZE];
    unsigned long int max_iter = 1000; // Nombre maximal d'itérations, ajustez selon les besoins
    initializeTable(tableau);
    mpz_t n; // nombre à factoriser
    mpz_init(n);

    printf("Entrez le nombre à factoriser : ");
    gmp_scanf("%Zd", n);

    pollard_p_minus_1(tableau, n, max_iter);

    printf("\n");
    print_tableau(tableau);
    clearTable(tableau);
    mpz_clear(n);

    clock_t end = clock();

    // calcule le temps écoulé en trouvant la différence (end - begin) et
    // divisant la différence par CLOCKS_PER_SEC pour convertir en secondes
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    printf("le temps écoulé est %f seconds \n", time_spent);
    return 0;
}
