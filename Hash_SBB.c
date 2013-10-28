#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#define MAX 10
#define TRUE 1
#define FALSE 0
/**############################ DEFINIÇÃO DE TIPOS ###########################**/
//========================= ALUNO ========================
typedef struct {
    int Matricula;
    char Nome[50];
    float Nota;
} TipoItem;

//========================= ARVORE =======================
typedef enum {
    Vertical, Horizontal
} Inclinacao;

typedef struct no* ApontadorNo;

typedef struct no {
    TipoItem Item;
    ApontadorNo Esq, Dir;
    Inclinacao BitE, BitD;
} No;

//========================== HASH =========================
typedef struct DualHash {
    ApontadorNo HashMatriculas[MAX];
    ApontadorNo HashNomes[MAX];
} HashDupla;

/**================ PROTÓTIPOS DE FUNÇÕES =================**/
void head();
void body_MAIN ();
// ========================= HASH ============================
int CalculoPosicao (TipoItem Item);
int CalculoPosicaoNome (TipoItem Item);
//=========================== ARVORE =========================
void DeslocaArvore (ApontadorNo *No);
void EE (ApontadorNo *Ap);
void DD (ApontadorNo *Ap);
void ED (ApontadorNo *Ap);
void DE (ApontadorNo *Ap);
void InicializaArvore (ApontadorNo *Arvore);
void EsqCurto (ApontadorNo *Ap, short *Fim);
void DirCurto (ApontadorNo *Ap, short *Fim);
void Antecessor(ApontadorNo q, ApontadorNo *r, short *Fim);
void IInsereSBBMatricula (TipoItem x, ApontadorNo *Ap, Inclinacao *IAp, short *Fim);
void InsereSBBMatricula (TipoItem x, ApontadorNo *Ap);
void PesquisaSBBMatricula (TipoItem *x, ApontadorNo *p, int *Achou);
void IRetiraSBB (TipoItem x, ApontadorNo *Ap, short *Fim);
void RetiraSBB (TipoItem x, ApontadorNo *Ap);
void IInsereSBBNomes (TipoItem x, ApontadorNo *Ap, Inclinacao *IAp, short *Fim);
void InsereSBBNomes (TipoItem x, ApontadorNo *Ap);
void PesquisaSBBNomes (TipoItem *x, ApontadorNo *p, int *Achou);

/**=================== FUNÇÃO PRINCIPAL ===================**/
int main (){
    int menu, op, x, booleanTest = 1;
    TipoItem Item;
    HashDupla Hash;

    for (x = 0; x < MAX; x++){
        // Inicializando as arvores nas posições das hashs
        InicializaArvore(&Hash.HashMatriculas[x]);
        InicializaArvore(&Hash.HashNomes[x]);
    }

    while (1){
          head();
          body_MAIN();
          scanf ("%d", &menu);
          booleanTest = 1; // Reinicia variavel booleanTest para o próximo ciclo
          
          if (menu == 1){ // Inserção
                   head();
                   printf ("Entre com os dados:\n\n");
                   printf ("\tMatricula: "); scanf ("%d", &Item.Matricula);
                   printf ("\tNome: "); fflush(stdin); gets(Item.Nome);
                   printf ("\tNota: "); scanf ("%f", &Item.Nota);
                   
                   // Inserindo nas Hashs para matriculas e notas:
                   InsereSBBMatricula(Item, &Hash.HashMatriculas[CalculoPosicao(Item)]);
                   InsereSBBNomes(Item, &Hash.HashNomes[CalculoPosicaoNome(Item)]);
        }

        if (menu == 2){ // Alteração
                 head();
                 printf ("Matricula do aluno: ");
                 scanf ("%d", &Item.Matricula);
                 PesquisaSBBMatricula (&Item, &Hash.HashMatriculas[CalculoPosicao(Item)], &booleanTest);
                 printf ("\n\nDeseja realmente alterar os dados de %s?", Item.Nome);
                 printf ("\n\t1. Sim\t2. Nao");
                 scanf ("%d", &op);
                 if (op == 1){
                        RetiraSBB (Item, &Hash.HashMatriculas[CalculoPosicao(Item)]);
                        RetiraSBB (Item, &Hash.HashNomes[CalculoPosicaoNome(Item)]);
                 }
                 head();
                 printf ("Quais dados deseja alterar?\n");
                 printf ("\t1. Matricula\n");
                 printf ("\t2. Nome\n");
                 printf ("\t3. Nota\n");
                 printf ("\t4. Retornar\n\n\t");
                 scanf ("%d", &op);
                 if (op == 1){
                        head();
                        printf ("Entre com a nova matricula: ");
                        scanf ("%d", &Item.Matricula);
                 }
                 if (op == 2){
                        head();
                        printf ("Entre com o nome do aluno: ");
                        fflush(stdin); gets(Item.Nome);
                 }
                 if (op == 3){
                        head();
                        printf ("Entre com a nota do aluno: ");
                        scanf ("%f", &Item.Nota);                        
                 }
                 if (op != 1 && op != 2 && op != 3 && op != 4){
                        printf ("\n\nEscolha invalida!");
                        system ("pause");
                 }
                 InsereSBBMatricula(Item, &Hash.HashMatriculas[CalculoPosicao(Item)]);
                 InsereSBBNomes(Item, &Hash.HashNomes[CalculoPosicaoNome(Item)]);
        }

        if (menu == 3){ // Buscar
                   head();
                   printf ("Tipo de busca:\n");
                   printf ("\t1. Por matricula");
                   printf ("\t2. Por nome\n\n\t");
                   scanf ("%d", &op);
                   if (op != 1 && op != 2){
                                   printf ("\tEntrada invalida!\n\t");
                                   system("pause");                                   
                   }
                   if (op == 1) {
                               head();
                               printf ("Entre com a matricula: ");
                               scanf ("%d", &Item.Matricula);
                               PesquisaSBBMatricula (&Item, &Hash.HashMatriculas[CalculoPosicao(Item)], &booleanTest);     // Pesquisa
                               if (!booleanTest){                                                                          // Variavel booleanTest recebe valor 0 caso o registro não exista
                                                 printf ("\nMatricula não cadastrada!\n\n");
                                                 system("pause");
                                                 } else {
                                                        printf ("\nNome: %s", Item.Nome);
                                                        printf ("\nNota: %f\n\n", Item.Nota);
                                                        system("pause");
                                                        }
                   }
                   if (op == 2) {
                               head();
                               printf ("Entre com o nome: ");
                               fflush (stdin); gets(Item.Nome);
                               PesquisaSBBNomes (&Item, &Hash.HashNomes[CalculoPosicaoNome(Item)], &booleanTest);        //Chama pesquisa por nome
                               if (!booleanTest){                                                                        // Variavel booleanTest recebe valor 0 caso o registro não exista
                                                 printf ("\nAluno não cadastrado!\n\n");
                                                 system("pause");
                                                 } else {
                                                        printf ("\nMatricula: %d", Item.Matricula);
                                                        printf ("\nNota: %f\n\n", Item.Nota);
                                                        system("pause");
                                                 }
                               }
                   }
                   
                   if (menu == 4){ // Retirar
                            head();
                            printf ("Entre com a matricula do aluno: ");
                            scanf ("%d", &Item.Matricula);
                            printf ("\n\n\t%d", &Item.Matricula);
                            PesquisaSBBMatricula (&Item, &Hash.HashMatriculas[CalculoPosicao(Item)], &booleanTest); // Função de busca
                            // A variável booleanTest recebe um valor inteiro como retorno,
                            //caso ela não encontre a Matricula, recebe o valor 0 (false)
                            printf ("\nDeseja apagar o (a) aluno (a) %s?", Item.Nome);
                            printf ("\n\t1. Sim\t2.Nao\n");
                            scanf ("%d", &op);
                            if (op != 1 && op != 2){
                                   printf ("\tEntrada invalida!\n\t");
                                   system("pause");                                   
                            }
                            if (op == 1){
                                   RetiraSBB (Item, &Hash.HashMatriculas[CalculoPosicao(Item)]);
                                   RetiraSBB (Item, &Hash.HashNomes[CalculoPosicaoNome(Item)]);
                            }
                   }
                   if (menu == 5) {
                            head();
                            printf ("Deseja sair do programa?\n");
                            printf ("\t1. Sim\t2.Nao\n\n\t");
                            scanf ("%d", &op);
                            if (op == 1) exit(0);
                            if (op != 1 && op != 2){
                                   printf ("\tEntrada invalida!\n\t");
                                   system("pause");                                   
                            }
                   }

        if (menu!=1 && menu!=2 && menu!=3 && menu!=4 && menu!=5){
            printf ("\tEntrada invalida!\n\t");
            system("pause");
        }
    }
}

void head(){
    system("cls");
    printf ("##====================================================================##\n");
    printf ("##                                                                    ##\n");
    printf ("##                        CADASTRO DE ALUNOS                          ##\n");
    printf ("##                                                                    ##\n");
    printf ("##====================================================================##\n");
    printf ("\n\n");
}

void body_MAIN (){
    printf ("\t1.\tInserir Aluno\n");
    printf ("\t2.\tAltera dados\n");
    printf ("\t3.\tPesquisa\n");
    printf ("\t4.\tRetira Aluno\n");
    printf ("\t5.\tSair");
    printf ("\n\n\t");
}
// ======================== HASH =============================
int CalculoPosicaoNome(TipoItem Item){
    return (atoi(Item.Nome)%MAX);
}

int CalculoPosicao (TipoItem Item){
    return ((Item.Matricula)%MAX);
}
// ==================== ÁRVORE SBB ===========================
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
    q->Item = (*r)->Item;
    q = *r;
    *r = (*r)->Esq;
    free(q);
    if (*r != NULL) *Fim = TRUE;
}

void IInsereSBBMatricula (TipoItem x, ApontadorNo *Ap, Inclinacao *IAp, short *Fim){
    if (*Ap == NULL){
        *Ap = (ApontadorNo) malloc (sizeof(No));
        *IAp = Horizontal;
        (*Ap)->Item = x;
        (*Ap)->BitE = Vertical;
        (*Ap)->BitD = Vertical;
        (*Ap)->Esq = NULL;
        (*Ap)->Dir = NULL;
        *Fim = FALSE;
        return;
    }
    if (x.Matricula < (*Ap)->Item.Matricula){
        IInsereSBBMatricula (x, &(*Ap)->Esq, &(*Ap)->BitE, Fim);
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
    IInsereSBBMatricula (x, &(*Ap)->Dir, &(*Ap)->BitD, Fim);
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

void InsereSBBMatricula (TipoItem x, ApontadorNo *Ap){
    short Fim;
    Inclinacao IAp;
    IInsereSBBMatricula (x, Ap, &IAp, &Fim);
}

void PesquisaSBBMatricula (TipoItem *x, ApontadorNo *p, int *Achou){
    int i;
    if (*p == NULL){
        *Achou = 0;
        return;
    }
    if (x->Matricula < (*p)->Item.Matricula){
        PesquisaSBBMatricula (x, &(*p)->Dir, Achou);
    }
    if (x->Matricula > (*p)->Item.Matricula){
        PesquisaSBBMatricula (x, &(*p)->Dir, Achou);
    }
    if (x->Matricula == (*p)->Item.Matricula){
                     *x = (*p)->Item;
                     return;
    }
}

void IRetiraSBB (TipoItem x, ApontadorNo *Ap, short *Fim){
    No *Aux;
    if (Ap == NULL){
        head();
        printf ("\n\n\tNumero de inscricao invalido!");
        *Fim = TRUE;
        getch();
        return;
    }
    if (x.Matricula > (*Ap)->Item.Matricula){
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

void RetiraSBB (TipoItem x, ApontadorNo *Ap){
    short Fim;
    IRetiraSBB (x, Ap, &Fim);
}

void IInsereSBBNomes (TipoItem x, ApontadorNo *Ap, Inclinacao *IAp, short *Fim){
    if (*Ap == NULL){
        *Ap = (ApontadorNo) malloc (sizeof(No));
        *IAp = Horizontal;
        (*Ap)->Item = x;
        (*Ap)->BitE = Vertical;
        (*Ap)->BitD = Vertical;
        (*Ap)->Esq = NULL;
        (*Ap)->Dir = NULL;
        *Fim = FALSE;
        return;
    }
    if (x.Nota < (*Ap)->Item.Nota){
        IInsereSBBNomes (x, &(*Ap)->Esq, &(*Ap)->BitE, Fim);
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
    IInsereSBBNomes (x, &(*Ap)->Dir, &(*Ap)->BitD, Fim);
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

void InsereSBBNomes (TipoItem x, ApontadorNo *Ap){
    short Fim;
    Inclinacao IAp;
    IInsereSBBNomes (x, Ap, &IAp, &Fim);
}

void PesquisaSBBNomes (TipoItem *x, ApontadorNo *p, int *Achou){
    int i;
    if (*p == NULL){
        head();
        printf ("\n\n\t\tCodigo de candidato nao encontrado!");
        Achou = 0;
        return;
    }
    if (x->Nota < (*p)->Item.Nota){
        PesquisaSBBNomes (x, &(*p)->Dir, Achou);
    }
    if (x->Nota > (*p)->Item.Nota){
        PesquisaSBBNomes (x, &(*p)->Dir, Achou);
    }
}
