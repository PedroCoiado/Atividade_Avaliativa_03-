#include <stdio.h>
#include <stdlib.h>

// ============================================================================
// PLANO DE AULA 09: Função void com ponteiros para trocar dois valores
// ============================================================================
void trocar(int *a, int *b) {
    int aux = *a; // Guarda o valor de 'a' na variável auxiliar
    *a = *b;      // Passa o valor de 'b' para 'a'
    *b = aux;     // Passa o valor salvo em 'aux' para 'b'
}

// Funções auxiliares visuais (para desenhar o vetor igual à lousa)
void mostrarVetorComIndices(int v[], int n) {
    printf("   Indices:  ");
    for (int i = 0; i < n; i++) {
        printf(" %2d ", i);
    }
    printf("\n   v[]    = [");
    for (int i = 0; i < n; i++) {
        printf(" %2d%s", v[i], (i < n - 1) ? "," : "");
    }
    printf(" ]\n");
}

void mostrarVetorSimples(int v[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d%s", v[i], (i < n - 1) ? ", " : "");
    }
    printf("]");
}

// ============================================================================
// PLANO DE AULA 08: Funções void para Manipulação de Arquivos
// ============================================================================

// Requisito 1: Criar e gravar um arquivo com dados numéricos (desordenados)
void criarArquivoDados(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo %s!\n", nomeArquivo);
        return;
    }

    int qtd, valor;
    printf("\nQuantos numeros deseja gravar em '%s'?\n", nomeArquivo);
    printf("(Dica: digite 6 e insira 7 2 5 1 8 3): ");
    scanf("%d", &qtd);

    if (qtd < 1 || qtd > 100) {
        printf("Quantidade ajustada automaticamente para 6.\n");
        qtd = 6;
    }

    for (int i = 0; i < qtd; i++) {
        printf("Digite o valor para a gaveta v[%d]: ", i);
        scanf("%d", &valor);
        fprintf(arquivo, "%d ", valor);
    }

    fclose(arquivo);
    printf("Arquivo '%s' criado e gravado com sucesso!\n", nomeArquivo);
}

// Requisito 2: Ler os dados do arquivo (usando ponteiro *quantidade)
void lerArquivoDados(const char *nomeArquivo, int v[], int *quantidade) {
    FILE *arquivo = fopen(nomeArquivo, "r");

    // Se o arquivo ainda não existir no computador, pede para criar agora
    if (arquivo == NULL) {
        printf("\nArquivo '%s' nao encontrado. Vamos criar o arquivo inicial!\n", nomeArquivo);
        criarArquivoDados(nomeArquivo);
        arquivo = fopen(nomeArquivo, "r");
        if (arquivo == NULL) {
            *quantidade = 0;
            return;
        }
    }

    *quantidade = 0;
    while (*quantidade < 100 && fscanf(arquivo, "%d", &v[*quantidade]) == 1) {
        (*quantidade)++;
    }

    fclose(arquivo);
}

// Função para salvar o vetor atualizado em dados.txt ou ordenado.txt
void salvarVetorEmArquivo(const char *nomeArquivo, int v[], int quantidade) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar no arquivo %s!\n", nomeArquivo);
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        fprintf(arquivo, "%d ", v[i]);
    }

    fclose(arquivo);
}

// ============================================================================
// PLANO DE AULA 11: Os 5 Algoritmos de Ordenação em Funções void
// (Imprimindo a Tabela de Teste de Mesa com T / F e Fórmulas Matemáticas)
// ============================================================================

// 1. BUBBLE SORT
void bubbleSort(int v[], int n) {
    printf("\n==============================================================================\n");
    printf("ENTENDENDO O BUBBLE SORT (Ordenacao por Bolha):\n");
    printf("- Ideia: Compara vizinhos v[j] e v[j+1]. Se o da esquerda for maior, troca!\n");
    printf("- Formula das Passagens (i): vai de 0 ate n - 2 (0 ate %d)\n", n - 2);
    printf("- Formula das Comparacoes (j): vai de 0 ate (n - 1 - i)\n");
    printf("==============================================================================\n");
    mostrarVetorComIndices(v, n);

    for (int i = 0; i < n - 1; i++) {
        int limiteJ = n - 1 - i;
        printf("\n--- PASSAGEM i = %d | Formula limite de j: (%d - 1 - %d) = %d ---\n", i, n, i, limiteJ);
        printf("  i |  j | j+1 | Teste: if(v[j] > v[j+1])   | aux | Vetor v[]\n");
        printf("------------------------------------------------------------------------------\n");

        for (int j = 0; j < limiteJ; j++) {
            int condicao = (v[j] > v[j + 1]);
            printf(" %2d | %2d |  %2d | v[%d](%2d) > v[%d](%2d) = %c ",
                   i, j, j + 1, j, v[j], j + 1, v[j + 1], condicao ? 'T' : 'F');

            if (condicao) {
                int aux = v[j];
                trocar(&v[j], &v[j + 1]);
                printf("     | %3d | ", aux);
                mostrarVetorSimples(v, n);
                printf(" (Trocou)\n");
            } else {
                printf("     |  -  | ");
                mostrarVetorSimples(v, n);
                printf(" (Mantem)\n");
            }
        }
    }
}

// 2. INSERTION SORT
void insertionSort(int v[], int n) {
    printf("\n==============================================================================\n");
    printf("ENTENDENDO O INSERTION SORT (Ordenacao por Insercao):\n");
    printf("- Ideia: Funciona como organizar cartas de baralho na mao.\n");
    printf("- Pega a carta chave = v[i] (comecando de i = 1) e compara com as anteriores (j = i - 1).\n");
    printf("- Enquanto v[j] > chave for Verdadeiro (T), empurra o numero para a direita: v[j+1] = v[j].\n");
    printf("==============================================================================\n");
    mostrarVetorComIndices(v, n);

    for (int i = 1; i < n; i++) {
        int chave = v[i];
        int j = i - 1;
        printf("\n--- PASSO i = %d | chave = v[%d] = %d | Comeca olhando j = i - 1 = %d ---\n", i, i, chave, j);

        while (j >= 0) {
            int condicao = (v[j] > chave);
            printf("  while(j >= 0 && v[j] > chave) -> v[%d](%d) > %d = %c\n",
                   j, v[j], chave, condicao ? 'T' : 'F');
            if (condicao) {
                printf("    -> Como deu T: empurra v[%d]=%d para a gaveta v[%d] e faz j-- (j vira %d)\n",
                       j, v[j], j + 1, j - 1);
                v[j + 1] = v[j];
                j--;
            } else {
                printf("    -> Como deu F: achou o lugar certo! Para de recuar.\n");
                break;
            }
        }
        v[j + 1] = chave;
        printf("  Encaixa a chave na formula v[j + 1]: v[%d] = %d -> Vetor: ", j + 1, chave);
        mostrarVetorSimples(v, n);
        printf("\n");
    }
}

// 3. SELECTION SORT
void selectionSort(int v[], int n) {
    printf("\n==============================================================================\n");
    printf("ENTENDENDO O SELECTION SORT (Ordenacao por Selecao):\n");
    printf("- Ideia: Procura o menor numero de todos e coloca na primeira posicao disponivel (i).\n");
    printf("- Formula: Assume que 'menor = i' e testa o resto do vetor com j = i + 1 ate n - 1.\n");
    printf("==============================================================================\n");
    mostrarVetorComIndices(v, n);

    for (int i = 0; i < n - 1; i++) {
        int menor = i;
        printf("\n--- PASSO i = %d | Assume inicialmente que o menor esta na gaveta %d (valor %d) ---\n",
               i, menor, v[menor]);

        for (int j = i + 1; j < n; j++) {
            int condicao = (v[j] < v[menor]);
            printf("  j = %d | if(v[%d] < v[%d]) -> %d < %d = %c",
                   j, j, menor, v[j], v[menor], condicao ? 'T' : 'F');
            if (condicao) {
                menor = j;
                printf(" -> Novo menor encontrado na gaveta %d (valor %d)!\n", menor, v[menor]);
            } else {
                printf("\n");
            }
        }
        int aux = v[i];
        trocar(&v[i], &v[menor]);
        printf("  Troca final do passo: v[%d] troca com v[%d] (aux = %d) -> Vetor: ", i, menor, aux);
        mostrarVetorSimples(v, n);
        printf("\n");
    }
}

// 4. QUICK SORT (Reproduz exatamente a Tabela do Quadro do Professor!)
void quickSort(int v[], int inicio, int fim, int n) {
    int i = inicio;
    int j = fim;
    int indiceMeio = (inicio + fim) / 2;
    int pivo = v[indiceMeio];

    printf("\n==============================================================================\n");
    printf("QUADRO DO QUICK SORT: quickSort(v, inicio = %d, fim = %d)\n", inicio, fim);
    printf("Formula Mat. do Pivo: v[(inicio + fim) / 2] = v[(%d + %d) / 2] = v[%d] = %d\n",
           inicio, fim, indiceMeio, pivo);
    mostrarVetorComIndices(v, n);
    printf("------------------------------------------------------------------------------\n");
    printf(" ini | fim |  i |  j | Pivo     | aux | w(i<=j) | w(v[i]<pivo)   | w(v[j]>pivo)   | if(i<=j)\n");
    printf("------------------------------------------------------------------------------\n");

    while (1) {
        int w_ij = (i <= j);
        if (!w_ij) {
            printf(" %3d | %3d | %2d | %2d | v[%d]=%-3d |  -  |    F    |       -        |       -        |    -\n",
                   inicio, fim, i, j, indiceMeio, pivo);
            break;
        }

        // 1) Testes do while(v[i] < pivo)
        while (v[i] < pivo) {
            printf(" %3d | %3d | %2d | %2d | v[%d]=%-3d |  -  |    T    | v[%d](%2d)<%-2d= T |       -        | (i++ -> %d)\n",
                   inicio, fim, i, j, indiceMeio, pivo, i, v[i], pivo, i + 1);
            i++;
        }
        // Momento em que v[i] < pivo dá Falso (F)
        printf(" %3d | %3d | %2d | %2d | v[%d]=%-3d |  -  |    T    | v[%d](%2d)<%-2d= F | ",
               inicio, fim, i, j, indiceMeio, pivo, i, v[i], pivo);

        // 2) Testes do while(v[j] > pivo)
        int primeiroTesteJ = 1;
        while (v[j] > pivo) {
            if (!primeiroTesteJ) {
                printf(" %3d | %3d | %2d | %2d | v[%d]=%-3d |  -  |    T    |       -        | ",
                       inicio, fim, i, j, indiceMeio, pivo);
            }
            printf("v[%d](%2d)>%-2d= T | (j-- -> %d)\n", j, v[j], pivo, j - 1);
            j--;
            primeiroTesteJ = 0;
        }
        if (!primeiroTesteJ) {
            printf(" %3d | %3d | %2d | %2d | v[%d]=%-3d |  -  |    T    |       -        | ",
                   inicio, fim, i, j, indiceMeio, pivo);
        }
        // Momento em que v[j] > pivo dá Falso (F)
        int if_ij = (i <= j);
        printf("v[%d](%2d)>%-2d= F |    %c\n", j, v[j], pivo, if_ij ? 'T' : 'F');

        // 3) Se if(i <= j) for Verdadeiro (T), realiza a troca com aux
        if (if_ij) {
            int aux = v[i];
            trocar(&v[i], &v[j]);
            printf("   -> TROCA REALIZADA (aux = %d): trocou v[%d] com v[%d]. Agora i++ (%d) e j-- (%d)\n",
                   aux, i, j, i + 1, j - 1);
            printf("   -> Vetor v[] agora: ");
            mostrarVetorSimples(v, n);
            printf("\n------------------------------------------------------------------------------\n");
            i++;
            j--;
        }
    }

    // Condições de recursão escritas na parte inferior da lousa
    int recEsq = (inicio < j);
    int recDir = (i < fim);
    printf("Testes de Recursao (Final da Lousa):\n");
    printf("  if (inicio < j) -> (%d < %d) = %c %s\n",
           inicio, j, recEsq ? 'T' : 'F', recEsq ? "=> Chama quickSort(v, inicio, j)" : "");
    printf("  if (i < fim)    -> (%d < %d) = %c %s\n",
           i, fim, recDir ? 'T' : 'F', recDir ? "=> Chama quickSort(v, i, fim)" : "");

    if (recEsq) quickSort(v, inicio, j, n);
    if (recDir) quickSort(v, i, fim, n);
}

// 5. MERGE SORT
void merge(int v[], int inicio, int meio, int fim, int n) {
    int i = inicio, j = meio + 1, k = 0;
    int aux[100];

    printf("\n  [INTERCALANDO (MERGE)] Juntando metade Esquerda (%d..%d) com Direita (%d..%d):\n",
           inicio, meio, meio + 1, fim);

    while (i <= meio && j <= fim) {
        int cond = (v[i] <= v[j]);
        printf("    Teste: v[%d](%d) <= v[%d](%d) = %c -> aux[%d] recebe %d\n",
               i, v[i], j, v[j], cond ? 'T' : 'F', k, cond ? v[i] : v[j]);
        if (cond) {
            aux[k++] = v[i++];
        } else {
            aux[k++] = v[j++];
        }
    }
    while (i <= meio) {
        printf("    Sobra da esquerda: aux[%d] recebe v[%d](%d)\n", k, i, v[i]);
        aux[k++] = v[i++];
    }
    while (j <= fim) {
        printf("    Sobra da direita : aux[%d] recebe v[%d](%d)\n", k, j, v[j]);
        aux[k++] = v[j++];
    }

    for (i = inicio, k = 0; i <= fim; i++, k++) {
        v[i] = aux[k];
    }

    printf("    Vetor v[] apos intercalar: ");
    mostrarVetorSimples(v, n);
    printf("\n");
}

void mergeSort(int v[], int inicio, int fim, int n) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        printf("\n[DIVIDINDO] Intervalo (%d..%d) | Formula: meio = (%d + %d) / 2 = %d\n",
               inicio, fim, inicio, fim, meio);
        mergeSort(v, inicio, meio, n);
        mergeSort(v, meio + 1, fim, n);
        merge(v, inicio, meio, fim, n);
    }
}

// ============================================================================
// PLANO DE AULA 12: Escolha da Ordenação usando SWITCH para chamar as voids
// ============================================================================
void escolherEOrdenar(int numeros[], int quantidade) {
    int opcaoAlgoritmo;
    int copia[100];

    // Copia para ordenar sem bagunçar o vetor original em memória
    for (int i = 0; i < quantidade; i++) {
        copia[i] = numeros[i];
    }

    printf("\n--- Escolha o Algoritmo de Ordenacao ---\n");
    printf("1 - Bubble Sort\n");
    printf("2 - Insertion Sort\n");
    printf("3 - Selection Sort\n");
    printf("4 - Quick Sort\n");
    printf("5 - Merge Sort\n");
    printf("Opcao: ");
    scanf("%d", &opcaoAlgoritmo);

    // Switch limpo: cada case apenas chama a sua função void!
    switch (opcaoAlgoritmo) {
        case 1:
            bubbleSort(copia, quantidade);
            break;
        case 2:
            insertionSort(copia, quantidade);
            break;
        case 3:
            selectionSort(copia, quantidade);
            break;
        case 4:
            quickSort(copia, 0, quantidade - 1, quantidade);
            break;
        case 5:
            printf("\n==============================================================================\n");
            printf("ENTENDENDO O MERGE SORT (Dividir para Conquistar):\n");
            printf("==============================================================================\n");
            mostrarVetorComIndices(copia, quantidade);
            mergeSort(copia, 0, quantidade - 1, quantidade);
            break;
        default:
            printf("Opcao de algoritmo invalida!\n");
            return;
    }

    printf("\n==============================================================================\n");
    printf("RESULTADO FINAL ORDENADO:\n");
    mostrarVetorComIndices(copia, quantidade);
    printf("==============================================================================\n");

    // Requisito 4: Salvar o resultado em ordenado.txt
    salvarVetorEmArquivo("ordenado.txt", copia, quantidade);
    printf("Valores ordenados salvos com sucesso no arquivo 'ordenado.txt'!\n");
}

// ============================================================================
// Requisito 5: Alterar um valor dentro do arquivo e reordenar novamente
// ============================================================================
void alterarValorEReordenar(int numeros[], int quantidade) {
    int posicao, novoValor;

    printf("\nValores atuais em 'dados.txt':\n");
    mostrarVetorComIndices(numeros, quantidade);

    printf("\nQual posicao (1 a %d) voce deseja alterar? ", quantidade);
    scanf("%d", &posicao);

    if (posicao < 1 || posicao > quantidade) {
        printf("Posicao invalida!\n");
        return;
    }

    printf("Digite o novo valor para substituir o numero %d: ", numeros[posicao - 1]);
    scanf("%d", &novoValor);

    numeros[posicao - 1] = novoValor;

    // Atualiza o arquivo dados.txt
    salvarVetorEmArquivo("dados.txt", numeros, quantidade);
    printf("Arquivo 'dados.txt' atualizado com sucesso!\n");

    // Chama o menu de ordenação para reordenar e atualizar ordenado.txt
    printf("\nAgora escolha o algoritmo para reordenar os dados:\n");
    escolherEOrdenar(numeros, quantidade);
}

// ============================================================================
// FUNÇÃO PRINCIPAL (int main) COM MENU EM SWITCH/CASE (Plano de Aula 12)
// ============================================================================
int main() {
    int numeros[100];
    int quantidade = 0;
    int opcaoMenu;

    // Ao abrir o programa, lê dados.txt (ou cria se não existir)
    lerArquivoDados("dados.txt", numeros, &quantidade);

    do {
        printf("\n==============================================================================\n");
        printf("MENU PRINCIPAL - ATIVIDADE AVALIATIVA 03\n");
        printf("Dados atuais em 'dados.txt' (n = %d):\n", quantidade);
        mostrarVetorComIndices(numeros, quantidade);
        printf("==============================================================================\n");
        printf("1 - Escolher tipo de ordenacao e gerar 'ordenado.txt'\n");
        printf("2 - Alterar um valor em 'dados.txt' e reordenar novamente\n");
        printf("3 - Criar/gravar novos valores em 'dados.txt'\n");
        printf("0 - Sair do programa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcaoMenu);

        switch (opcaoMenu) {
            case 1:
                escolherEOrdenar(numeros, quantidade);
                break;
            case 2:
                alterarValorEReordenar(numeros, quantidade);
                break;
            case 3:
                criarArquivoDados("dados.txt");
                lerArquivoDados("dados.txt", numeros, &quantidade);
                break;
            case 0:
                printf("\nEncerrando o sistema. Ate logo!\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
        }
    } while (opcaoMenu != 0);

    return 0;
}