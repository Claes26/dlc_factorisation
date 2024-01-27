#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gmp.h"

#define TABLE_SIZE 30


/*ALGORITME:

entrée : un entier n composé qui nest pas une puissance dun nombre premier 
sortie : un facteur non trivial de n ou alors une erreur
Pollard-Rho(n) 
(a, b) := (2, 2) #  on prend x0 = 2 
répéter: 
(a, b) = (f(a), f(f(b))) # f(x) = x^2 + 1
d := pgcd(a-b, n) 
si 1 < d < n 
retourner d 
si d = n erreur
*/

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

void addElement(mpz_t *parametre, mpz_t z_element)
{
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        if(mpz_cmp_ui (parametre[i], 0) == 0)
        {
            insertValues(parametre, i, z_element);
            break;
        }
    }
}

int isEmpty(mpz_t *parametre)
{
    int entries = 0;
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        if(mpz_cmp_ui (parametre[i], 0) != 0)
        {
        	entries++;
        	}
    }
     
    if (entries != 0)
        return 1;
    else
        return 0;
}

int size(mpz_t *parametre)
{
    int entries = 0;
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        if(mpz_cmp_ui (parametre[i], 0) != 0)
        {
        	entries++;
        }
    }
    return entries;
}


void print_tableau(mpz_t *parametre)
{
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        if(mpz_cmp_ui (parametre[i], 0) != 0){
        gmp_printf("%Zd \n",parametre[i]);
        }
    }
}

void pollardRho(mpz_t result, mpz_t z_number, unsigned long int max)
{

	unsigned long int k = 0;
	mpz_t z_a, z_b, z_pgcd, z_ai, z_bi, z_b4, z_ab;
	mpz_inits(z_a, z_b, z_pgcd, z_ai, z_bi, z_b4, z_ab, NULL);
	mpz_set_ui(z_a, 2);
	mpz_set_ui(z_b, 2);
	mpz_set_ui(z_pgcd, 1);

	while (mpz_cmp_ui (z_pgcd, 1) == 0 && k < max) // while z_pgcd == 1 and max iterations is not reached
	{
		mpz_powm_ui (z_ai, z_a, 2, z_number);//z_ai =z_a*z_a
		mpz_add_ui (z_ai, z_ai, 1);//z_ai=z_ai+1
		mpz_set(z_a, z_ai );//z_a= z_ai=z_a*z_a+1
		mpz_mod (z_a, z_a, z_number);//reduce mod z_number

		//calculer z_b = f(f(z_b)) mod z_number
		mpz_powm_ui (z_b4, z_b, 4, z_number);//z_b4 = z_b^4
		mpz_powm_ui (z_bi, z_b, 2, z_number);//z_bi = z_b^2
		mpz_add_ui (z_bi, z_bi, 1);//z_bi = z_b^2+1
		mpz_set(z_b, z_bi);//z_b=z_bi=z_b^2 +1
		mpz_add (z_bi, z_b, z_b);//z_bi = 2*z_b
		mpz_add(z_b, z_b4, z_bi);//z_b = z_b4+z_bi=z_b^4+2*z_b^2+2
		mpz_mod (z_b, z_b, z_number);//reduce mod z_number

		//calculer pgcd(z_a - z_b, z_number) 
		mpz_neg (z_b, z_b);//calculer -z_b
		mpz_add (z_ab, z_a, z_b); //z_a-z_b
		mpz_gcd (z_pgcd, z_ab, z_number);
        k += 1;
	}
	mpz_set(result, z_pgcd);
	mpz_clears(z_a, z_b, z_pgcd, z_ai, z_bi, z_b4, z_ab, NULL);
}


void decompo_deux_facteurs(mpz_t resultat, mpz_t z_number) //décompose un nombre en deux facteurs quelconques
{//cette fonction est vérifiée
	unsigned long int tab_prime[5] = {2, 3, 5, 7, 11}; 
	unsigned long int prime = 0;
	mpz_t z_racine;
	mpz_init(z_racine);
	mpz_sqrt (z_racine, z_number);

	for (int i = 0; i < 5; ++i)
	{
		if (mpz_cmp_ui (z_racine, tab_prime[i]) < 0)
		{
			mpz_set(resultat, z_number);
			break;
		}
		if (mpz_divisible_ui_p (z_number, tab_prime[i]) != 0)
		{
			mpz_set_si(resultat, tab_prime[i]);
			break;
		}

	}
	prime = tab_prime[4] + 2;
	while(mpz_cmp_ui (z_racine, prime) >= 0)
	{
		if (mpz_divisible_ui_p (z_number, prime) != 0)
		{
			mpz_set_si(resultat, prime);
		}
		prime += 2;
	}
	mpz_clear(z_racine);
}

void decomposition_pollardrho(mpz_t *tab_prime, mpz_t z_number, unsigned long int max)//doit renvoyer un tableau contenant la lite dse facteurs primes
{
	int n, i;
	i = 0; n = 0;
	mpz_t z_n, z_fact_1, z_fact_2;
	mpz_inits(z_n, z_fact_1, z_fact_2, NULL);
	mpz_t tab_calcul [TABLE_SIZE];
	initializeTable(tab_calcul);
	insertValues(tab_calcul, 0, z_number);
	
	while(isEmpty(tab_calcul) != 0) //tant que le tab_calcul n'est pas vide
	{
		i++;
		n = size(tab_calcul);
		mpz_set(z_n, tab_calcul[n-1]);
		mpz_set_ui(tab_calcul[n-1], 0);//suppression
		if(mpz_probab_prime_p (z_n, 3) != 0)//verifier que z_n est prime, si oui (z_n est un facteur prime de z_number)
		{
			insertValues(tab_prime, i-1, z_n); //on ajoute à la liste
		}
		else
		{
			pollardRho(z_fact_1, z_n, max);
			mpz_divexact (z_fact_2, z_n, z_fact_1);
			if(mpz_cmp_ui (z_fact_1, 1) == 0 || mpz_cmp_ui (z_fact_2, 1) == 0)//si l'un des facteurs est 1
			{
				//echec: x nest pas 1er mais sa decomposition ne se fait pas 
				// on le passe à la fonction de mélina
	        	//on essaie une décomposition par division
	        	decompo_deux_facteurs(z_fact_1, z_n);
	        	mpz_divexact (z_fact_2, z_n, z_fact_1);
			}

			addElement(tab_calcul, z_fact_1);
			addElement(tab_calcul, z_fact_2);
		}
	}
	
	mpz_clears(z_n, z_fact_1, z_fact_2, NULL);
	clearTable(tab_calcul);
}


int main()
{
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
	return 0;

}
