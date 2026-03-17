// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

#define territorioMax 5
#define stringMax 30

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
typedef struct
{
    char nome[stringMax];
    char cor[stringMax];
    int tropas;
} Territorio;

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.

// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
void cadastroTerritorio(Territorio *territorio, int *totalTerritorio)
{

    if (*totalTerritorio < territorioMax)
    {

        printf("escreva o nome do territorio\n ");
        fgets(territorio[*totalTerritorio].nome, stringMax, stdin);

        printf("escreva a cor do exercito ocupante\n ");
        fgets(territorio[*totalTerritorio].cor, stringMax, stdin);

        printf("escreva o numero de tropas no territorio\n ");
        scanf("%d", &territorio[*totalTerritorio].tropas);

        territorio[*totalTerritorio].nome[strcspn(territorio[*totalTerritorio].nome, "\n")] = '\0';
        territorio[*totalTerritorio].cor[strcspn(territorio[*totalTerritorio].cor, "\n")] = '\0';

        (*totalTerritorio)++;
    }
    else
    {
        printf("Maximo de territorios cadastrados");
        printf("\n");
    }
}
void verTerritorios(Territorio *territorio, int totalTerritorio)
{

    if (totalTerritorio == 0)
    {
        printf("Não há territorios cadastrados\n");
    }
    else
    {
        for (int i = 0; i < totalTerritorio; i++)
        {
            printf("O territorio e: %s\n", territorio[i].nome);
            printf("A cor e: %s\n", territorio[i].cor);
            printf("Com %d tropas\n", territorio[i].tropas);
            printf("\n\n");
        }
    }
}
// Função utilitária:
// limpar buffer
void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
// verificar se a alocacao foi concluida
void VerificarAlocacao(void *ptr)
{
    if (ptr == NULL)
    {

        printf("falha ao alocar memoria");
    }
}

// comando de ataque e comecar a partida

void ataque(Territorio *territorio, int atacante, int defensor)
{
}
// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main()
{
    Territorio *territorio;
    int opcao = 0;
    // o totalterritorio tambem é o numero que representa o territorio no jogo +1
    int totalTerritorio = 0;
    int atacante, defensor;
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    territorio = (Territorio *)calloc(territorioMax, sizeof(Territorio));
    VerificarAlocacao(territorio);

    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    do
    {
        printf("Escolha uma opção\n");
        printf("Para criar um territorio, digite 1\n");
        printf("Para ver a lista de territorios, digite 2\n");
        printf("Para começar a partida, digite 3\n ");
        printf("Para sair, digite 0");
        printf("\n");

        scanf("%d", &opcao);

        limparBuffer();

        switch (opcao)
        {
        case 1:

            cadastroTerritorio(territorio, &totalTerritorio);
            break;

        case 2:

            verTerritorios(territorio, totalTerritorio);

            break;

        case 3:

            printf("Vamos começar o jogo!\n");
            printf("digite um pais para atacar e um pais para defender, se quiser sair, aperte 0\n");
            for (int i = 0; i < totalTerritorio; i++)
            {
                printf("%d - representa o país %s\n", i + 1, territorio[i].nome);
                printf("da cor %s\n", territorio[i].cor);
                printf("e possui %d tropas\n", territorio[i].tropas);
            }

            scanf("%d %d\n", &atacante, &defensor);
            limparBuffer();

            break;

        case 0:
            printf("encerrando o programa");
            break;

        default:
            printf("Insira um valor valido");

            break;
        }

    } while (opcao != 0);
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.
    free(territorio);

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.

// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
