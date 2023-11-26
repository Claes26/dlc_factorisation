#include <stdio.h>
#include <stdlib.h>

void DivisionSuccessive() {
    //
    printf("Méthode de division successive\n");
}

void RhoPollard() {
    // 
    printf("Méthode rho de Pollard\n");
}

void p_minus_1_Pollard() {
    // 
    printf("Méthode p-1 de Pollard\n");
}

int main() {
    int choix;
    
    do {
        // Le menu
        printf("\nMenu de l'outil de factorisation\n");
        printf("1. Division Successive\n");
        printf("2. Méthode rho de Pollard\n");
        printf("3. Méthode p-1 de Pollard\n");
        printf("4. Quitter\n");

        // Lire le choix de l'utilisateur
        printf("Choisissez une méthode (1-3) ; 4 pour quitter: ");
        scanf("%d", &choix);

        // Exécuter la méthode en fonction du choix
        switch (choix) {
            case 1:
                DivisionSuccessive();
                break;
            case 2:
                RhoPollard();
                break;
            case 3:
                p_minus_1_Pollard();
                break;
            case 4:
                printf("Programme terminé.\n");
                break;
            default:
                printf("Choix non valide. Veuillez entrer un nombre entre 1 et 4.\n");
        }

    } while (choix != 4);

    return 0;
}
