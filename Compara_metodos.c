/*
Nome: Patrick Pierre Fernandes Ferreira

Data: 27/04/2012
Descrição: Trabalho apresentado ao professor Renato Cota como parte das exigências para
avaliação da disciplina de AEDII, 2º período, consistindo em um programa para comparação
de algoritmos de ordenação.
Data da ultima atualização: 26/04/2012
*/
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
/**************** PROTÓTIPOS DAS FUNÇÕES ****************/
void Criar_vet_Decrescente(int vet[], int n);
void Reiniciar_vet (int *vet, int *pri, int n);
void CalcTime (double SecTime, int *TempoMim, int *TempoSec);
//Metodo de Inserção
void insercao (int vet[], int n, int *comp, int *troc);
//Metodo de Seleção
void selecao (int vet[], int n, int *comp, int *troc);
//Metodo Shellsort
void shellsort (int vet[], int n, int *comp, int *troc);
//Metodo Quicksort
void Particao (int esq, int dir, int *i, int *j, int vet[], int *comp, int *troc);
void Ordena (int esq, int dir, int vet[], int *comp, int *troc);
void QuickSort(int vet[], int n, int *comp, int *troc);
//Metodo Heapsort
void Heapsort(int vet[], int n, int *comp, int *troc);
/**************** PROTÓTIPOS DAS FUNÇÕES ****************/

int main (){
    system("title Comparação entre algoritmos de ordenação");
    int tes, n, i, k, vet[50001], pri[50001], comp=0, troc=0, TempoMim, TempoSec;
    clock_t tInicio, tFim;
    double Tempo;
    FILE * Resultados;
    Resultados = fopen ("Resultados.txt", "w"); //Cria arquivo com permissão de escrita

    srand(time(NULL));

    for (tes=0;tes<3;tes++){
        if (tes==0) n=500;           //fazer os testes com 500 numeros
        if (tes==1) n=5000;          //fazer os testes com 5000 numeros
        if (tes==2) n=50000;         //fazer os testes com 50000 numeros
        for (i=0; i<n; i++){
            vet[i] = rand()%n;       //pegar valores aleatórios para vet[i]
            for (k=0; k<i; k++){     //verificar se o valor já foi inserido antes,
                if(vet[k]==vet[i]){  //no caso de a afirmação ser verdadeira, buscar outro valor randômico
                    vet[i]=rand()%n;
                    k-=1;
                }
            }
        }
        for (i=0;i<n;i++){           //Copia o vetor criado para um outro vetor para poder salvar a condição inicial e realizarmos
            pri[i]=vet[i];           //os testes com a mesma seqüencia numérica
        }

        printf ("\n\nCONJUNTO DE %d REGISTROS:\n", n);              //Imprime na tela
        fprintf (Resultados, "\nCONJUNTO DE %d REGISTROS:\n", n);   //Imprime no arquivo

        /**********Inserção**********/
        //Aleatório
        tInicio=clock();                //Salva o estado inicial do Clock
        insercao(vet, n, &comp, &troc);
        tFim=clock();                   //Salva o estado final do Clock
        Tempo = ((double)(tFim-tInicio))/CLOCKS_PER_SEC; //calcula o tempo gasto em segundos baseado nos pulsos de clock
        CalcTime (Tempo, &TempoMim, &TempoSec);
        printf ("Insercao (aleatorio): tempo de execucao: %d min e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        fprintf (Resultados, "Insercao (aleatorio): tempo de execucao: %d mim e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        //Ordenado
        tInicio=clock();
        insercao(vet, n, &comp, &troc);
        tFim=clock();
        Tempo = ((double)(tFim-tInicio))/CLOCKS_PER_SEC;
        CalcTime (Tempo, &TempoMim, &TempoSec);
        printf ("Insercao (ordenado): tempo de execucao: %d min e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        fprintf (Resultados, "Insercao (ordenado): tempo de execucao: %d mim e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        //Ordenado em ordem decrescente
        Criar_vet_Decrescente(vet, n);
        tInicio=clock();
        insercao(vet, n, &comp, &troc);
        tFim=clock();
        Tempo = ((double)(tFim-tInicio))/CLOCKS_PER_SEC;
        CalcTime (Tempo, &TempoMim, &TempoSec);
        printf ("Insercao (em ordem decrescente): tempo de execucao: %d min e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        fprintf (Resultados, "Insercao (em ordem decrescente): tempo de execucao: %d mim e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        /**********Inserção**********/

        Reiniciar_vet(vet, pri, n); //Reinicia o vetor "vet" para que possa ser testada a mesma sequência para os outros algorítmos de ordenação
        comp=0; troc=0; //Reinicia contador de comparações e trocas

        /**********Seleção**********/
        //Aleatório
        tInicio=clock();
        selecao(vet, n, &comp, &troc);
        tFim=clock();
        Tempo = ((double)(tFim-tInicio))/CLOCKS_PER_SEC;
        CalcTime (Tempo, &TempoMim, &TempoSec);
        printf ("Selecao (aleatorio): tempo de execucao: %d min e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        fprintf (Resultados, "Selecao (aleatorio): tempo de execucao: %d mim e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        //Ordenado
        tInicio=clock();
        selecao(vet, n, &comp, &troc);
        tFim=clock();
        Tempo = ((double)(tFim-tInicio))/CLOCKS_PER_SEC;
        CalcTime (Tempo, &TempoMim, &TempoSec);
        printf ("Selecao (ordenado): tempo de execucao: %d min e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        fprintf (Resultados, "Selecao (ordenado): tempo de execucao: %d mim e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        //Ordenado em ordem decrescente
        Criar_vet_Decrescente(vet, n);
        tInicio=clock();
        selecao(vet, n, &comp, &troc);
        tFim=clock();
        Tempo = ((double)(tFim-tInicio))/CLOCKS_PER_SEC;
        CalcTime (Tempo, &TempoMim, &TempoSec);
        printf ("Selecao (em ordem decrescente): tempo de execucao: %d min e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        fprintf (Resultados, "Selecao (em ordem decrescente): tempo de execucao: %d mim e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        /**********Seleção**********/

        Reiniciar_vet(vet, pri, n);
        comp=0; troc=0;

        /**********Shellsort**********/
        //Aleatório
        tInicio=clock();
        shellsort(vet, n, &comp, &troc);
        tFim=clock();
        Tempo = ((double)(tFim-tInicio))/CLOCKS_PER_SEC;
        CalcTime (Tempo, &TempoMim, &TempoSec);
        printf ("Shellsort (aleatorio): tempo de execucao: %d min e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        fprintf (Resultados, "Shellsort (aleatorio): tempo de execucao: %d mim e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        //Ordenado
        tInicio=clock();
        shellsort(vet, n, &comp, &troc);
        tFim=clock();
        Tempo = ((double)(tFim-tInicio))/CLOCKS_PER_SEC;
        CalcTime (Tempo, &TempoMim, &TempoSec);
        printf ("Shellsort (ordenado): tempo de execucao: %d min e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        fprintf (Resultados, "Shellsort (ordenado): tempo de execucao: %d mim e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        //Ordenado em ordem decrescente
        Criar_vet_Decrescente(vet, n);
        tInicio=clock();
        shellsort(vet, n, &comp, &troc);
        tFim=clock();
        Tempo = ((double)(tFim-tInicio))/CLOCKS_PER_SEC;
        CalcTime (Tempo, &TempoMim, &TempoSec);
        printf ("Shellsort (em ordem decrescente): tempo de execucao: %d min e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        fprintf (Resultados, "Shellsort (em ordem decrescente): tempo de execucao: %d mim e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        /**********Shellsort**********/

        Reiniciar_vet(vet, pri, n);
        comp=0; troc=0;

        /**********Quicksort**********/
        //Aleatório
        tInicio=clock();
        QuickSort(vet, n, &comp, &troc);
        tFim=clock();
        Tempo = ((double)(tFim-tInicio))/CLOCKS_PER_SEC;
        CalcTime (Tempo, &TempoMim, &TempoSec);
        printf ("Quicksort (aleatorio): tempo de execucao: %d min e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        fprintf (Resultados, "Quicksort (aleatorio): tempo de execucao: %d mim e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        //Ordenado
        tInicio=clock();
        QuickSort(vet, n, &comp, &troc);
        tFim=clock();
        Tempo = ((double)(tFim-tInicio))/CLOCKS_PER_SEC;
        CalcTime (Tempo, &TempoMim, &TempoSec);
        printf ("Quicksort (ordenado): tempo de execucao: %d min e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        fprintf (Resultados, "Quicksort (ordenado): tempo de execucao: %d mim e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        //Ordenado em ordem decrescente
        Criar_vet_Decrescente(vet, n);
        tInicio=clock();
        QuickSort(vet, n, &comp, &troc);
        tFim=clock();
        Tempo = ((double)(tFim-tInicio))/CLOCKS_PER_SEC;
        CalcTime (Tempo, &TempoMim, &TempoSec);
        printf ("Quicksort (em ordem decrescente): tempo de execucao: %d min e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        fprintf (Resultados, "Quicksort (em ordem decrescente): tempo de execucao: %d mim e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        /**********Quicksort**********/

        Reiniciar_vet(vet, pri, n);
        comp=0; troc=0;
        /**********Heapsort**********/
        //Aleatório
        tInicio=clock();
        Heapsort(vet, n, &comp, &troc);
        tFim=clock();
        Tempo = ((double)(tFim-tInicio))/CLOCKS_PER_SEC;
        CalcTime (Tempo, &TempoMim, &TempoSec);
        printf ("Heapsort (aleatorio): tempo de execucao: %d min e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        fprintf (Resultados, "Heapsort (aleatorio): tempo de execucao: %d mim e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        //Ordenado
        tInicio=clock();
        Heapsort(vet, n, &comp, &troc);
        tFim=clock();
        Tempo = ((double)(tFim-tInicio))/CLOCKS_PER_SEC;
        CalcTime (Tempo, &TempoMim, &TempoSec);
        printf ("Heapsort (ordenado): tempo de execucao: %d min e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        fprintf (Resultados, "Heapsort (ordenado): tempo de execucao: %d mim e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        //Ordenado em ordem decrescente
        Criar_vet_Decrescente(vet, n);
        tInicio=clock();
        Heapsort(vet, n, &comp, &troc);
        tFim=clock();
        Tempo = ((double)(tFim-tInicio))/CLOCKS_PER_SEC;
        CalcTime (Tempo, &TempoMim, &TempoSec);
        printf ("Heapsort (em ordem decrescente): tempo de execucao: %d min e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        fprintf (Resultados, "Heapsort (em ordem decrescente): tempo de execucao: %d mim e %d seg - comparacoes: %d - trocas: %d\n", TempoMim, TempoSec, comp, troc);
        /**********Heapsort**********/
    }
    getch();
    fclose (Resultados);
    return (0);
}
/**********Outras funções**********/
void Criar_vet_Decrescente(int *vet, int n){
    int k, j;
    for (k = 0, j = n-1; k < n; k++, j--){
        vet[k] = j;
    }
}

void Reiniciar_vet (int *vet, int *pri, int n){ //Função criada para "reiniciar" o vetor, igualando-o ao vetor primário (pri)
    int i;
    for (i=0;i<n;i++){
        vet[i]=pri[i];
    }
}

void CalcTime (double SecTime, int *TempoMim, int *TempoSec){ //Função criada para calcular o tempo colhido, inicialmente em segundos, em minutos e segundos
    *TempoMim = ((int)SecTime)/60;
    *TempoSec = ((int)SecTime)%60;
}
/**********Outras funções**********/

/**********Inserção**********/
//Crescente
void insercao (int vet[], int n, int *comp, int *troc){
    int i, j, x;
    for (i=1;i<n;i++){
        x = vet[i];                          //define um ponto para começarmos a comparar salvando vet[i] na variavel x
        j = i-1;                             //j será a unidade a ser comparada com o i
        vet[n] = x; /*sentinela*/
        (*comp)++;
        while (x < vet[j] && j >= 0){        //desloca os dados para "encaixar" o valor encontrado
            vet[j+1] = vet[j];
            j--;
            (*troc)++;
        }
        vet[j+1] = x;
        (*troc)++;
    }
}

//Decrescente
void insercao_decresc (int vet[], int n, int *comp, int *troc){
    int i, j, x;
    for (i=1;i<n;i++){
        x = vet[i];
        j = i-1;
        vet[n] = x; /*sentinela*/
        (*comp)++;
        while (x > vet[j] && j >= 0){       //Mudança feita: troca do sinal ">" por "<"
            vet[j+1] = vet[j];
            j--;
            (*troc)++;
        }
        vet[j+1] = x;
        (*troc)++;
    }
}

/**********Inserção**********/

/**********Seleção**********/
//Crescente
void selecao (int vet[], int n, int *comp, int *troc){
    int i, j, Min, aux, l;
    for (i=0;i<n;i++){
        for(j=i+1; j<n; j++){
            if (vet[j]<vet[i]){
                aux=vet[j];
                vet[j]=vet[i];
                vet[i]=aux;
                (*troc)++;
            }
            (*comp)++;
        }
    }
}

//Decrescente
void selecao_decresc (int vet[], int n, int *comp, int *troc){
    int i, j, Min, aux, l;
    for (i=0;i<n;i++){
        for(j=i+1; j<n; j++){
            if (vet[j]>vet[i]){             //Mudança feita: troca do sinal ">" por "<"
                aux=vet[j];
                vet[j]=vet[i];
                vet[i]=aux;
                (*troc)++;
            }
            (*comp)++;
        }
    }
}
/**********Seleção**********/

/**********Shellsort**********/
//Crescente
void shellsort (int vet[], int n, int *comp, int *troc){
    int i, j, h=1, x;

    do h = h*3+1; while (h<n); //Calcula o valor total de "h", h=4; h=13; h=40...até que h se torne maior ou igual a "n"
    do{
        h/=3;                  //Divide o valor de h por tres, para assim gerarmos o "salto" inicial da função. Ex.: para n=10, h=4 (13/3=4)
        for (i=h; i<n; i++){   //ou seja, iremos verificar inicialmente as posições 0-4, 1-5, 2-6, 3-7, 4-8, 5-9;
            x=vet[i];
            j=i-h;
            while(j>=0 && vet[j]>x){
                vet[j+h] = vet[j];
                j-=h;
                (*troc)++;
                (*comp)++;
            }                 //Enquanto o h for diferente de 0, essa função irá se repetir. Isso acontecerá quando a divisão de h por tres
            vet[j+h]=x;       //resultar em um valor abaixo de 1. Ex.: h=13; h=4; h=1; h=0.
        }
    }while(h!=0);
}

//Decrescente
void shellsort_decresc (int vet[], int n, int *comp, int *troc){
    int i, j, h=1, x;

    do h = h*3+1; while (h<n);
    do{
        h/=3;
        for (i=h; i<n; i++){
            x=vet[i];
            j=i-h;
            while(j>=0 && vet[j]<x){ //Mudança feita: troca do sinal ">" por "<"
                vet[j+h] = vet[j];
                j-=h;
                (*troc)++;
                (*comp)++;
            }
            vet[j+h]=x;
        }
    }while(h!=0);
}
/**********Shellsort**********/

/**********Quicksort**********/
//Crescente
void Particao (int esq, int dir, int *i, int *j, int vet[], int *comp, int *troc){
    int pivo, aux;
    *i=esq;                             //Como *i será o valor que iremos comparar com os numeros abaixo do pivo, ele recebe esq (inicialmente 0)
    *j=dir;                             //o mesmo acontece com *j
    pivo = vet[(*i+*j)/2];              //Obtem o pivô
    do{
        while (pivo>vet[*i]){           //verifica se os numeros acima do pivô são maiores que ele, enquanto for verdadeiro *i é acrescido
            (*i)++;
            (*comp)++;
        }
        while (pivo<vet[*j]){           //verifica se os numeros abaixo do pivô são menores que ele, enquanto for verdadeiro *j é decrescido
            (*j)--;
            (*comp)++;
        }
        if (*i <= *j){                  //Aqui é realizada a troca entre o elemento vet[*i] e vet[*j]
            aux=vet[*i];
            vet[*i]=vet[*j];
            vet[*j]=aux;
            (*i)++;
            (*j)--;
            (*troc)++;
        }
    } while (*i <= *j);
}

void Ordena (int esq, int dir, int vet[], int *comp, int *troc){
    int i, j;
    Particao (esq, dir, &i, &j, vet, comp, troc);   //Divide o vetor compara das estremidades até encontrar o pivô
    (*comp)++;
    if (esq<j) Ordena (esq, j, vet, comp, troc);    //Forma recursiva de se reiniciar a função particionando o vetor em "vetores menores",
    (*comp)++;                                      //daqui a funcao irá reiniciar a função Ordena, se se fizer necessário
    if (i<dir) Ordena (i, dir, vet, comp, troc);
}

void QuickSort(int vet[], int n, int *comp, int *troc){
    Ordena (0, n, vet, comp, troc);                 //Inicia o processo de ordenação do vetor
}
//Decrescente
void Particao_decresc (int esq, int dir, int *i, int *j, int vet[], int *comp, int *troc){
    int pivo, aux, k;
    *i=esq;
    *j=dir;
    pivo = vet[(*i+*j)/2]; /*OBTEM O PIVÔ*/
    do{
        while (pivo<vet[*i]){                       //Mudança no sinal de ">" para "<"
            (*i)++;
            (*comp)++;
        }
        while (pivo>vet[*j]){                       //Mudança no sinal de "<" para ">"
            (*j)--;
            (*comp)++;
        }
        if (*i <= *j){
            aux=vet[*i];
            vet[*i]=vet[*j];
            vet[*j]=aux;
            (*i)++;
            (*j)--;
            (*troc)++;
        }
    } while (*i < *j);
}

void Ordena_decresc (int esq, int dir, int vet[], int *comp, int *troc){
    int i, j;
    Particao (esq, dir, &i, &j, vet, comp, troc);
    (*comp)++;
    if (esq<j) Ordena (esq, j, vet, comp, troc);
    (*comp)++;
    if (i<dir) Ordena (i, dir, vet, comp, troc);
}

void QuickSort_decresc (int vet[], int n, int *comp, int *troc){
    Ordena (0, n, vet, comp, troc);
}
/**********Quicksort**********/

/**********Heapsort**********/
//Crescente
void Heapsort(int vet[], int n, int *comp, int *troc){
   int i = n/2, pai, filho, t;
   for (;;){
       if (i > 0){
           i--;
           t = vet[i];
        } else {
            n--;
            if (n == 0) return;
            t = vet[n];
            vet[n] = vet[0];
            (*troc)++;
        }
        pai = i;                                                        //Define "pai" como sendo o meio do vetor
        filho = i*2 + 1;
        while (filho < n){
            if ((filho + 1 < n)  &&  (vet[filho + 1] > vet[filho])){
                filho++;
            }
            if (vet[filho] > t) {
                vet[pai] = vet[filho];
                pai = filho;
                filho = pai*2 + 1;
            } else break;
            (*comp)++;
        }
        vet[pai] = t;
    }
}
//Decrescente
void Heapsort_decresc (int vet[], int n, int *comp, int *troc){
   int i = n/2, pai, filho, t;
   for (;;) {
       if (i > 0){
           i--;
           t = vet[i];
        } else {
            n--;
            if (n == 0) return;
            t = vet[n];
            vet[n] = vet[0];
            (*troc)++;
        }
        pai = i;
        filho = i*2 + 1;
        while (filho < n) {
            if ((filho + 1 < n)  &&  (vet[filho + 1] < vet[filho])) filho++; //Troca do sinal ">" por "<"
            if (vet[filho] < t) {
                vet[pai] = vet[filho];
                pai = filho;
                filho = pai*2 + 1;
            } else break;
            (*comp)++;
        }
        vet[pai] = t;
    }
}
/**********Heapsort**********/
