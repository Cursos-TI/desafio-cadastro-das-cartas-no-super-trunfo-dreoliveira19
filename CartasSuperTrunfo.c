#include <stdio.h>
#include <string.h>

// Definição da estrutura para armazenar os dados das cartas
typedef struct {
    char estado;
    char codigo[4];
    char nomeCidade[50];
    int populacao;
    float area;
    float pib;
    int pontosTuristicos;
    float densidadePopulacional; 
    float pibPerCapita;          
} Carta;

// Função para calcular Densidade Demográfica da cidade
void calcularDensidade(Carta *c) {
    if (c->area > 0) {
        c->densidadePopulacional = c->populacao / c->area;
    } else {
        c->densidadePopulacional = 0;
    }
}

// Função para calcular PIB per Capta da cidade
void calcularPib(Carta *c) {
    if (c->populacao > 0) {
        c->pibPerCapita = c->pib * 1000000000 / c->populacao; // PIB em reais por pessoa
    } else {
        c->pibPerCapita = 0;
    }
}

// Função para exibir os dados de uma carta
void exibirCarta(Carta c) {
    printf("\n--- Dados da Carta ---\n");
    printf("Estado: %c\n", c.estado);
    printf("Código da Carta: %s\n", c.codigo);
    printf("Nome da Cidade: %s\n", c.nomeCidade);
    printf("População: %d\n", c.populacao);
    printf("Área: %.2f km²\n", c.area);
    printf("Densidade Populacional: %.2f pessoas/km²\n", c.densidadePopulacional);
    printf("PIB: %.2f bilhões de reais\n", c.pib);
    printf("PIB per Capita: %.2f reais\n", c.pibPerCapita);
    printf("Número de Pontos Turísticos: %d\n", c.pontosTuristicos);
    printf("----------------------\n");
}

int main() {
    Carta cartas[32]; // Total de 32 cartas (8 estados x 4 cidades por estado)
    int totalCartas = 0;
    int opcao = 0;
    char opcaoContinuar = 'S';
    printf("Bem-vindo ao sistema Super Trunfo de Países!\n\n");

    while(opcao != 9){ // Menu de Opções
        printf("\nEscolha sua Opção\n");
        printf("1 - Cadastrar Cartas\n");
        printf("2 - Exibir Cartas\n");
        printf("9 - Encerrar\n");
        scanf(" %d", &opcao);

        if(opcao == 1){ //Cadastrar Cartas
            opcaoContinuar = 'S';
            while ((totalCartas < 32) && (opcaoContinuar != 'N' && opcaoContinuar != 'n') ) {
                Carta novaCarta;

                printf("\n--- Cadastro de Carta %d ---\n", totalCartas + 1);
                printf("Digite o estado (A-H): ");
                scanf(" %c", &novaCarta.estado);

                // Validação do estado
                if (novaCarta.estado < 'A' || novaCarta.estado > 'H') {
                    printf("Estado inválido! Digite uma letra entre A e H.\n");
                    continue;
                }

                printf("Digite o código da carta (ex: A01): ");
                scanf(" %s", novaCarta.codigo);

                printf("Digite o nome da cidade: ");
                scanf(" %[^\n]", novaCarta.nomeCidade);

                printf("Digite a população da cidade: ");
                scanf(" %d", &novaCarta.populacao);

                printf("Digite a área da cidade em km²: ");
                scanf(" %f", &novaCarta.area);

                printf("Digite o PIB da cidade (em bilhões de reais): ");
                scanf(" %f", &novaCarta.pib);

                printf("Digite o número de pontos turísticos: ");
                scanf(" %d", &novaCarta.pontosTuristicos);

                // Calcular Densidade e PIB Per Capta
                calcularDensidade(&novaCarta);
                calcularPib(&novaCarta);

                // Armazenar a carta no array
                cartas[totalCartas] = novaCarta;
                totalCartas++;

                // Exibir confirmação do cadastro
                printf("\nCarta cadastrada com sucesso!\n");
                exibirCarta(novaCarta);

                // Perguntar se o usuário deseja continuar cadastrando
                printf("Deseja cadastrar outra carta? (S/N): ");
                scanf(" %c", &opcaoContinuar);
            }

            if(totalCartas >=32){
                printf("\nLimite de cartas atingido (32 cartas).\n");
            }
            else{
                printf("\nTotal de cartas cadastradas: %d\n", totalCartas);
            }
        }

        if(opcao == 2){// Exibição de todas as cartas cadastradas
            printf("\n=== Cartas Cadastradas ===\n");
            for (int i = 0; i < totalCartas; i++) {
                exibirCarta(cartas[i]);
            }

            printf("\nTotal de cartas cadastradas: %d\n", totalCartas);
        }

    }
    return 0;
}
