#include <stdio.h>
#include <gmp.h>
#include <time.h>      // for time()
#include <unistd.h>    // for sleep()

#ifndef DivSuccFinal_h
#define DivSuccFinal_h

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

void divisionSuccessive(mpz_t *tableau, mpz_t n, unsigned long int prime_max) {
    mpz_t diviseur;
    mpz_init(diviseur);
    mpz_set_ui(diviseur, 2);  // Commencez avec le premier diviseur possible
    while (mpz_cmp_ui(diviseur, prime_max) < 0) {
        // Tant que n n'est pas encore complètement factorisé
        while (mpz_divisible_p(n, diviseur) != 0) {
            // Tant que diviseur est un diviseur de n
            addElement(tableau, diviseur);
            mpz_divexact(n, n, diviseur);  // Divise n par le diviseur
        }

        mpz_nextprime(diviseur, diviseur);  // Passe au prochain nombre premier
    }
    addElement(tableau, n);
    mpz_clear(diviseur);
}
/*
int main() {
// pour stocker le temps d'exécution du code
    double time_spent = 0.0;
    
    clock_t begin = clock();
    
    // faire des trucs ici 
    mpz_t tableau[TABLE_SIZE];
    unsigned long int prime_max = 0;
    initializeTable(tableau);
    mpz_t n;  // nombre à factoriser
    mpz_init(n);
    
    
    printf("Entrez le nombre à factoriser : ");
    gmp_scanf("%Zd", n);
    printf("Entrer le nombre maximal: ");
    scanf("%ld", &prime_max);
   
    divisionSuccessive(tableau, n, prime_max);
   
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
}*/
#endif 
