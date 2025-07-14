/*
UNIVERSIDADE FEDERAL DE SERGIPE
CIDADE UNIVERSITÁRIA PROF. JOSÉ ALOÍSIO DE CAMPOS
CENTRO DE CIÊNCIAS EXATAS E TECNOLOGIA
DEPARTAMENTO DE COMPUTAÇÃO
ENGENHARIA DE COMPUTAÇÃO
COMP0405 - ESTRUTURAS DE DADOS - 2025.1
Turma 02
------------------------------
TRABALHO DA PRIMEIRA UNIDADE
GRUPO 11 - TEMA 12:
------------------------------
Utilizando multilista faça um programa para gerenciamento de times ou equipes em um clube esportivo. 
O programa deve cadastrar as equipes usando uma lista simplesmente 
encadeada de forma que cada equipe aponte para a equipe seguinte. Para cada equipe devem ser cadastrados os 
atletas usando uma lista circular duplamente encadeada. 
Cada atleta deve apontar para o próximo atleta. 
Para cada atleta devem ser guardadas as informações de nome, matrícula, idade, número da camisa e quantidade de faltas. 
Para cada time ou equipe devem ser guardadas as informações nome do time ou equipe, esporte treinado e categoria. 
A categoria diz respeito a idade dos jogadores e devido a grande variedade entre esportes, 
pode ser cadastrada como um string de 30 letras. O sistema deve possuir no mínimo as seguintes funcionalidades:
• Cadastrar equipe
• Cadastrar atleta em equipe
• Remove equipe
• Remover atleta
• Mostrar todas as equipes cadastradas
• Mostrar composição de equipe específica
• Mostrar dados de atleta específico
• Mostrar dados de todos os atletas de determinada categoria
------------------------------
AUTORES:
------------------------------
ÁLEX MATHEUS COLETA SANTOS - 202200014669
ENZO LIBÓRIO FRAGA - 202400028810
LAUREN VICTORIA FERREIRA ROMA - 202200014749
LUIS FELIPE RAMALHO CARVALHO - 202400028955
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para os dados do Time/Equipe
typedef struct gerenciamentoTimes {
    char nome[50];
    char categoria[50];
    char esporte[50];
} Time;

// Estrutura para os dados do Atleta
typedef struct gereciamentoAtletas {
    char nome[50];
    int matricula;
    int idade;
    int numeroDaCamisa;
    int quantDeFaltas;
} Atleta;

// Nó da lista de atletas (circular duplamente encadeada)
typedef struct noAtleta {
    Atleta atleta;
    struct noAtleta *prox;
    struct noAtleta *ant; // O requisito pedia lista simples, mas a estrutura e a lógica usam dupla
} noAtleta;

// Nó da lista de times (simplesmente encadeada)
typedef struct noTime {
    Time time;
    struct noTime *proxTime;
    noAtleta *listaAtletas; // Ponteiro para o início da lista de atletas
} noTime;

// Cabeçalho da lista de times
typedef struct head {
    noTime *refInicio;
    noTime *refFinal;
    int quantidade;
} Head;


/*********************************************************/
/* Função de inicialização            */
/*********************************************************/
// Função para inicializar o cabeçalho
Head *iniciarHead(void) {
    Head *head = (Head*)malloc(sizeof(Head));
    if (head == NULL) {
        printf("Erro ao alocar memória para head.\n");
        return NULL; // Retornar NULL em caso de erro
    }
    head->quantidade = 0;
    head->refInicio = NULL;
    head->refFinal = NULL;
    return head;
}


/*********************************************************/
/* 1. Função para cadastrar equipe            */
/*********************************************************/
void cadastrar_equipe(Head *head) {
    if (head == NULL) {
        printf("Lista não inicializada.\n");
        return;
    }

    noTime *novo = (noTime*)malloc(sizeof(noTime));
    if (novo == NULL) {
        printf("Erro ao alocar a memória para o time.\n");
        return;
    }

    printf("\n\n--- Cadastro de Nova Equipe ---\n");
    printf("Digite o nome da equipe       : ");
    fgets(novo->time.nome, sizeof(novo->time.nome), stdin);
    novo->time.nome[strcspn(novo->time.nome, "\n")] = '\0';

    printf("Digite o esporte da equipe    : ");
    fgets(novo->time.esporte, sizeof(novo->time.esporte), stdin);
    novo->time.esporte[strcspn(novo->time.esporte, "\n")] = '\0';

    printf("Digite a categoria da equipe  : ");
    fgets(novo->time.categoria, sizeof(novo->time.categoria), stdin);
    novo->time.categoria[strcspn(novo->time.categoria, "\n")] = '\0';

    novo->listaAtletas = NULL;
    novo->proxTime = NULL;

    if (head->quantidade == 0) {
        head->refInicio = novo;
        head->refFinal = novo;
    } else {
        head->refFinal->proxTime = novo;
        head->refFinal = novo;
    }

    head->quantidade++;
    printf("\nEquipe cadastrada com sucesso!\n");
}


/*********************************************************/
/* 2. Função para cadastrar atleta em uma equipe            */
/*********************************************************/
void cadastrar_atleta(Head *head) {
    if (head == NULL || head->refInicio == NULL) {
        printf("\nNenhuma equipe cadastrada. Cadastre uma equipe primeiro.\n");
        return;
    }

    char nomeEquipe[50];
    printf("\n\nDigite o nome da equipe para cadastrar o atleta:");
    fgets(nomeEquipe, sizeof(nomeEquipe), stdin);
    nomeEquipe[strcspn(nomeEquipe, "\n")] = '\0';
    char esporte[50];
    printf("\nDigite o esporte da equipe que deseja cadastrar o atleta:");
    fgets(esporte, sizeof(esporte), stdin);
    esporte[strcspn(esporte, "\n")] = '\0';
    char categoria[50];
    printf("\nDigite a categoria da equipe que deseja cadastrar o atleta:");
    fgets(categoria, sizeof(categoria), stdin);
    categoria[strcspn(categoria, "\n")] = '\0';

    // Busca a equipe
    noTime *aux = head->refInicio;
    while (aux != NULL && strcmp(aux->time.nome, nomeEquipe) != 0 && strcmp(aux->time.esporte, esporte) != 0 
    && strcmp(aux->time.categoria, categoria) != 0) {
        aux = aux->proxTime;
    }

    // CORREÇÃO: Verifica se a equipe foi encontrada
    if (aux == NULL) {
        printf("Equipe '%s' não encontrada.\n", nomeEquipe);
        return;
    }

    noAtleta *novoAtleta = (noAtleta*)malloc(sizeof(noAtleta));
    if (novoAtleta == NULL) {
        printf("Erro ao alocar a memória para o atleta.\n");
        return;
    }

    // CORREÇÃO: Pede os dados DEPOIS de encontrar a equipe
    printf("\n--- Cadastro de Novo Atleta em '%s' ---\n", aux->time.nome);

    printf("Digite o nome do atleta                 : ");
    fgets(novoAtleta->atleta.nome, sizeof(novoAtleta->atleta.nome), stdin);
    novoAtleta->atleta.nome[strcspn(novoAtleta->atleta.nome, "\n")] = '\0';

    printf("Digite a matrícula do atleta            : ");
    scanf("%d", &novoAtleta->atleta.matricula);

    printf("Digite a idade do atleta                : ");
    scanf("%d", &novoAtleta->atleta.idade);

    printf("Digite o número da camisa do atleta     : ");
    scanf("%d", &novoAtleta->atleta.numeroDaCamisa);

    printf("Digite a quantidade de faltas do atleta : ");
    scanf("%d", &novoAtleta->atleta.quantDeFaltas);
    getchar(); // Limpar o buffer do teclado

    novoAtleta->prox = novoAtleta->ant = NULL;

    // Inserção na lista circular de atletas
    if (aux->listaAtletas == NULL) { // Primeiro atleta da equipe
        novoAtleta->prox = novoAtleta;
        novoAtleta->ant = novoAtleta;
        aux->listaAtletas = novoAtleta;
    } else { // Equipe já possui atletas
        noAtleta *ultimo = aux->listaAtletas->ant;

        novoAtleta->prox = aux->listaAtletas;
        novoAtleta->ant = ultimo;
        ultimo->prox = novoAtleta;
        aux->listaAtletas->ant = novoAtleta;
        // Opcional: inserir no início (como estava) ou no fim. Mantido no início.
        aux->listaAtletas = novoAtleta;
    }
    printf("\nAtleta cadastrado com sucesso!\n");
}


/**********************************************************/
/* 3. Função para remover uma equipe                  */
/*********************************************************/
void remover_equipe(Head *head) {
    if (head == NULL || head->refInicio == NULL) {
        printf("\nNenhuma equipe cadastrada para remover.\n");
        return;
    }

     char nomeEquipe[50];
    printf("\n\nDigite o nome da equipe para cadastrar o atleta:");
    fgets(nomeEquipe, sizeof(nomeEquipe), stdin);
    nomeEquipe[strcspn(nomeEquipe, "\n")] = '\0';
    char esporte[50];
    printf("\nDigite o esporte da equipe que deseja cadastrar o atleta:");
    fgets(esporte, sizeof(esporte), stdin);
    esporte[strcspn(esporte, "\n")] = '\0';
    char categoria[50];
    printf("\nDigite a categoria da equipe que deseja cadastrar o atleta:");
    fgets(categoria, sizeof(categoria), stdin);
    categoria[strcspn(categoria, "\n")] = '\0';

    // Busca a equipe
    noTime *aux = head->refInicio;
    noTime *anterior = NULL;
    while (aux != NULL && strcmp(aux->time.nome, nomeEquipe) != 0 && strcmp(aux->time.esporte, esporte) != 0 
    && strcmp(aux->time.categoria, categoria) != 0) {
        anterior = aux;
        aux = aux->proxTime;
    }


    if (aux == NULL) {
        printf("\nEquipe '%s' não encontrada.\n", nomeEquipe);
        return;
    }

    // Antes de remover a equipe, liberar a memória de todos os seus atletas
    if (aux->listaAtletas != NULL) {
        noAtleta *atletaaux = aux->listaAtletas;
        noAtleta *atletaRemover;
        
        // Quebra a circularidade para facilitar a remoção
        atletaaux->ant->prox = NULL; 

        while (atletaaux != NULL) {
            atletaRemover = atletaaux;
            atletaaux = atletaaux->prox;
            free(atletaRemover);
        }
        printf("Todos os atletas da equipe '%s' foram removidos.\n", nomeEquipe);
    }

    // Agora, remove a equipe da lista de equipes
    if (anterior == NULL) { // A equipe a ser removida é a primeira da lista
        head->refInicio = aux->proxTime;
        if (head->refInicio == NULL) { // Se era a única equipe
            head->refFinal = NULL;
        }
    } else { // A equipe está no meio ou no fim
        anterior->proxTime = aux->proxTime;
        if (aux->proxTime == NULL) { // Se a equipe era a última
            head->refFinal = anterior;
        }
    }
    
    free(aux); // Libera o nó da equipe
    head->quantidade--;
    printf("\nEquipe '%s' removida com sucesso!\n", nomeEquipe);
}


/**********************************************************/
/* 4. Função para remover um atleta de uma equipe         */
/*********************************************************/
void remover_atleta(Head *head) {
    if (head == NULL || head->refInicio == NULL) {
        printf("\nNenhuma equipe cadastrada.\n");
        return;
    }

    char nomeEquipe[50];
    printf("\n\nDigite o nome da equipe para cadastrar o atleta:");
    fgets(nomeEquipe, sizeof(nomeEquipe), stdin);
    nomeEquipe[strcspn(nomeEquipe, "\n")] = '\0';
    char esporte[50];
    printf("\nDigite o esporte da equipe que deseja cadastrar o atleta:");
    fgets(esporte, sizeof(esporte), stdin);
    esporte[strcspn(esporte, "\n")] = '\0';
    char categoria[50];
    printf("\nDigite a categoria da equipe que deseja cadastrar o atleta:");
    fgets(categoria, sizeof(categoria), stdin);
    categoria[strcspn(categoria, "\n")] = '\0';

    // Busca a equipe
    noTime *aux = head->refInicio;
    while (aux != NULL && strcmp(aux->time.nome, nomeEquipe) != 0 && strcmp(aux->time.esporte, esporte) != 0 
    && strcmp(aux->time.categoria, categoria) != 0) {
        aux = aux->proxTime;
    }


    if (aux == NULL) {
        printf("Equipe '%s' não encontrada.\n", nomeEquipe);
        return;
    }

    if (aux->listaAtletas == NULL) {
        printf("A equipe '%s' não possui atletas cadastrados.\n", nomeEquipe);
        return;
    }

    char nomeAtleta[50];
    printf("Digite a nome do atleta a ser removido: ");
    fgets(nomeAtleta, sizeof(nomeAtleta), stdin);
    nomeAtleta[strcspn(nomeAtleta, "\n")] = '\0';

    int matriculaAtleta;
    printf("Digite a matrícula do atleta a ser removido: ");
    scanf("%d", &matriculaAtleta);
    getchar();
  

    noAtleta *atletaaux = aux->listaAtletas;
    noAtleta *atletaRemover = NULL;

    // Procura o atleta na lista circular
    noAtleta *inicio = atletaaux;
    do {
        if (atletaaux->atleta.nome == nomeAtleta && atletaaux->atleta.matricula == matriculaAtleta) {
            atletaRemover = atletaaux;
            break;
        }
        atletaaux = atletaaux->prox;
    } while (atletaaux != inicio);

    if (atletaRemover == NULL) {
        printf("\nAtleta com matrícula %d não encontrado na equipe '%s'.\n", matriculaAtleta, nomeEquipe);
        return;
    }

    // Lógica de remoção da lista circular duplamente encadeada
    if (atletaRemover->prox == atletaRemover) { // É o único atleta na lista
        aux->listaAtletas = NULL;
    } else {
        noAtleta *anterior = atletaRemover->ant;
        noAtleta *proximo = atletaRemover->prox;
        
        anterior->prox = proximo;
        proximo->ant = anterior;

        // Se o atleta a ser removido era o "início" da lista, auxiza o ponteiro
        if (aux->listaAtletas == atletaRemover) {
            aux->listaAtletas = proximo;
        }
    }
    
    printf("\nAtleta '%s' (matrícula %d) removido da equipe '%s' com sucesso!\n", atletaRemover->atleta.nome, atletaRemover->atleta.matricula, nomeEquipe);
    free(atletaRemover);
}


/**********************************************************/
/* 5. Função para exibir todas as equipes                   */
/**********************************************************/
void exibir_equipes(Head *head) {
    if (head == NULL || head->refInicio == NULL) {
        printf("\nNenhuma equipe cadastrada.\n");
        return;
    }

    noTime *aux = head->refInicio;
    printf("\n--- Todas as Equipes Cadastradas ---\n\n");
    int i = 1;
    while (aux != NULL) {
        printf("------ Equipe %d ------\n", i++);
        printf("Nome da equipe      : %s\n", aux->time.nome);
        printf("Esporte da equipe   : %s\n", aux->time.esporte);
        printf("Categoria da equipe : %s\n\n", aux->time.categoria);
        aux = aux->proxTime;
    }
}


/****************************************************************/
/* 6. Função para exibir a composição de uma equipe específica   */
/****************************************************************/
void exibir_equipe_especifica(Head *head) {
    if (head == NULL || head->refInicio == NULL) {
        printf("\nNenhuma equipe cadastrada.\n");
        return;
    }
    
     char nomeEquipe[50];
    printf("\n\nDigite o nome da equipe para cadastrar o atleta:");
    fgets(nomeEquipe, sizeof(nomeEquipe), stdin);
    nomeEquipe[strcspn(nomeEquipe, "\n")] = '\0';
    char esporte[50];
    printf("\nDigite o esporte da equipe que deseja cadastrar o atleta:");
    fgets(esporte, sizeof(esporte), stdin);
    esporte[strcspn(esporte, "\n")] = '\0';
    char categoria[50];
    printf("\nDigite a categoria da equipe que deseja cadastrar o atleta:");
    fgets(categoria, sizeof(categoria), stdin);
    categoria[strcspn(categoria, "\n")] = '\0';

    noTime *aux = head->refInicio;
    while (aux != NULL && strcmp(aux->time.nome, nomeEquipe) != 0 && strcmp(aux->time.esporte, esporte) != 0 
    && strcmp(aux->time.categoria, categoria) != 0) {
        aux = aux->proxTime;
    }

    if (aux == NULL) {
        printf("Equipe '%s' não encontrada.\n", nomeEquipe);
        return;
    }

    noAtleta *auxAtleta = aux->listaAtletas;
    if (auxAtleta == NULL) {
        printf("\nNão há atletas cadastrados na equipe '%s'.\n", nomeEquipe);
        return;
    }

    printf("\n--- Atletas da Equipe: %s ---\n", aux->time.nome);
    printf("-------------------------------------------\n");
    
    noAtleta *inicio = auxAtleta;
    do {
        printf("Nome: %s | Matrícula: %d\n", auxAtleta->atleta.nome, auxAtleta->atleta.matricula);
        auxAtleta = auxAtleta->prox;
    } while (auxAtleta != inicio);
    printf("-------------------------------------------\n");
}


/****************************************************************/
/* 7. Função para mostrar dados de atleta;  */
/****************************************************************/
void mostrar_dados_atleta_especifico(Head *head) {
    if (head == NULL || head->refInicio == NULL) {
        printf("\nNenhuma equipe cadastrada. Não é possível buscar atletas.\n");
        return;
    }

    char nomeEquipe[50], esporte[50], categoria[50];
    printf("\n\nDigite o nome da equipe: ");
    fgets(nomeEquipe, sizeof(nomeEquipe), stdin);
    nomeEquipe[strcspn(nomeEquipe, "\n")] = '\0';

    printf("Digite o esporte da equipe: ");
    fgets(esporte, sizeof(esporte), stdin);
    esporte[strcspn(esporte, "\n")] = '\0';

    printf("Digite a categoria da equipe: ");
    fgets(categoria, sizeof(categoria), stdin);
    categoria[strcspn(categoria, "\n")] = '\0';

    // Busca da equipe
    noTime *aux = head->refInicio;
    while (aux != NULL &&
          strcmp(aux->time.nome, nomeEquipe) != 0 &&
           strcmp(aux->time.esporte, esporte) != 0 &&
           strcmp(aux->time.categoria, categoria) != 0) {
        aux = aux->proxTime;
    }

    if (aux == NULL) {
        printf("Equipe não encontrada.\n");
        return;
    }

    if (aux->listaAtletas == NULL) {
        printf("A equipe não possui atletas cadastrados.\n");
        return;
    }

    char nomeAtleta[50];
    int matriculaAtleta;
    printf("Digite o nome do atleta: ");
    fgets(nomeAtleta, sizeof(nomeAtleta), stdin);
    nomeAtleta[strcspn(nomeAtleta, "\n")] = '\0';

    printf("Digite a matrícula do atleta: ");
    scanf("%d", &matriculaAtleta);
    getchar(); // Limpar o buffer

    noAtleta *atletaaux = aux->listaAtletas;
    noAtleta *inicio = atletaaux;
    noAtleta *atletaEncontrado = NULL;

    do {
        if (strcmp(atletaaux->atleta.nome, nomeAtleta) == 0 &&
            atletaaux->atleta.matricula == matriculaAtleta) {
            atletaEncontrado = atletaaux;
            break;
        }
        atletaaux = atletaaux->prox;
    } while (atletaaux != inicio);

    if (atletaEncontrado != NULL) {
        printf("\n--- Dados do Atleta (Matrícula: %d) ---\n", matriculaAtleta);
        printf("Nome: %s\n", atletaEncontrado->atleta.nome);
        printf("Matrícula: %d\n", atletaEncontrado->atleta.matricula);
        printf("Idade: %d\n", atletaEncontrado->atleta.idade);
        printf("Número da Camisa: %d\n", atletaEncontrado->atleta.numeroDaCamisa);
        printf("Quantidade de Faltas: %d\n", atletaEncontrado->atleta.quantDeFaltas);
        printf("Equipe: %s\n", nomeEquipe);
        printf("------------------------------------\n");
    } else {
        printf("\nAtleta com matrícula %d não encontrado na equipe.\n", matriculaAtleta);
    }
}
/****************************************************************/
/* 8. Função para mostrar atletas por categoria;  */
/****************************************************************/
void mostrar_atletas_por_categoria(Head *head) {
    if (head == NULL || head->refInicio == NULL) {
        printf("\nNenhuma equipe cadastrada. Não é possível buscar atletas por categoria.\n");
        return;
    }

    char categoriaProcurada[50];
    printf("\n\n--- Mostrar Atletas por Categoria ---\n");
    printf("Digite a categoria que deseja buscar (Ex: Sub-17, Senior): ");
    fgets(categoriaProcurada, sizeof(categoriaProcurada), stdin);
    categoriaProcurada[strcspn(categoriaProcurada, "\n")] = '\0';

    int atletasEncontrados = 0; // Contador para verificar se algum atleta foi encontrado na categoria
    noTime *current_equipe = head->refInicio;

    printf("\n--- Atletas na Categoria '%s' ---\n", categoriaProcurada);
    while (current_equipe != NULL) { // Percorre todas as equipes
        // Compara a categoria (strcmp retorna 0 se forem iguais)
        if (strcmp(current_equipe->time.categoria, categoriaProcurada) == 0) {
            if (current_equipe->listaAtletas != NULL) { // Se a equipe tem atletas
                printf("\nEquipe: %s (%s)\n", current_equipe->time.nome, current_equipe->time.esporte);
                printf("-------------------------------------------\n");
                noAtleta *current_atleta = current_equipe->listaAtletas;
                noAtleta *inicio_atleta_lista = current_atleta; // Guarda o início para a condição de parada
                
                do { // Percorre a lista circular de atletas desta equipe
                    printf("Nome: %s | Matrícula: %d | Idade: %d | Camisa: %d | Faltas: %d\n",
                           current_atleta->atleta.nome, current_atleta->atleta.matricula, current_atleta->atleta.idade,
                           current_atleta->atleta.numeroDaCamisa, current_atleta->atleta.quantDeFaltas);
                    current_atleta = current_atleta->prox;
                    atletasEncontrados++;
                } while (current_atleta != inicio_atleta_lista); // Condição de parada
                printf("-------------------------------------------\n");
            } else {
                printf("\nEquipe: %s (%s) - Nao possui atletas cadastrados nesta categoria.\n", current_equipe->time.nome, current_equipe->time.esporte);
            }
        }
        current_equipe = current_equipe->proxTime; // Próxima equipe
    }

    if (atletasEncontrados == 0) {
        printf("\nNenhum atleta encontrado para a categoria '%s'.\n", categoriaProcurada);
    }
    printf("----------------------------------------------\n");
}

/****************************************************************/
/* FUNÇÃO PRINCIPAL   */
/****************************************************************/
int main () {
    int opcao;
    Head *head = iniciarHead();

    if (head == NULL) {
        return 1; // Encerra se a alocação inicial falhar
    }

    do {
        printf("--------------------------------\n");
        printf("GERENCIAMENTO DE CLUBE ESPORTIVO\n");
        printf("              MENU              \n");
        printf("--------------------------------\n");
        printf("1 - Cadastrar equipe;\n");
        printf("2 - Cadastrar atleta em equipe;\n");
        printf("3 - Remover equipe;\n");
        printf("4 - Remover atleta;\n");
        printf("5 - Mostrar todas as equipes;\n");
        printf("6 - Mostrar composição de equipe;\n");
        printf("7 - Mostrar dados de atleta;\n");
        printf("8 - Mostrar atletas por categoria;\n");
        printf("0 - Encerrar programa.\n");
        printf("--------------------------------\n");
        printf("Digite uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Consome o '\n' deixado pelo scanf

        switch (opcao) {
            case 1:
                cadastrar_equipe(head);
                break;
            case 2:
                cadastrar_atleta(head);
                break;
            case 3:
                remover_equipe(head);
                break;
            case 4:
                remover_atleta(head);
                break;
            case 5:
                exibir_equipes(head);
                break;
            case 6:
                exibir_equipe_especifica(head);
                break;
            case 7:
                mostrar_dados_atleta_especifico(head);
                break;
            case 8:
                mostrar_atletas_por_categoria(head);
                break;
            case 0:
                printf("\nSaindo do programa...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
        if (opcao != 0) {
             printf("\nPressione Enter para continuar...");
             getchar(); // Pausa para o usuário ler a saída
        }
        printf("\n\n");
    } while (opcao != 0);

    // Liberar toda a memória alocada antes de sair
    noTime *aux = head->refInicio;
    while(aux != NULL) {
        noTime *proximaEquipe = aux->proxTime;
        // Reutiliza a lógica de remover equipe para limpar os atletas
        if (aux->listaAtletas != NULL) {
            noAtleta *atletaaux = aux->listaAtletas;
            atletaaux->ant->prox = NULL;
            while(atletaaux != NULL) {
                noAtleta *proximoAtleta = atletaaux->prox;
                free(atletaaux);
                atletaaux = proximoAtleta;
            }
        }
        free(aux);
        aux = proximaEquipe;
    }
    free(head);

    return 0;
}