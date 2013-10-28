/*
UNIVERSIDADE ESTADUAL DE MONTES CLAROS - UNIMONTES
Centro de Ciências Exatas e Tecnológicas - CCET
Departamento de Ciências da Computação - DCC
Curso de Sistemas de Informação

Professor:  Renato Cota
Acadêmicos: Patrick Pierre
Data:   26/06/2012
Descrição: Trabalho apresentado ao professor Renato Cota como parte das exigências para
avaliação da disciplina de AEDII, 2º período, consistindo em um programa para correção
de provas de concursos.
Data da ultima atualização: 25/06/2012
*/

#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 13
#define TRUE 1
#define FALSE 0
/******************** DEFINICAO DE ESTRUTURAS ********************/
//====================== CANDIDATOS =======================
typedef struct {
    int Cod_Candidato;
    char Nome[50];
    char GabaritoCand[100];
    int Nota;
} TipoCandidato;

typedef struct Celula_Str *Apontador;

typedef struct Celula_Str {
    TipoCandidato Candidato;
    Apontador Prox;
    Apontador Ant;
} Celula_Candidato;

typedef struct {
    Apontador Primeiro, Ultimo;
    int Tamanho;
} TipoLista_Candidatos;
//====================== CONCURSOS =======================
typedef struct {
    int Cod_Concurso;
    char Cargo[30];
    char DataP[10];
    char Promotor[30];
    char Gabarito_Oficial[100];
    int QtdeQuestoes;
    int QtdeVagas;
    TipoLista_Candidatos Lista;
} TipoConcurso;

typedef struct Celula_Str2 *Ponteiro;

typedef struct Celula_Str2 {
    TipoConcurso Concurso;
    Ponteiro Proximo;
    Ponteiro Anterior;
} Celula_Concurso;

typedef struct {
    Ponteiro Pri, Ult;
    int T;
} TipoLista_Concursos;
//====================== TABELA HASH =======================
typedef struct Cel *Indicate;

typedef struct Cel {
    TipoCandidato Cand;
    Indicate Prox;
}Celula_Hash;

//======================= ÁRVORE SBB =======================
typedef enum {
    Vertical, Horizontal
} Inclinacao;

typedef struct no* ApontadorNo;

typedef struct no {
    TipoCandidato Cand;
    ApontadorNo Esq, Dir;
    Inclinacao BitE, BitD;
} No;

/******************** DEFINICAO DE ESTRUTURAS ********************/

/******************** PROTOTIPOS DAS FUNÇÕES  ********************/
//===================  MANIPULAÇÃO DE ESTRUTURA ===================
void InicializaConcursos (TipoLista_Concursos *Concursos);
void InicializaCandidatos (TipoLista_Candidatos *Lista);
void InsereCandidato (TipoLista_Candidatos *Lista, TipoCandidato x);
void InsereConcurso (TipoLista_Concursos *Concursos, TipoConcurso x);
void Retira (TipoLista_Candidatos *Lista, TipoCandidato *x);
void Particao (int esq, int dir, int *i, int *j, TipoLista_Candidatos *Candidatos);
void Ordena (int Esq, int Dir, TipoLista_Candidatos *Candidatos);
void QuickSort (int n, TipoLista_Candidatos *Candidatos);
//========================== TABELA HASH ==========================
void PesquisaHash (TipoCandidato *Cand, TipoLista_Candidatos *HashCand);
int CalculoPosicao (TipoCandidato Cand);
//========================== ÁRVORE SBB ===========================
void DeslocaArvore (ApontadorNo *No);
void EE (ApontadorNo *Ap);
void DD (ApontadorNo *Ap);
void ED (ApontadorNo *Ap);
void DE (ApontadorNo *Ap);
void InicializaArvore (ApontadorNo *Arvore);
void EsqCurto (ApontadorNo *Ap, short *Fim);
void DirCurto (ApontadorNo *Ap, short *Fim);
void Antecessor(ApontadorNo q, ApontadorNo *r, short *Fim);
void IInsereSBB (TipoCandidato x, ApontadorNo *Ap, Inclinacao *IAp, short *Fim);
void InsereSBB (TipoCandidato x, ApontadorNo *Ap);
void PesquisaSBB (TipoCandidato *x, ApontadorNo *p, int QtdeQst, int *Achou);
void IRetiraSBB (TipoCandidato x, ApontadorNo *Ap, short *Fim);
void RetiraSBB (TipoCandidato x, ApontadorNo *Ap);
//======================== OUTRAS FUNÇÕES =========================
void Logo (void);
void Menu (void);
int Lista_ConcursosVazia (TipoLista_Concursos Concursos);
int Lista_CandidatosVazia (TipoLista_Candidatos Lista);
void Imprime_Concursos (TipoLista_Concursos Concursos);
void Imprime_Candidatos (TipoLista_Candidatos Lista, TipoConcurso Conc);
void Imprime_Aprovados (TipoLista_Candidatos Lista, int n, TipoConcurso Conc);
void Selecionar_Concursos (TipoLista_Concursos Concursos, TipoLista_Candidatos *Lista, TipoConcurso *Conc);
int VerificaConcurso (TipoLista_Concursos Concursos, TipoConcurso Conc);
int VaziaLista (TipoLista_Candidatos Lista);
int VaziaConcursos (TipoLista_Concursos Concursos);
void CorrigeProva (TipoConcurso Conc, TipoCandidato *Cand);
//======================== OUTRAS FUNÇÕES =========================
/******************** PROTOTIPOS DAS FUNÇÕES  ********************/

/*********************** FUNÇÃO PRINCIPAL ***********************/
int main (){
    int menu, x, a, ver = 0, posicao, Achou, escolha, ContaCand = 1000;
    char conf;
    TipoLista_Concursos Concursos;
    TipoLista_Candidatos Lista;
    TipoLista_Candidatos HashCand[MAX];
    TipoConcurso Conc;
    TipoCandidato Cand;
    ApontadorNo Arvore;

    InicializaConcursos (&Concursos);
    for (x = 0; x < MAX; x++){
        InicializaCandidatos(&HashCand[x]);
    }
    InicializaArvore(&Arvore);

    for (;;){
        Menu();
        scanf ("%d", &menu);
        if (menu == 1){
            Logo ();
            printf ("\tInsira o codigo do concurso: ");
            scanf ("%d", &Conc.Cod_Concurso);
            if (VerificaConcurso(Concursos, Conc)){
                printf ("\n\n\tCodigo de concurso ja cadastrado!");
                getch ();
                ver = 1;
            }
            if (ver == 0){
                printf ("\tPromotor do concurso: ");
                fflush(stdin);
                gets(Conc.Promotor);
                printf ("\tData de realizacao do concurso: ");
                fflush(stdin);
                gets(Conc.DataP);
                printf ("\tEntre com o cargo para o concurso: ");
                fflush(stdin);
                gets(Conc.Cargo);
                printf ("\tQuantidade de vagas disponiveis: ");
                scanf ("%d", &Conc.QtdeVagas);
                printf ("\tQuantidade de questoes da prova: ");
                scanf ("%d", &Conc.QtdeQuestoes);
                printf ("\n Obs.:\tSomente somente letras minusculas para o cadastro das alternativas são permitidos.");
                for (x = 0; x < Conc.QtdeQuestoes; x++){
                    printf ("\n\t%d. ", x+1);
                    fflush(stdin);
                    scanf ("%c", &conf);
                    if (conf != 'a' && conf != 'b' && conf != 'c' && conf != 'd' && conf != 'e'){
                        printf ("\n\tCaractere invalido!");
                        x--;
                    } else {
                        Conc.Gabarito_Oficial[x] = conf;
                    }
                }
                InicializaCandidatos (&Conc.Lista);
                InsereConcurso(&Concursos, Conc);
                printf ("\n\n\tCadastro realizado com sucesso!");
                getch ();
            }
            ver = 0;
        }
        if (menu == 2){
            Logo();
            if (Lista_ConcursosVazia(Concursos)){
                printf ("\t\tNao existem concursos cadastrados!");
                getch();
            } else {
                Selecionar_Concursos (Concursos, &Lista, &Conc);
            }
        }
        if (menu == 3){
            Logo ();
            ContaCand++;
            if (!VaziaConcursos(Concursos)){
                printf ("\n\tEntre com os dados do candidato a ser inserido\n\n");
                Cand.Cod_Candidato = ContaCand;
                printf ("\tCodigo de cadastro: %d\n", Cand.Cod_Candidato);
                printf ("\tNome: ");
                fflush (stdin);
                gets (Cand.Nome);
                printf ("\tEntre com o gabarito do candidato: \n");
                printf ("Obs.:\tQuestões para as questões que não possuirem respostas, entre com o valor -n-;");
                printf ("\n\tSomente somente letras minusculas para o cadastro das alternativas são permitidos.");
                for (x = 0; x < Conc.QtdeQuestoes; x++){
                    printf ("\n\t%d. ", x+1);
                    fflush(stdin);
                    scanf ("%c", &conf);
                    if (conf != 'a' && conf != 'b' && conf != 'c' && conf != 'd' && conf != 'e' && conf != 'n'){
                        printf ("\n\tCaractere invalido!");
                        x--;
                    } else {
                        Cand.GabaritoCand[x] = conf;
                    }
                }
                CorrigeProva (Conc, &Cand);
                InsereCandidato (&Conc.Lista, Cand);
                posicao = CalculoPosicao (Cand);
                InsereCandidato (&HashCand[posicao], Cand);
                InsereSBB (Cand, &Arvore);
            } else {
                printf ("\tERRO:\tNao existem concursos cadastrados!");
                getch();
            }
        }
        if (menu == 4){
            QuickSort(Conc.Lista.Tamanho, &Conc.Lista);
        }
        if (menu == 5){
            Imprime_Candidatos(Conc.Lista, Conc);
        }
        if (menu == 6){
            printf ("\nCandidatos aprovados no concurso %d:", Conc.Cod_Concurso);
            Imprime_Aprovados (Conc.Lista, Conc.QtdeVagas, Conc);
        }
        if (menu == 7){
            system("cls");
            Logo ();
            printf ("\tEntre com o nome que deseja procurar: ");
            fflush (stdin);
            gets (Cand.Nome);
            PesquisaHash (&Cand, HashCand);
        }
        if (menu == 8){
            Logo();
            printf ("\n\n\tEntre com o codigo do candidato: ");
            scanf ("%d", &Cand.Cod_Candidato);
            PesquisaSBB (&Cand, &Arvore, Conc.QtdeQuestoes, &Achou);
            if (Achou){
                Logo();
                printf ("\tCandidato encontrado!\n");
                printf ("\n\tCodigo:\t%d\n", Cand.Cod_Candidato);
                printf ("\tNome:\t%s\n", Cand.Nome);
                printf ("\tNota:\t%d\n", Cand.Nota);
                printf ("\n\n\tPressione qualquer tecla para retornar.");
                getch();
            }
        }
        if (menu == 9){
            Logo();
            printf ("\n\n\tEntre com o codigo do candidato a ser retirado: ");
            scanf ("%d", &Cand.Cod_Candidato);
            PesquisaSBB (&Cand, &Arvore, Conc.QtdeQuestoes, &Achou);
            if (Achou){
                Logo();
                printf ("\tCandidato encontrado!\n");
                printf ("\n\tCodigo:\t%d\n", Cand.Cod_Candidato);
                printf ("\tNome:\t%s\n", Cand.Nome);
                printf ("\tNota:\t%d\n", Cand.Nota);
                printf ("\n\tDeseja apagar o candidato?");
                printf ("\n\t\t1. Sim\t2. Nao");
                scanf ("%d", &escolha);
                if (escolha == 1){
                    Retira(&Lista, &Cand);
                    RetiraSBB(Cand, &Arvore);
                }
            }
        }
        if (menu == 10){
            Logo();
            printf ("\n\n\tTem certeza que deseja que deseja sair do programa?\n");
            printf ("\t\t1. Sim\t2. Nao\n");
            scanf ("%d", &escolha);
            if (escolha == 1){
                return(0);
            }
        }
        if (menu != 1 && menu != 2 && menu != 3 && menu != 4 && menu != 5 && menu != 6 && menu != 7 && menu != 8 && menu != 9 && menu != 10){
            printf ("Opcao invalida!");
            getch();
        }
    }
}
/*********************** FUNÇÃO PRINCIPAL ***********************/

/*************************** FUNÇÕES ****************************/
//===================  MANIPULAÇÃO DE ESTRUTURA ===================
void InicializaConcursos (TipoLista_Concursos *Concursos){
    Concursos->Pri = (Ponteiro) malloc (sizeof(Celula_Concurso));
    Concursos->Ult = Concursos->Pri;
    Concursos->Pri->Anterior = NULL;
    Concursos->Pri->Proximo = NULL;
    Concursos->T = 0;
} //Inicializa a lista de concursos;

void InicializaCandidatos (TipoLista_Candidatos *Lista){
    Lista->Primeiro = (Apontador) malloc (sizeof(Celula_Candidato));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Ant = NULL;
    Lista->Primeiro->Prox = NULL;
    Lista->Tamanho = 0;
} //Inicializa uma lista de candidatos cadastrados no concurso

void InsereCandidato (TipoLista_Candidatos *Lista, TipoCandidato x){
    Apontador Aux;
    Aux = Lista->Ultimo;
    Lista->Ultimo->Prox = (Apontador) malloc (sizeof(Celula_Candidato));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Candidato = x;
    Lista->Ultimo->Prox = NULL;
    Lista->Tamanho++;
} //Insere candidato na lista de candidatos do concurso cadastrado;

void InsereConcurso (TipoLista_Concursos *Concursos, TipoConcurso x){
    Ponteiro Aux;
    Aux = Concursos->Ult;
    Concursos->Ult->Proximo = (Ponteiro) malloc (sizeof(Celula_Concurso));
    Concursos->Ult = Concursos->Ult->Proximo;
    Concursos->Ult->Concurso = x;
    Concursos->Ult->Proximo = NULL;
    Concursos->T++;
} //Insere concurso na lista de concursos;

void Retira (TipoLista_Candidatos *Lista, TipoCandidato *x){
    Apontador q, Aux;
    Aux = Lista->Primeiro->Prox;
    q = Aux->Prox;
    if (VaziaLista(*Lista)){
        Logo();
        printf ("\n\n\tERRO!\tLista vazia.");
        return;
    }
    while (q!=NULL){
			*x = q->Candidato;
			Aux->Prox = q->Prox;
			if (Aux->Prox == NULL)
				Lista->Ultimo = Aux;
			free(q);
			return;
		q = q->Prox;
		Aux = Aux->Prox;
    }
}

void Particao (int esq, int dir, int *i, int *j, TipoLista_Candidatos *Candidatos){
    Apontador AuxEsq, AuxDir, AuxPivot;
    int Pivot, cont;
    TipoCandidato Cand;
    *i = esq;
    *j = dir;
    AuxEsq = Candidatos->Primeiro->Prox;
    AuxDir = Candidatos->Ultimo;
    AuxPivot = Candidatos->Primeiro->Prox;
    for (cont=0; cont<(*i); cont++){
        AuxEsq = AuxEsq->Prox; //Encontra o apontador na posição i
    }
    for (cont=0; cont>(Candidatos->Tamanho - *j); cont--){
        AuxDir = AuxDir->Ant; //Encontra o apontador na posição i
    }
    Pivot = (*i+*j)/2;
    for (cont=0; cont<Pivot; cont++){
        AuxPivot = AuxPivot->Prox;
    }
    Pivot = AuxPivot->Candidato.Nota;
    do {
        while (Pivot < AuxEsq->Candidato.Nota){
            (*i++);
            AuxEsq = AuxEsq->Prox;
        }
        while (Pivot > AuxDir->Candidato.Nota){
            (*j++);
            AuxDir = AuxDir->Ant;
        }
        if ((*i)<=(*j)){
            Cand = AuxEsq->Candidato;
            AuxEsq->Candidato = AuxDir->Candidato;
            AuxDir->Candidato = Cand;
            (*i)++;
            AuxEsq = AuxEsq->Prox;
            (*j)--;
            AuxDir = AuxDir->Ant;
        }
    } while (*i < *j);
}

void Ordena (int Esq, int Dir, TipoLista_Candidatos *Candidatos){
    int i, j;
    Particao (Esq, Dir, &i, &j, Candidatos);
    if (Esq < j) Ordena (Esq, j, Candidatos);
    if (Dir < i) Ordena (i, Dir, Candidatos);
}

void QuickSort (int n, TipoLista_Candidatos *Candidatos){
    Ordena (1, n, Candidatos);
} //Ordenar os candidatos por nota
//====================== TABELA HASH =======================
void PesquisaHash (TipoCandidato *Cand, TipoLista_Candidatos *HashCand){
    Apontador Aux;
    int i;
    if (VaziaLista(*HashCand)){
        printf ("\n\t\tNao existem itens cadastrados!\n");
        getch();
        return;
    }
    system("cls");
    Logo();
    Aux = HashCand->Primeiro->Prox;
    while (Aux != NULL){
        if (strcmpi(Aux->Candidato.Nome, (*Cand).Nome) == 0){
            printf ("\n\t\tCadastro:\t%d", Aux->Candidato.Cod_Candidato);
            printf ("\n\t\tNome:\t%s", Aux->Candidato.Nome);
            printf ("\n\t\tNota:\t%d", Aux->Candidato.Nota);
            getch();
            return;
        }
        Aux = Aux->Prox;
    }
} //Pesquisa valor na Tabela Hash

int CalculoPosicao (TipoCandidato Cand){
    int i;
    i = atoi(Cand.Nome);
    return (i%MAX);
} //Calcula a posição do item na Hash
//========================== ÁRVORE SBB ===========================
void DeslocaArvore (ApontadorNo *No){
    if ((*No) == NULL) return;
    DeslocaArvore(&((*No)->Esq));
    DeslocaArvore(&((*No)->Dir));
    free(*No);
    return;
}

void EE (ApontadorNo *Ap){
    ApontadorNo Ap1;
    Ap1 = (*Ap)->Esq;
    (*Ap)->Esq = Ap1->Dir;
    Ap1->Dir = *Ap;
    Ap1->BitE = Vertical;
    (*Ap)->BitE = Vertical;
    *Ap = Ap1;
} //Esquerda - Esquerda

void DD (ApontadorNo *Ap){
    ApontadorNo Ap1;
    Ap1 = (*Ap)->Dir;
    (*Ap)->Dir = Ap1->Esq;
    Ap1->Dir = *Ap;
    Ap1->BitD = Vertical;
    (*Ap)->BitD = Vertical;
    *Ap = Ap1;
} //Direita - Direita

void ED (ApontadorNo *Ap){
    ApontadorNo Ap1, Ap2;
    Ap1 = (*Ap)->Esq;
    Ap2 = Ap1->Dir;
    Ap1->BitD = Vertical;
    (*Ap)->BitE = Vertical;
    Ap1->Dir = Ap2->Esq;
    Ap2->Esq = Ap1;
    (*Ap)->Esq = Ap2->Dir;
    Ap2->Dir = *Ap;
    *Ap = Ap2;
} //Esqerda - Direita

void DE (ApontadorNo *Ap){
    ApontadorNo Ap1, Ap2;
    Ap1 = (*Ap)->Dir;
    Ap2 = Ap1->Esq;
    Ap1->BitE = Vertical;
    (*Ap)->BitD = Vertical;
    Ap1->Dir = Ap2->Esq;
    Ap2->Esq = Ap1;
    (*Ap)->Esq = Ap2->Dir;
    Ap2->Dir = *Ap;
    *Ap = Ap2;
} //Direita - Esquerda

void InicializaArvore (ApontadorNo *Arvore){
    *Arvore = NULL;
} //Inicializa uma arvore vazia

void EsqCurto (ApontadorNo *Ap, short *Fim){
    ApontadorNo Ap1;
    if ((*Ap)->BitE == Horizontal){
        (*Ap)->BitE = Vertical;
        *Fim = TRUE;
        return;
    }
    if ((*Ap)->BitD == Horizontal){
        Ap1 = (*Ap)->Dir;
        (*Ap)->Dir = Ap1->Esq;
        Ap1->Esq = *Ap;
        *Ap = Ap1;
        if ((*Ap)->Esq->Dir->BitE == Horizontal){
            DE(&(*Ap)->Esq);
            (*Ap)->BitE = Horizontal;
        }
        *Fim = TRUE;
        return;
    }
    (*Ap)->BitD = Horizontal;
    if ((*Ap)->Dir->BitE == Horizontal){
        DE(Ap);
        *Fim = TRUE;
        return;
    }
    if ((*Ap)->Dir->BitD == Horizontal){
        DD(Ap);
        *Fim == TRUE;
    }
}

void DirCurto (ApontadorNo *Ap, short *Fim){
    ApontadorNo Ap1;
    if ((*Ap)->BitD == Horizontal) {
        (*Ap)->BitD = Vertical;
        *Fim = TRUE;
        return;
    }
    if ((*Ap)->BitE == Horizontal) {
        Ap1 = (*Ap)->Esq;
        (*Ap)->Esq = Ap1->Dir;
        Ap1->Dir = *Ap;
        *Ap = Ap1;
        if ((*Ap)->Dir->Esq->BitD == Horizontal) {
            ED(&(*Ap)->Dir);
            (*Ap)->BitD = Horizontal;
        } else if ((*Ap)->Dir->Esq->BitE == Horizontal) {
            EE(&(*Ap)->Dir);
            (*Ap)->BitD = Horizontal;
        }
        *Fim = TRUE;
        return;
    }
    (*Ap)->BitE = Horizontal;
    if ((*Ap)->Esq->BitD == Horizontal) {
        ED(Ap);
        *Fim = TRUE;
        return;
    }
    if ((*Ap)->Esq->BitE == Horizontal) {
        EE(Ap);
        *Fim = TRUE;
    }
}

void Antecessor(ApontadorNo q, ApontadorNo *r, short *Fim){
    if ((*r)->Dir != NULL) {
        Antecessor(q, &(*r)->Dir, Fim);
        if (!*Fim) DirCurto(r, Fim);
        return;
    }
    q->Cand = (*r)->Cand;
    q = *r;
    *r = (*r)->Esq;
    free(q);
    if (*r != NULL) *Fim = TRUE;
}

void IInsereSBB (TipoCandidato x, ApontadorNo *Ap, Inclinacao *IAp, short *Fim){
    if (*Ap == NULL){
        *Ap = (ApontadorNo) malloc (sizeof(No));
        *IAp = Horizontal;
        (*Ap)->Cand = x;
        (*Ap)->BitE = Vertical;
        (*Ap)->BitD = Vertical;
        (*Ap)->Esq = NULL;
        (*Ap)->Dir = NULL;
        *Fim = FALSE;
        return;
    }
    if (x.Cod_Candidato < (*Ap)->Cand.Cod_Candidato){
        IInsereSBB (x, &(*Ap)->Esq, &(*Ap)->BitE, Fim);
        if (*Fim) return;
        if ((*Ap)->BitE != Horizontal){
            *Fim = TRUE;
            return;
        }
        if ((*Ap)->Esq->BitE == Horizontal){
            EE(Ap);
            *IAp = Horizontal;
        }
        return;
    }
    IInsereSBB (x, &(*Ap)->Dir, &(*Ap)->BitD, Fim);
    if (*Fim) return;
    if ((*Ap)->BitD != Horizontal){
        *Fim = TRUE;
        return;
    }
    if ((*Ap)->Dir->BitD == Horizontal){
        DD(Ap);
        *IAp = Horizontal;
        return;
    }
    if ((*Ap)->Dir->BitE == Horizontal){
        DE(Ap);
        *IAp = Horizontal;
    }
}

void InsereSBB (TipoCandidato x, ApontadorNo *Ap){
    short Fim;
    Inclinacao IAp;
    IInsereSBB (x, Ap, &IAp, &Fim);
}

void PesquisaSBB (TipoCandidato *x, ApontadorNo *p, int QtdeQst, int *Achou){
    int i;
    if (*p == NULL){
        Logo();
        printf ("\n\n\t\tCodigo de candidato nao encontrado!");
        Achou = 0;
        return;
    }
    if (x->Cod_Candidato < (*p)->Cand.Cod_Candidato){
        PesquisaSBB (x, &(*p)->Dir, QtdeQst, Achou);
        return;
    }
    if (x->Cod_Candidato > (*p)->Cand.Cod_Candidato){
        PesquisaSBB (x, &(*p)->Dir, QtdeQst, Achou);
        return;
    }
}

void IRetiraSBB (TipoCandidato x, ApontadorNo *Ap, short *Fim){
    No *Aux;
    if (Ap == NULL){
        Logo();
        printf ("\n\n\tNumero de inscricao invalido!");
        *Fim = TRUE;
        getch();
        return;
    }
    if (x.Cod_Candidato > (*Ap)->Cand.Cod_Candidato){
        IRetiraSBB (x, &(*Ap)->Dir, Fim);
        if (!*Fim) DirCurto(Ap, Fim);
        return;
    }
    *Fim = FALSE;
    Aux  = *Ap;
    if (Aux->Dir == NULL){
        *Ap = Aux->Esq;
        free(Aux);
        if (*Ap != NULL) *Fim = TRUE;
        return;
    }
    if (Aux->Esq == NULL) {
        *Ap = Aux->Dir;
        free(Aux);
        if (*Ap != NULL) *Fim = TRUE;
        return;
    }
    Antecessor(Aux, &Aux->Esq, Fim);
    if (!*Fim) EsqCurto(Ap, Fim); //Encontrou a chave
}
void RetiraSBB (TipoCandidato x, ApontadorNo *Ap){
    short Fim;
    IRetiraSBB (x, Ap, &Fim);
}
//======================== OUTRAS FUNÇÕES =========================
void Logo (void){
    int o;
    system ("cls");
    printf ("  %c", 201);
    for (o=0;o!=72;o++){
        printf ("%c", 205);
    }
    printf ("%c", 187);
    printf ("\n  %c\t\t\t\t\t\t\t\t\t   %c", 186, 186);
    printf ("\n");
    printf ("  %c\t\t\t\t    COTEC\t\t\t\t   %c\n", 186, 186);
    printf ("  %c\t\t\t\t\t\t\t\t\t   %c\n", 186, 186);
    printf ("  %c", 200);
    for (o=0;o!=72;o++){
        printf ("%c", 205);
    }
    printf ("%c\n\n\n", 188);
} //Imprime Logo

void Menu (void){
    Logo();
    printf ("\t1.\tInserir concurso\n");
    printf ("\t2.\tSelecionar concurso\n");
    printf ("\t3.\tInserir candidato\n");
    printf ("\t4.\tProcessar informacoes (ordenar candidatos por nota)\n");
    printf ("\t5.\tCandidatos cadastrados no concurso\n");
    printf ("\t6.\tCandidatos classificados ate o limite de vagas\n");
    printf ("\t7.\tProcurar candidato por nome\n");
    printf ("\t8.\tProcurar candidato por numero de inscricao\n");
    printf ("\t9.\tApagar candidato\n");
    printf ("\t10.\tSair\n");
} //Imprime Menu

int Lista_ConcursosVazia (TipoLista_Concursos Concursos){
    return (Concursos.Pri == Concursos.Ult);
} //Verifica se a lista de concursos está vazia;

int Lista_CandidatosVazia (TipoLista_Candidatos Lista){
    return (Lista.Primeiro == Lista.Ultimo);
} //Verifica se a lista de candidatos está vazia;

void Imprime_Concursos (TipoLista_Concursos Concursos){
    Ponteiro Aux;
    Aux = Concursos.Pri->Proximo;
    while (Aux != NULL){
        printf ("%d\t%s\n", Aux->Concurso.Cod_Concurso, Aux->Concurso.Cargo);
        Aux = Aux->Proximo;
    }
} //Imprime a lista de concursos, constando o codigo do concurso e o cargo;

void Imprime_Candidatos (TipoLista_Candidatos Lista, TipoConcurso Conc){
    Apontador Aux;
    Aux = Lista.Primeiro->Prox;
    Logo();
    printf ("\n\n\tPromotor do concurso:\t%s", Conc.Promotor);
    printf ("\nData em que foi realizado:\t%s", Conc.DataP);
    while (Aux != NULL){
        printf ("%d\t%s\t%d\n", Aux->Candidato.Cod_Candidato, Aux->Candidato.Nome, Aux->Candidato.Nota);
        Aux = Aux->Prox;
    }
    getch();
} // Imprime a lista de candidatos, constando codigos, nomes e notas dos candidatos cadastrados no concurso selecionado;

void Imprime_Aprovados (TipoLista_Candidatos Lista, int n, TipoConcurso Conc){
    Apontador Aux;
    int cont;
    Aux = Lista.Primeiro->Prox;
    Logo();
    printf ("\n\n\tPromotor do concurso:\t%s", Conc.Promotor);
    printf ("\nData em que foi realizado:\t%s", Conc.DataP);
    for (cont = 0; cont<n; cont++){
        printf ("%d\t%s\t%d\n", Aux->Candidato.Cod_Candidato, Aux->Candidato.Nome, Aux->Candidato.Nota);
        Aux = Aux->Prox;
    }
    getch();
} //Imprime lista de candidatos aprovados

void Selecionar_Concursos (TipoLista_Concursos Concursos, TipoLista_Candidatos *Lista, TipoConcurso *Conc){
    int escolha, AuxCod;
    Ponteiro Aux;
    Logo();
    Aux = Concursos.Pri->Proximo;
    printf ("\tDeseja listar os concursos cadastrados?\n");
    printf ("\t\t1. sim\t\t2. nao\n");
    scanf ("%d", &escolha);
    if (escolha == 1) Imprime_Concursos (Concursos);
    printf ("\nEntre com o codigo do concurso: ");
    scanf ("%d", &AuxCod);
    printf ("\n");
    while (Aux != NULL){
        if (AuxCod == Aux->Concurso.Cod_Concurso) break;
        Aux = Aux->Proximo;
    }
    *Conc = Aux->Concurso;
    *Lista = Aux->Concurso.Lista;
} //Seleciona concurso na lista de concursos;

int VerificaConcurso (TipoLista_Concursos Concursos, TipoConcurso Conc){
   Ponteiro Aux;
   Aux = Concursos.Pri->Proximo;
   while (Aux != NULL){
       if (Aux->Concurso.Cod_Concurso == Conc.Cod_Concurso) return (1); //Caso exista o cadastro, retorna "true"
       Aux = Aux->Proximo;
   }
   return (0); //Caso não exista o cadastro, retorna "false"
} //Verifica se o Codigo do concurso a ser inserido já foi cadastrado;

int VaziaLista (TipoLista_Candidatos Lista){
    return (Lista.Primeiro == Lista.Ultimo);
}

int VaziaConcursos (TipoLista_Concursos Concursos){
    return (Concursos.Pri == Concursos.Ult);
} //Verifica se a lista de concursos está vazia;

void CorrigeProva (TipoConcurso Conc, TipoCandidato *Cand){
    int x;
    Cand->Nota = 0;
    for (x = 0; x < Conc.QtdeQuestoes; x++){
        if (Cand->GabaritoCand[x] == Conc.Gabarito_Oficial[x]) (Cand->Nota)+=3;
        if (Cand->GabaritoCand[x] != Conc.Gabarito_Oficial[x] && Cand->GabaritoCand[x] != 'n') (Cand->Nota)--;
    }
    if (Cand->Nota < 0) Cand->Nota = 0;
} //Avalia nota do candidato;

/*************************** FUNÇÕES ****************************/
