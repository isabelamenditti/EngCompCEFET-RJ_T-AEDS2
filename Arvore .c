#include <stdio.h>
#include <stdlib.h>

typedef struct no{ //definindo a estrutura do nó da árvore RB
    char cor; //será utilizado apenas 1 char: preto(P) ou vermelho(V)
    int id; //o dado a ser armazenado é o número de identificação do cliente
    struct no *esq; //filho da esquerda
    struct no *dir; //filho da direita
    struct no *pai;
}No;

No* CriarArvore(No *ArvoreRB){ //Definindo os dados no nó raiz
    No *raiz = (No *)malloc(sizeof(No));

    ArvoreRB->esq = raiz;
    ArvoreRB->dir = raiz;

    raiz->cor = 'P';
    raiz->id = 0;
    raiz->esq = NULL;
    raiz->dir = NULL;
    raiz->pai = ArvoreRB;

    return(raiz);
}

void BuscaCliente(No *raiz, int n){
    No *x = raiz;

    while(x != NULL){
        if(n == x->id){
            printf("Cliente ID %d ainda encontra-se na fila de espera!\n", n);
            return;
        }
        
        else if(n < x->id)
            x = x->esq;

        else
            x = x->dir;
    }
    printf("Cliente ID %d NÂO encontrado!\n\n", n);

    return;
}

No* Rotacao_RR(No *ArvoreRB, No *x){

    No *aux = x->esq; //ponteiro auxiliar que recebe o filho que provoca o desbalanceamento no nó x

    if(x->pai->esq == x) //caso de rotação simples RR
        x->pai->esq = aux;
    
    else //caso de rotação dupla RL
        x->pai->dir = aux;

    if(x->pai == ArvoreRB) //caso o nó rotacionado seja raiz
        x->pai->dir = aux;

    
    x->esq = aux->dir;
    aux->dir = x;
    aux->pai = x->pai;
    x->pai = aux;

    if(x->esq != NULL) //verificando se a subárvore da esquerda está vazia
        x->esq->pai = x;    
    
    return ArvoreRB;
}

No* Rotacao_LL(No *ArvoreRB, No *x){

    No *aux = x->dir; //ponteiro auxiliar que recebe o filho que provoca o desbalanceamento no nó x

    if(x->pai->dir == x) //caso de rotação simples LL
        x->pai->dir = aux;
    
    else //caso de rotação dupla LR
        x->pai->esq = aux;

    if(x->pai == ArvoreRB) //caso o nó rotacionado seja raiz
        x->pai->esq = aux;

    x->dir = aux->esq;
    aux->esq = x;
    aux->pai = x->pai;
    x->pai = aux;

    if(x->dir != NULL) //verificando se a subárvore da direita está vazia
        x->dir->pai = x;    

    return ArvoreRB;
}

void TrocaCor(No *x){

    if(x->cor == 'V')
        x->cor = 'P';
    else
        x->cor = 'V';

    return;
}

No* FixUP_Insercao(No *ArvoreRB, No* raiz, No* novo){ //Resolvendo os casos 2 e 3 da Inserção
    //2) Pai vermelho e tio vermelho: alteração em loop das cores do pai, do tio e do avô
    //3) Pai vermelho e tio preto: Aplicação de rotações LL, RR, LR ou RL
    No* PaiNovo = novo->pai;
    No* avo = PaiNovo->pai;
    No* tio;

    while(PaiNovo->cor == 'V'){

        if(avo->esq == PaiNovo){ //verificando se o pai do novo é da subárvore da esquerda
            
            tio = avo->dir; //tio pertence a subárvore direita

            if(tio != NULL && tio->cor == 'V'){ //caso 2
                PaiNovo->cor = 'P';
                TrocaCor(tio);
                TrocaCor(avo);
                novo = avo;
                PaiNovo = novo->pai;
                avo = PaiNovo->pai;
                //printf("Troca de cores!\n");
            }

            else{ //caso 3
            
                if(novo == PaiNovo->dir){ //filho esquerda-direita: aplicação de rotação dupla LR
                    //fazer LL
                    ArvoreRB = Rotacao_LL(ArvoreRB, PaiNovo);
                    PaiNovo = novo; //rotação dupla: troca cor do inserido e do avô
                    //printf("LL realizada!\n");
                }
                //fazer RR
                TrocaCor(avo);
                TrocaCor(PaiNovo); //rotação simples: troca cor do pai e do avô
                ArvoreRB = Rotacao_RR(ArvoreRB, avo);
                //printf("RR realizada!\n");

                break;
            }
        }
        
        else{ //pai do novo é da subárvore da direita

            tio = avo->esq;

            if(tio != NULL && tio->cor == 'V'){ //caso 2
                TrocaCor(PaiNovo);
                TrocaCor(tio);
                TrocaCor(avo);

                if(avo != raiz){
                    novo = avo;
                    PaiNovo = novo->pai;
                    avo = PaiNovo->pai;
                }
                //printf("Troca de cores!\n");
            }

            else{ //caso 3
                if(novo == PaiNovo->esq){ //filho direita-esquerda: aplicação de rotação dupla RL
                    //fazer RR
                    ArvoreRB = Rotacao_RR(ArvoreRB, PaiNovo);
                    PaiNovo = novo; //rotação dupla: troca cor do inserido e do avô
                    //printf("RR realizada!\n");
                }
                //fazer LL
                TrocaCor(avo);
                TrocaCor(PaiNovo); //rotação simples: troca cor do pai e do avô
                ArvoreRB = Rotacao_LL(ArvoreRB, avo);
                //printf("LL realizada!\n");

                break;
            }
        }
    }
    raiz = ArvoreRB->esq;
    raiz->cor = 'P'; //raiz deve ser preta sempre

    return raiz;
}

No* InsercaoCliente(No *ArvoreRB, No *raiz, int n){
    No *aux = raiz; //x atuará como um verificador se o nó é o último da subárvore

    if(raiz->id == 0){ //Verificando se a árvore está vazia e esse é o primeiro filho adicionado
        raiz->id = n;
        return raiz;
    }

    No *PaiNovo; //ponteiro para salvar o valor de x antes que ele fique igual a NULL, ou seja, será o pai do novo nó

    while(aux != NULL){ //descendo na árvore para verificar a posição do novo nó inserido
        PaiNovo = aux;

        if(n < aux->id)
            aux = aux->esq;

        else
            aux = aux->dir;
    }

    //Informações do Novo Nó:
    No *novo = (No *)malloc(sizeof(No));
    novo->id = n;
    novo->cor = 'V';
    novo->dir = NULL;
    novo->esq = NULL;
    novo->pai = PaiNovo;
    
    if(n < PaiNovo->id) //Se ele for filho esquerdo
        PaiNovo->esq = novo;

    else //Se ele for filho direito
        PaiNovo->dir = novo;

    //printf("no adicionado: %d %c  |   pai dele: %d %c\n", novo->id, novo->cor, PaiNovo->id, PaiNovo->cor); //Verificação da inserção na árvore binária

    //Casos de inserção, verificação da dor do pai:
    //1) Pai preto: só adicionar o nó sem nenhum problema
    if(PaiNovo->cor == 'P')
        return raiz;

    //2) Pai vermelho e tio vermelho: alteração em loop das cores do pai, do tio e do avô
    //3) Pai vermelho e tio preto: Aplicação de rotações LL, RR, LR ou RL
    raiz = FixUP_Insercao(ArvoreRB, raiz, novo); 
    return raiz;
}

No* FixUP_Remocao(No* ArvoreRB, No* PaiRemovido){ //Resolvendo Problemas de Duplo Preto
    No* raiz = ArvoreRB->esq;
    No* irmao = PaiRemovido->dir; //se o nó for preto, seu irmão não pode ser NULL
    No* PaidoPai = PaiRemovido->pai;
    char CorPai = PaiRemovido->cor;

    //se o lado esquerdo é NULL e o filho dele NÃO é vermelho, o filho só pode ser NULL
    //Remoção de nó preto com filho NULL: PROBLEMAS DE DUPLO PRETO
    
    //CASO DE IRMÃO VERMELHO:
    //Caso 3.1: Remoção de nó preto com irmão vermelho
    if(irmao->cor == 'V'){ //irmão não pode ser NULL, para isso o nó removido deveria ser vermelho
        TrocaCor(PaiRemovido);
        TrocaCor(irmao);
        
        ArvoreRB = Rotacao_LL(ArvoreRB, PaiRemovido);
        ArvoreRB->esq->cor = 'P';

        irmao = PaiRemovido->dir;
    }

    //CASOS DE IRMÃO PRETO:        
    //Caso 3.2: Irmão preto e filhos do irmão NULL
    if((irmao->dir == NULL || irmao->dir->cor == 'P') && (irmao->esq == NULL || irmao->esq->cor == 'P')){
        TrocaCor(irmao);
        TrocaCor(PaiRemovido);;

        if(CorPai == 'P' && PaiRemovido != raiz){ //Subindo com o Duplo Preto
            PaiRemovido->cor = 'P';
            //printf("Subiu DP!\n");
            ArvoreRB = FixUP_Remocao(ArvoreRB, PaidoPai); //Loop ao subir com o Duplo Preto
        }

        return ArvoreRB;
    }

    //Caso 3.3: Remoção de nó com irmão preto e filho da esquerda do irmão vermelho e filho da direita preto ou NULL
    if(irmao->esq != NULL && irmao->esq->cor == 'V' && (irmao->dir == NULL || irmao->dir->cor == 'P')){
        TrocaCor(irmao);
        TrocaCor(irmao->esq);
        ArvoreRB = Rotacao_RR(ArvoreRB, irmao);
    }

    //Caso 3.4: Remoção de nó com irmão preto, filho da esquerda preto ou NULL e filho da direita do irmão vermelho
    PaiRemovido->cor = 'P';
    irmao->cor = CorPai;

    if(irmao->dir != NULL)
        irmao->dir->cor = 'P';

    ArvoreRB = Rotacao_LL(ArvoreRB, PaiRemovido);

    ArvoreRB->esq->cor = 'P'; //Atualizando a cor da raiz

    return ArvoreRB;
}

No* RemocaoCliente(No *ArvoreRB, No *raiz){ //remoção do nó mais à esquerda
    No *k = raiz;

    if(raiz->id == 0){ //verificando se a árvore encontra-se vazia
        //printf("Arvore vazia, nada foi removido!\n");
        return ArvoreRB;
    }

    while(k->esq != NULL) //andando até o nó mais à esquerda
        k = k->esq;

    if(k==raiz && raiz->dir == NULL){ //verificando se a árvore contém apenas o nó raiz
        raiz->id = 0;
        //printf("Raiz removida, arvore agora se encontra vazia!\n");
        return ArvoreRB;
    }
    
    if(k==raiz){ //Raiz é o nó mais à esquerda, mas tem filho à direita
        ArvoreRB->esq = raiz->dir;
        ArvoreRB->dir = raiz->dir;
        raiz->dir->pai = ArvoreRB;
        raiz->dir->cor = 'P';
        raiz = raiz->dir;
        free(k);
        //printf("Raiz removida recebeu seu filho a direita! Raiz: %d\n", raiz->id);
        return ArvoreRB;
    }

    No *filho = k->dir; //filho do nó que está sendo removido
    No *PaiRemovido = k->pai; //pai do nó que está sendo removido
    char CorRemovido = k->cor;

    //Removendo o nó
    PaiRemovido->esq = filho;   
    free(k);
    //printf("No removido com sucesso!\n");
    
    //Caso 1: Remoção de nó vermelho não altera o balanceamento
    if(CorRemovido == 'V') //Caso o nó seja vermelho, ele não possui filhos, ou seja, seus filhos são NULL
        return ArvoreRB;

    //Caso o nó seja preto, obrigatoriamente seu filho é vermelho ou NULL
    //Caso 2: Remoção de nó preto com filho vermelho
    if(filho != NULL && filho->cor == 'V'){ 
        filho->pai = PaiRemovido;
        filho->cor = 'P';
        return ArvoreRB;
    }
    
    //Caso o filho seja NULL, problema Duplo Preto
    ArvoreRB = FixUP_Remocao(ArvoreRB, PaiRemovido);

    return ArvoreRB;
}

void ImpressaoArvore(No *raiz){ //saída em pré-ordem
    
    if(raiz != NULL && raiz->id != 0){
        printf("%d ", raiz->id);
        
        if(raiz->cor == 'V')
            printf("RED\n");

        else
            printf("BLACK\n");

        ImpressaoArvore(raiz->esq); //chamadas recursivas na subárvore esquerda
        ImpressaoArvore(raiz->dir); //chamadas recursivas na subárvore direita
    }
}

int main(){
    No *ArvoreRB = (No *)malloc(sizeof(No)); //criação da Árvore RB
    No *raiz = CriarArvore(ArvoreRB);

    int n;

    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>> ENTRADA <<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    while(scanf("%d", &n) != EOF){
        if(n == -1){
            ArvoreRB = RemocaoCliente(ArvoreRB, raiz); //remoção sempre ocorre no elemento de menor valor, ou seja, o mais à esquerda
            raiz = ArvoreRB->esq;
        }
        /*else if(n ==-2){
            int busca;
            scanf("%d", &busca);
            BuscaCliente(raiz, busca);
        }*/
        else{
            raiz = InsercaoCliente(raiz->pai, raiz, n); //nó inserido deve ser sempre vermelho
            ArvoreRB = raiz->pai;
        }
    }
    //printf("Fila de espera:\n");
    ImpressaoArvore(raiz);

    return EXIT_SUCCESS;
}