#include <stdio.h>
#include <string.h>

// Definição da estrutura para armazenar os dados das cartas
typedef struct {
    char estado;
    char codigo[4];
    char nomeCidade[50];
    unsigned long populacao;
    float area;
    float pib;
    int pontosTuristicos;
    float densidadePopulacional;
    float pibPerCapita;
    float superPoder;
} Carta;

// Função para calcular Densidade Populacional da cidade
void calcularDensidade(Carta *c) {
    if (c->area > 0) {
        c->densidadePopulacional = c->populacao / c->area;
    } else {
        c->densidadePopulacional = 0;
    }
}

// Função para calcular PIB per Capita da cidade
void calcularPib(Carta *c) {
    if (c->populacao > 0) {
        c->pibPerCapita = (c->pib * 1000000000) / c->populacao;
    } else {
        c->pibPerCapita = 0;
    }
}

// Função para calcular o Super Poder
void calcularSuperPoder(Carta *c) {
    c->superPoder = c->populacao + c->area + c->pib + c->pibPerCapita + (1 / (c->densidadePopulacional + 1)) + c->pontosTuristicos;
}

// Função para exibir os dados de uma carta
void exibirCarta(Carta c) {
    printf("\n--- Dados da Carta ---\n");
    printf("Estado: %c\n", c.estado);
    printf("C\u00f3digo da Carta: %s\n", c.codigo);
    printf("Nome da Cidade: %s\n", c.nomeCidade);
    printf("Populacao: %lu\n", c.populacao);
    printf("Area: %.2f km\u00b2\n", c.area);
    printf("Densidade Populacional: %.2f pessoas/km\u00b2\n", c.densidadePopulacional);
    printf("PIB: %.2f bilh\u00f5es de reais\n", c.pib);
    printf("PIB per Capita: %.2f reais\n", c.pibPerCapita);
    printf("Numero de Pontos Turisticos: %d\n", c.pontosTuristicos);
    printf("Super Poder: %.2f\n", c.superPoder);
    printf("----------------------\n");
}

void exibirResultado(const char *criterio, float valor1, float valor2, int maiorGanha) {
    int resultado;
    
    if (maiorGanha) {
        resultado = (valor1 > valor2);
    } else {
        resultado = (valor1 < valor2);
    }

    if (resultado) {
        printf("%s: Carta 1 venceu\n", criterio);
    } else {
        printf("%s: Carta 2 venceu\n", criterio);
    }
}

// Função para comparar duas cartas
void compararCartas(Carta c1, Carta c2) {
    printf("\n=== Comparacao de Cartas ===\n");
    printf("Comparando: %s (%s) x %s (%s)\n\n", c1.nomeCidade, c1.codigo, c2.nomeCidade, c2.codigo);

    exibirResultado("Populacao", c1.populacao, c2.populacao, 1);
    exibirResultado("Area", c1.area, c2.area, 1);
    exibirResultado("PIB", c1.pib, c2.pib, 1);
    exibirResultado("PIB per Capita", c1.pibPerCapita, c2.pibPerCapita, 1);
    exibirResultado("Densidade Populacional", c1.densidadePopulacional, c2.densidadePopulacional, 0);
    exibirResultado("Pontos Turisticos", c1.pontosTuristicos, c2.pontosTuristicos, 1);
    exibirResultado("Super Poder", c1.superPoder, c2.superPoder, 1);
}

int main() {
    Carta cartas[32];
    int totalCartas = 0;
    int opcao = 0;
    char opcaoContinuar;
    printf("Bem-vindo ao sistema Super Trunfo de Paises!\n\n");

    while (opcao != 9) {
        printf("\nEscolha sua Opcao\n");
        printf("1 - Cadastrar Cartas\n");
        printf("2 - Exibir Cartas\n");
        printf("3 - Comparar Cartas\n");
        printf("9 - Encerrar\n");
        scanf(" %d", &opcao);

        if (opcao == 1) {
            opcaoContinuar = 'S';
            while (totalCartas < 32 && (opcaoContinuar != 'N' && opcaoContinuar != 'n')) {
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
                scanf(" %lu", &novaCarta.populacao);

                printf("Digite a área da cidade em km²: ");
                scanf(" %f", &novaCarta.area);

                printf("Digite o PIB da cidade (em bilhões de reais): ");
                scanf(" %f", &novaCarta.pib);

                printf("Digite o número de pontos turísticos: ");
                scanf(" %d", &novaCarta.pontosTuristicos);

                // Calcular Densidade e PIB Per Capta
                calcularDensidade(&novaCarta);
                calcularPib(&novaCarta);
                calcularSuperPoder(&novaCarta);
                
                // Armazenar a carta no array
                cartas[totalCartas] = novaCarta;
                totalCartas++;
                
                printf("\nCarta cadastrada com sucesso!\n");
                exibirCarta(novaCarta);

                printf("Deseja cadastrar outra carta? (S/N): ");
                scanf(" %c", &opcaoContinuar);
            }
        }
        else{
            if (opcao == 2) {
                printf("\n=== Cartas Cadastradas ===\n");
                for (int i = 0; i < totalCartas; i++) {
                    exibirCarta(cartas[i]);
                }
            }
            else{
                if (opcao == 3) {
                    if (totalCartas < 2) {
                        printf("\nNecessario pelo menos duas cartas para comparar!\n");
                        continue;
                    }
                    int c1, c2;
                    printf("\nDigite o indice da primeira carta (0 a %d): ", totalCartas - 1);
                    scanf("%d", &c1);
                    printf("Digite o indice da segunda carta (0 a %d): ", totalCartas - 1);
                    scanf("%d", &c2);
                    
                    if (c1 >= 0 && c1 < totalCartas && c2 >= 0 && c2 < totalCartas) {
                        compararCartas(cartas[c1], cartas[c2]);
                    } else {
                        printf("Indices invalidos!\n");
                    }
                }
                else{
                    if (opcao == 9) {
                        printf("Encerrando o jogo...\n");
                    }
                    else{
                        printf("Opção Inválida\n");
                    }
                }
            }
        }
    }
    return 0;
}