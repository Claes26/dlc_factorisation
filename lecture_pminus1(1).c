#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>

#define MAX_LINE_SIZE 500

void pollard_p_minus_1(mpz_t N, unsigned long int B, mpz_t result) 
{
    mpz_t a, g, test1;
    mpz_init(a); //init a
    mpz_init(g); //init g 
    mpz_init(test1); //init test1

    //Choisir un nombre aléatoire a dans l'intervalle [2, N-1] d'abord
    gmp_randstate_t state; //'init' de state
    gmp_randinit_default(state);  //init de l'état de base
    mpz_urandomm(a, state, N); //Genere un nb $ "a" dans [2, N-1]
    mpz_add_ui(a, a, 2);  //on a ajoute à "a"+2 pour qu'il soit bien dans l'intervalle [2, N-1]

    
    mpz_set_ui(result, 1); //init result=1
///////////////////////////////////////////////
    //Méthode (p-1) de Pollard
    for (unsigned long int i = 2; i <= B; i++) 
    {
            mpz_powm_ui(test1, a, i, N); //cal de a^i mod N

        //Màj de "result" avec PGCD ((a^i - 1),N);
        mpz_sub_ui(test1, test1, 1); //Subtraction a^i - 1
        mpz_gcd(g, test1, N); //Calcul PGCD avec N



        if (mpz_cmp_ui(g, 1) != 0 && mpz_cmp(g, N) != 0) //Si PGCD différent de 1 et N => on a trouvé un facteur non-trivial
        {
            mpz_set(result, g);  
            break;
        }
    }
////////////////////////////////////////////////
    mpz_clear(a);
    mpz_clear(g);
    mpz_clear(test1);
    gmp_randclear(state);
}


int main() {
    // Open the input file for reading
    FILE *inputFile = fopen("liste_entiers.txt", "r");

    if (inputFile == NULL) {
        fprintf(stderr, "Error opening input file: liste_entiers.txt\n");
        return 1;  // Exit with an error code
    }

    // Open the output file for writing
    FILE *outputFile = fopen("fichier_testant.txt", "w");

    if (outputFile == NULL) {
        fprintf(stderr, "Error opening output file: fichier_test.txt\n");
        fclose(inputFile);  // Close the input file before exiting
        return 2;  // Exit with an error code
    }

    char line[MAX_LINE_SIZE];
    mpz_t z_number, result, factor2;
	mpz_inits(z_number, result, factor2, NULL);

    while (fgets(line, sizeof(line), inputFile) != NULL) {
        mpz_t firstElement;
        mpz_init(firstElement);
        
        if (gmp_sscanf(line, "%Zd", firstElement) == 1) {
            
		gmp_printf("First element of the line: %Zd \n", firstElement);
		mpz_set(z_number, firstElement);
		clock_t start_time = clock();
		pollard_p_minus_1( z_number, 1000000000, result);
		//pollardRho(result , z_number, 6000000000000);
		mpz_divexact(factor2, z_number, result);
		clock_t end_time = clock();
		gmp_fprintf(outputFile, "%Zu = %Zu * %Zu \n" ,z_number, result, factor2);
		double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
		fprintf(outputFile, "Execution time: %f seconds\n", elapsed_time);
        } else {
            fprintf(stderr, "Error extracting first element from line: %s", line);
        }
        mpz_clear(firstElement);
    }

    fclose(inputFile);
    fclose(outputFile);
    mpz_clears(z_number, result, factor2, NULL);

    return 0; 
}
