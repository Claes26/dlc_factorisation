/////////////////////////////////////////////
//     Ce programme va aller lire un fichier TXT dans le même dossier que le programme ==> ici il s'appelle "NOMBRES.txt"
//      ET VA ECRIRE dans un fichier que l'utilisateur doit créer => TIMES.txt
//////////////////////////////////////////////////

int main()
mpz_t z_number, result;
    mpz_inits(z_number, result, NULL);
    FILE *file;
    FILE *outputFile;
    char line[1024];
    mpz_t N;
    clock_t start_time, end_time;
    double cpu_time_used;


    mpz_init(N); //init le N N=le nombre qui sera lu sur chaque ligne)
	//unsigned long int B=60; 
    file = fopen("NOMBRES.txt", "r"); //ouvre le fichier

    if (file == NULL) { //test si le fichier est vide
        fprintf(stderr, "Impossible d'ouvrir le fichier numbers.txt\n");
        return 1;
    }

    outputFile = fopen("TIMES.txt", "w"); //ouvre le fichier TIMES (pour écrire)

    if (outputFile == NULL) {//test si le fichier est vide
        fprintf(stderr, "Impossible d'ouvrir le fichier times.txt\n");
        fclose(file);
        return 1;
    }
    
    

////////////////////////////////////////////////////////////////////    
   // unsigned long int B=10; 
    start_time = clock(); //TIME - début mesure 
   unsigned long int i ; 
   for (i=10 ; i < 100;  i=i+2) ////////////////////////////////////////////// TON PMAX QUI VA BOUGER A CHAQUE ITERATION 
{

  //printf("test %ld\n", i+1);
  //////////////////////////////////////////////////////////////////////////////
    rewind(file); 
    while (fgets(line, sizeof(line), file)) 
{
        if (line[strlen(line) - 1] == '\n') 
        { //suprimer le saut de ligne
            line[strlen(line) - 1] = '\0';
        }

        mpz_set_str(N, line, 10);//conversion : texte en MPZ_T      

        pollardRho(result, N, i) ; //appli la facto pour chaque ligne
        
      // printf("%u, %Zd, %ld \n", N, result,i);
       end_time = clock(); //TIME - fin de la clock
        cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;  
gmp_printf("where %Zd, %ld \n", N ,i);
         


}
////////////////////////////////////////////////////////////////////
//fprintf(outputFile, "%.10f\n", cpu_time_used); //TIME - écrire le temps   
fprintf(outputFile, "%.10f\n", cpu_time_used); //TIME - écrire le temps   //écrit le temps à fait de facto de list
} //fin du FOR

///fermuture des fichiers 
    fclose(file);
    fclose(outputFile);

//libére la mémoire
    mpz_clear(N);
mpz_clears(z_number, result, NULL);
    return 0;
}
