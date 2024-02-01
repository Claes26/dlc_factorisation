#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>
#define TABLE_SIZE 30
// #include "DivSuccFinal.h" 
//#include "pollardrho.h"


/*
void trial_division(mpz_t n, mpz_t pmax) {
    // Implémentation de la factorisation par divisions successives
    // (Ajoutez votre implémentation ici)
}

void pollard_rho(mpz_t n, double max_time) {
    clock_t start_time, end_time;
    double cpu_time_used;
    
    // Mesurer le temps de début
    start_time = clock();

    // Implémentation de la factorisation rho de Pollard
    // (Ajoutez votre implémentation ici)

    // Mesurer le temps de fin
    end_time = clock();

    // Calculer le temps écoulé en secondes
    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    // Continuer la factorisation jusqu'à ce que le temps maximal soit atteint
    while (cpu_time_used < max_time) {
        // Implémentation de la factorisation rho de Pollard
        // (Ajoutez votre implémentation ici)

        // Mesurer le temps de fin
        end_time = clock();

        // Calculer le temps écoulé en secondes
        cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    }
}

void pollard_p_minus_1(mpz_t n, double max_time) {
    clock_t start_time, end_time;
    double cpu_time_used;

    // Mesurer le temps de début
    start_time = clock();

    // Implémentation de la factorisation (p-1) de Pollard
    // (Ajoutez votre implémentation ici)

    // Mesurer le temps de fin
    end_time = clock();

    // Calculer le temps écoulé en secondes
    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    // Continuer la factorisation jusqu'à ce que le temps maximal soit atteint
    while (cpu_time_used < max_time) {
        // Implémentation de la factorisation (p-1) de Pollard
        // (Ajoutez votre implémentation ici)

        // Mesurer le temps de fin
        end_time = clock();

        // Calculer le temps écoulé en secondes
        cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    }
}
*/


int main() {
    int option;
    mpz_t n;
    mpz_t pmax;
    double max_time;
    char response;

    do {
        // Afficher le menu d'options
        printf("\nMenu des options :\n");
        printf("Tapez 1 pour l'option 1\n");
        printf("Tapez 2 pour l'option 2\n");
        printf("Tapez 3 pour l'option Division Successive\n");
        printf("Tapez 4 pour l'option Rho\n");
        printf("Tapez 5 pour l'option P-1\n");
        printf("Tapez 6 pour l'option Variante P-1\n");
        printf("Tapez 7 pour l'option 7 pour quitter\n");

        // Lire l'option choisie par l'utilisateur
        printf("Choisissez une option : ");
        scanf("%d", &option);

        // Traiter l'option choisie
        switch (option) {
          case 1:
                // Factoriser avec la méthode des divisions successives jusqu'à pmax
       //         trial_division(n, pmax);
                break;
           case 2:
                // Factoriser avec la méthode des divisions successives jusqu'à pmax
          //      trial_division(n, pmax);
                break;
        //  case 3:
                // Factoriser avec la méthode des divisions successives jusqu'à pmax
             //   trial_division(n, pmax);
          //      break;
        
        
        
            case 3:
                // Factoriser avec la méthode des divisions successives jusqu'à pmax
              /*  
             mpz_t tableau[TABLE_SIZE] ; 
	unsigned long int prime_max = 0 ; 
	
	
	    initializeTable(tableau);
	    mpz_t n;  // nombre à factoriser
	    mpz_init(n);
		        
                printf("Entrez le nombre à factoriser : ");
	    gmp_scanf("%Zd", n);
	    printf("Entrer le nombre maximal: ");
	    scanf("%ld", &prime_max);
                
                //divisionSuccessive(n, pmax); //La fonction
                    divisionSuccessive(tableau, n, prime_max);
                
                printf("\n");
                print_tableau(tableau);
	    clearTable(tableau);
	    mpz_clear(n);
		*/        
                break;

            case 4:
                // Factoriser avec la méthode rho de Pollard
                //pollard_rho(n, max_time);
                break;

            case 6:
                // Factoriser avec la méthode (p-1) de Pollard
                /*
                mpz_t tableau[TABLE_SIZE];
	unsigned long int max = 0;
	initializeTable(tableau);
	mpz_t z_number;
	mpz_init(z_number);
	printf("Entrer le nombre à factoriser: \n");
	gmp_scanf("%Zu", z_number);
	printf("Entrer le nombre d'iterations: \n");
	scanf("%ld" ,&max);
	printf("le nombre d'iterations: %ld \n", max);
	decomposition_pollardrho(tableau, z_number, max);
	print_tableau(tableau);
	mpz_clear(z_number);
	clearTable(tableau);
                */
                break;

            case 7:
                // Quitter le programme
                exit(0);

            default:
                printf("Option non valide. Veuillez choisir une option valide.\n");
                continue;
        }

        // Demander si l'utilisateur veut factoriser un autre nombre
        printf("Voulez-vous factoriser un autre nombre ? (1/Oui 2/Non) : ");
        scanf(" %c", &response);

    } while (response == '1');

    // Libérer la mémoire allouée pour n et pmax
    mpz_clear(n);
    mpz_clear(pmax);

    return 0;
}
