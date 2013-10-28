#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#define inicioarranjo 0
#define MAX_ALUNOS 50
#define MAX_DISCIPLINAS 10
//========================= DEFINIÇÃO DE ESTRUTURAS =========================

//=========== ESTRUTURAS UTILIZADAS NA LISTA DE ALUNOS E DISCIPLINAS=========
typedef int TipoApontador;

typedef int TipoChave;

//===================== ESTRUTURAS PARA LISTA DE ALUNOS =====================
typedef struct{
        TipoChave Matricula;
        char Nome[50];
        int Nota;
} TipoAluno;

typedef struct{
        TipoAluno Alunos[MAX_ALUNOS];
        TipoApontador Pri, Ult;
}TipoListaAlunos;

//================== ESTRUTURAS PARA LISTA DE DISCIPLINAS ===================
typedef struct{
        TipoChave Chave;
        char NomeDisc[50];
        TipoListaAlunos ListaAlunos;
}TipoDisc;

typedef struct{
    TipoDisc ItemDisc[MAX_DISCIPLINAS];
    TipoApontador Primeiro, Ultimo;
}TipoLista;

//================================= FUNÇÕES =================================
void titulo (void) {
     system("cls");
     printf ("   ======================================================================\n");
     printf ("   =                              UNIMONTES                             =\n");
     printf ("   ======================================================================\n");
} // Imprime cabeçalho

void FLVazia(TipoLista *Lista){
     Lista->Primeiro = inicioarranjo;
     Lista->Ultimo = Lista->Primeiro;
} // Faz Lista Vazia

void FLAVazia (TipoListaAlunos *Alunos){
     Alunos->Pri = inicioarranjo;
     Alunos->Ult = Alunos->Pri;
} // Faz Lista de Alunos Vazia

int VaziaDisc (TipoLista Lista){
    return(Lista.Primeiro == Lista.Ultimo);
} // Verifica se a lista de disciplinas está vazia

int VaziaAl (TipoListaAlunos Alunos){
    return (Alunos.Pri == Alunos.Ult);
} // Verifica se a lista de alunos está vazia

void InsereAluno (TipoAluno x, TipoListaAlunos *LAlunos){
     if(LAlunos->Ult > MAX_ALUNOS) printf ("Lista cheia\n");
                         else{
                              LAlunos->Alunos[LAlunos->Ult] = x;
                              LAlunos->Ult++;
                              }
} // Insere aluno na lista de alunos (dentro da disciplina)

void InsereDisc (int *aux, TipoDisc x, TipoLista *Lista){
     if(Lista->Ultimo > MAX_DISCIPLINAS) printf("Lista cheia\n");
            else{
                Lista->ItemDisc[Lista->Ultimo] = x;
                *aux = Lista->Ultimo;
                Lista->Ultimo++;
            }
} // Insere disciplina na lista de disciplinas

void ImprimeDisc (TipoLista Lista){
    int aux;
    titulo();
    for (aux = Lista.Primeiro; aux < Lista.Ultimo; aux++){
        printf ("\n\t%d\t%s", Lista.ItemDisc[aux].Chave, Lista.ItemDisc[aux].NomeDisc);
    }
} // Imprime uma relação das disciplinas cadastradas com suas respectivas chaves

void ImprimeAl (TipoListaAlunos LAlunos){
     TipoApontador aux;
     titulo();
     for (aux = LAlunos.Pri; aux < LAlunos.Ult; aux++){
         printf ("\n\t%d\t%s\t%d", LAlunos.Alunos[aux].Matricula, LAlunos.Alunos[aux].Nome, LAlunos.Alunos[aux].Nota);
     }
} // Imprime uma relação de alunos cadastrados na disciplina atualmente selecionada

void RetiraDisc(TipoDisc Item, TipoLista *Lista){
     TipoApontador Aux, Aux2;
     for (Aux = Lista->Primeiro; Aux < Lista->Ultimo; Aux++){
         if (Lista->ItemDisc[Aux].Chave == Item.Chave){
                                        Lista->Ultimo--;
                                        for (Aux2 = Aux; Aux2 < Lista->Ultimo+1; Aux2++)
                                            Lista->ItemDisc[Aux2] = Lista->ItemDisc[Aux2+1];
                                        return;
         }
     }
     titulo();
     printf ("\n\n\tCodigo incorreto!\n");
     system("pause");
} // Retira disciplina

void RetiraAluno (TipoAluno Aluno, TipoListaAlunos *Lista){
     TipoApontador Aux, Aux2;
     titulo();
     for (Aux = Lista->Pri; Aux < Lista->Ult; Aux++){
         if (Lista->Alunos[Aux].Matricula == Aluno.Matricula){
                                          Lista->Ult--;
                                          for (Aux2 = Aux; Aux2 < Lista->Ult+1; Aux2++)
                                              Lista->Alunos[Aux2] = Lista->Alunos[Aux2+1];
                                          return;
         }
     }
     titulo();
     printf ("\n\n\tMatricula incorreta!\n\n\t");
     system ("pause");
} // Retira aluno da disciplina atualmente selecionada

void SelecionaDisc(int *auxret, TipoLista Lista){
                       int aux_cod, aux;
                       ImprimeDisc (Lista);
                       printf ("\n\n\tEntre com o codigo da disciplina: ");
                       scanf ("%d", &aux_cod);
                       for (aux = Lista.Primeiro; aux < Lista.Ultimo; aux++){
                           if (aux_cod == Lista.ItemDisc[aux].Chave){
                                       printf ("\n\n\tDisciplina %s selecionada!\n", Lista.ItemDisc[aux].NomeDisc);
                                       *auxret = aux;
                                       system ("pause");
                                       return;
                           }
                       }
                       printf ("\n\n\tCodigo incorreto!");
} // Seleciona disciplina

//============================ FUNÇÃO PRINCIPAL =============================
int main(){
    int opi, aux = -1, ch = -1;
    TipoApontador Aux;
    TipoDisc Disciplina;
    TipoLista Lista;
    TipoAluno Aluno;

    FLVazia(&Lista);

    for(;;){
        titulo();
        printf ("\n\n\t1. Inserir disciplina");
        printf ("\n\t2. Selecionar disciplina");
        printf ("\n\t3. Inserir aluno");
        printf ("\n\t4. Retirar disciplina");
        printf ("\n\t5. Retirar aluno");
        printf ("\n\t6. Imprimir relacao de alunos na disciplina atual");
        printf ("\n\t7. Sair\n\n\n\t");
        fflush (stdin);
        scanf("%d", &opi);
        switch(opi){
            case 1:
                 titulo ();
                 printf ("\n\tEntre com os dados referentes a disciplina a ser inserida:");
                 printf ("\n\n\tCodigo da disciplina (entre 1001 e 9999): ");
                 scanf ("%d", &Disciplina.Chave);
                 if (Disciplina.Chave <= 1000 || Disciplina.Chave >= 10000){
                                      printf ("\n\n\tChave invalida!\n\n\t");
                                      system ("pause");
                                      break;
                 }
                 printf ("\tDisciplina: ");
                 fflush(stdin);
                 gets (Disciplina.NomeDisc);
                 FLAVazia (&Disciplina.ListaAlunos);
                 InsereDisc(&aux, Disciplina, &Lista);
                 printf ("\n\tDisciplina inserida com sucesso!\n\t");
                 system ("pause");
                 while (ch != 1 && ch != 2){
                       titulo();
                       printf ("\n\tDeseja selecionar a disciplina de '%s'?", Lista.ItemDisc[aux].NomeDisc);
                       printf ("\n\t1. Sim\t\t2. Nao\n\n\t");
                       scanf ("%d", &ch);
                       if (ch == 2) aux = -1;
                       if (ch > 2) printf ("\n\n\tOpcao invalida!\n");
                 }
                 ch = -1;
                 break;
            case 2:
                 if (VaziaDisc (Lista)){
                               titulo();
                               printf ("\n\n\tNao existem disciplinas cadastradas!\n\n\t");
                               system ("pause");
                               break;
                 }
                 SelecionaDisc(&aux, Lista); // Selecionar disciplina na lista de disciplinas
                 break;
            case 3:
                 titulo();
                 if (aux == -1){
                         printf ("\n\n\tDisciplina ainda nao selecionada!\n\n\t");
                         system ("pause");
                         break;
                 }
                 printf ("\n\t%d\t\t%s", Lista.ItemDisc[aux].Chave, Lista.ItemDisc[aux].NomeDisc);
                 printf ("\n\tEntre com os dados referentes ao aluno a ser cadastrado:");
                 printf ("\n\tMatricula (entre 10000 e 99999): ");
                 scanf ("%d", &Aluno.Matricula);
                 if (Aluno.Matricula <= 10000 || Aluno.Matricula >= 99999){
                                      printf ("\n\n\tMatricula invalida!\n\n\t");
                                      system ("pause");
                                      break;
                 }
                 printf ("\tNome: ");
                 fflush(stdin);
                 gets(Aluno.Nome);
                 printf ("\tNota: ");
                 scanf ("%d", &Aluno.Nota);
                 InsereAluno (Aluno, &Lista.ItemDisc[aux].ListaAlunos);
                 break;
            case 4:
                 titulo();
                 if(VaziaDisc(Lista)){
                                      printf("\n\n\tA Lista esta vazia!\n\t");
                                      system("pause");
                                      break;
                 }
                 ImprimeDisc(Lista);
                 printf ("\n\tCodigo da disciplina a ser retirada: ");
                 scanf ("%d", &Disciplina.Chave);
                 RetiraDisc (Disciplina, &Lista);
                 break;
            case 5:
                 titulo();
                 if (VaziaAl(Lista.ItemDisc[aux].ListaAlunos)){
                                                               printf ("\n\n\tNao existem alunos cadastrados na disciplina\n\t");
                                                               system ("pause");
                                                               break;
                 }
                 ImprimeAl (Lista.ItemDisc[aux].ListaAlunos);
                 printf ("\n\n\tEntre com a matricula do aluno: ");
                 scanf ("%d", &Aluno.Matricula);
                 RetiraAluno (Aluno, &Lista.ItemDisc[aux].ListaAlunos);
                 break;
            case 6:
                 titulo();
                 ImprimeAl (Lista.ItemDisc[aux].ListaAlunos);
                 printf ("\n\n\t");
                 system ("pause");
                 break;
            case 7:
                return(0);
            default:
                    printf ("\n\n\tOpcao invalida!\n\n\t");
                    system("pause");
                    break;
        }
    }
}
