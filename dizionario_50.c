/*
    Creare un programma in grado di gestire un dizionario Italiano – Inglese, presente su un
    file di testo. Il programma dovrà mostrare un menù a video con le seguenti funzionalità
    (obbligatorio implementare le funzionalità come sottoprogrammi):
    1. cerca un vocabolo nel dizionario
    2. inserisci un nuovo vocabolo
    Il primo sottoprogramma riceve in ingresso, mediante un parametro, un vocabolo
    italiano di cui si vuole ottenere la traduzione in inglese, legge il file dizionario e nel caso
    in cui venga trovata la parola, riporta a video la traduzione. Il secondo sottoprogramma
    invece riceve in ingresso, mediante due parametri, un nuovo vocabolo italiano e la
    relativa traduzione in inglese, e li salva nel file dizionario (mantenendo le informazioni
    già presenti).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME "files/dizionario.txt"
#define L 100 // lunghezza massima di una frase (sono stufo di usare l'allocazione dinamica)

int stampa_menu(){
    int num;
    system("CLS");
    printf("\n");
    printf(" 1 - Traduci frase o vocabolo\n");
    printf(" 2 - Aggiungi vocabolo alla lista\n");
    printf(" 0 - Esci\n");
    printf("Inserire il numero corrispondente alla scelta: ");
    scanf("%d", &num);
    return num;
}

void add_vocabolo();
void translate();
int esiste_gia(char vocabolo[]);

int main(){
    int scelta = 1;
    printf("Benvenuto nel traduttore farlocco. By Carlo Zambaldo.\n");
    system("PAUSE");
    do{
        scelta = stampa_menu();
        switch(scelta){
            case 1:
                // traduci frase
                translate();
                break;
            case 2:
                // inserisci nuovo vocabolo
                add_vocabolo();
                break;
            case 0:
                printf("Arrivederci.\n");
                break;
            default:
                printf("Errore!!!\n");
                scelta = 0;
                break;
        }
    } while (scelta > 0);
    return 0;
}

int esiste_gia(char vocabolo[]){
    FILE* f_in = fopen(FILE_NAME, "r");
    char cerca[L], cestino[L];

    while(feof(f_in) == 0){    // scorro il file e cerco il vocabolo
        fscanf(f_in, "%s = %s", cerca, cestino);
        if(strcmp(cerca, vocabolo) == 0){
            fclose(f_in);  // -----------------------------------------potrei far ritornare la traduzione
            return 1; // esiste
        }
    }
    return 0; // non esiste
    fclose(f_in);
}

void add_vocabolo(){
    printf("Inserire il vocabolo da aggiungere al dizionario: ");
    char ita[L];
    scanf("%s", ita);
    if(esiste_gia(ita) == 1){
        printf("Attenzione! Il vocabolo %s esiste gia'!\n", ita);
    } else {
        FILE* add = fopen(FILE_NAME, "a");
        if(add == NULL){
            printf("Errore nell'apertura del file. \n");
            system("PAUSE");
            return;
        }
        fprintf(add, "%s =", ita);
        printf("Inserire la traduzione di %s: ", ita);
        scanf("\n%s", ita);
        fprintf(add, " %s\n", ita);
        printf("\nHo salvato la parola. \n");
        fclose(add);
        
    }
    system("PAUSE");
}

void translate(){
    char frase[L];
    int len = 1;
    char cerca[L], traduzione[L], parola[L];
    printf("Inserire la frase da tradurre (ITA > ING): ");
    fgets(frase, L, stdin);fgets(frase, L, stdin);
    len = strlen(frase);
    FILE* dizionario = fopen(FILE_NAME, "r");
    if(dizionario == NULL){
        printf("Errore nell'apertura del dizionario.\n");
        system("PAUSE");
        return;
    }
    printf("La traduzione e': ");
    // scorro tutto il file e cerco parola per parola
    int i, k=0, trovato;
    for(i=0; (i<len && k<L); i++){
        trovato = 0;
        cerca[k] = frase[i];
        k++;
        if(frase[i] == ' ' || frase[i] == '\0' || frase[i] == '\n'){    // se ho finito la parola
            cerca[k-1] = '\0';
            while (feof(dizionario) == 0 && trovato == 0){   // la cerco in tutto il dizionario (finche' non finisce il dizionario)
                fscanf(dizionario, "%s = %s", parola, traduzione);    // parola in italiano = parola in inglese
                // - DEBUG -- printf("%s: %s - %s\n", cerca, parola, traduzione);
                if(strcmp(cerca, parola) == 0){  // se la trovo stampo la sua traduzione
                    printf("%s ", traduzione);
                    trovato++;
                }
            } 
            k=0; // preparo l'indice per prendere una nuova parola
            fseek(dizionario, 0, SEEK_SET);
        }
        
    }
    if(trovato == 0){
        printf("\nNon e' stata trovata una parola nel dizionario. Aggiungerla selezionando 2 dal menu.\n");
    }

    fclose(dizionario);
    printf("\n\n");
    system("PAUSE");   
}
