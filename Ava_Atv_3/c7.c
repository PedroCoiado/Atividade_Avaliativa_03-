#include <stdio.h>
#include <stdlib.h>

// Troca o valor de duas variaveis na memoria usando ponteiros
void trocar(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

// Funcoes auxiliares para imprimir o vetor na tela
void mostrarVetorComIndices(int v[], int n) {
    printf("   Indices:  ");
    for (int i = 0; i < n; i++) printf(" %2d ", i);
    printf("\n   v[]    = [");
    for (int i = 0; i < n; i++) printf(" %2d%s", v[i], (i < n - 1) ? "," : "");
    printf(" ]\n");
}

void mostrarVetorSimples(int v[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d%s", v[i], (i < n - 1) ? ", " : "");
    }
    printf("]");
}

// ---------------------------------------------------------
// Manipulacao de Arquivos
// ---------------------------------------------------------

// Cria o arquivo e grava os valores iniciais digitados pelo usuario
void criarArquivoDados(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao criar %s.\n", nomeArquivo);
        return;
    }

    int qtd, valor;
    printf("\nQuantos numeros deseja gravar em '%s'? (Recomendado: 6): ", nomeArquivo);
    scanf("%d", &qtd);

    if (qtd < 1 || qtd > 100) {
        qtd = 6; // Padrao de seguranca caso o usuario digite um valor invalido
    }

    for (int i = 0; i < qtd; i++) {
        printf("Digite o valor para v[%d]: ", i);
        scanf("%d", &valor);
        fprintf(arquivo, "%d ", valor);
    }

    fclose(arquivo);
    printf("Dados salvos em '%s'.\n", nomeArquivo);
}

// Le os dados do arquivo e atualiza a variavel 'quantidade' por referencia
void lerArquivoDados(const char *nomeArquivo, int v[], int *quantidade) {
    FILE *arquivo = fopen(nomeArquivo, "r");

    // Se o arquivo nao existir, forca a criacao
    if (arquivo == NULL) {
        printf("\nArquivo '%s' nao encontrado. Iniciando criacao...\n", nomeArquivo);
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

// Funcao generica para salvar qualquer vetor no arquivo (dados ou ordenado)
void salvarVetorEmArquivo(const char *nomeArquivo, int v[], int quantidade) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) return;

    for (int i = 0; i < quantidade; i++) {
        fprintf(arquivo, "%d ", v[i]);
    }
    fclose(arquivo);
}

// ---------------------------------------------------------
// Algoritmos de Ordenacao (Com Passo a Passo)
// ---------------------------------------------------------

// 1. Bubble Sort
void bubbleSort(int v[], int n) {
    printf("\n--- Passo a passo: Bubble Sort ---\n");
    for (int i = 0; i < n - 1; i++) {
        int limiteJ = n - 1 - i;
        for (int j = 0; j < limiteJ; j++) {
            if (v[j] > v[j + 1]) {
                printf("Trocando %d e %d -> ", v[j], v[j + 1]);
                trocar(&v[j], &v[j + 1]);
                mostrarVetorSimples(v, n);
                printf("\n");
            }
        }
    }
}

// 2. Insertion Sort
void insertionSort(int v[], int n) {
    printf("\n--- Passo a passo: Insertion Sort ---\n");
    for (int i = 1; i < n; i++) {
        int chave = v[i];
        int j = i - 1;
        printf("Inserindo chave %d: ", chave);
        
        // Empurra os elementos maiores para a direita
        while (j >= 0 && v[j] > chave) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = chave; // Encaixa a chave na posicao correta
        mostrarVetorSimples(v, n);
        printf("\n");
    }
}

// 3. Selection Sort
void selectionSort(int v[], int n) {
    printf("\n--- Passo a passo: Selection Sort ---\n");
    for (int i = 0; i < n - 1; i++) {
        int menor = i;
        // Varre o resto do vetor procurando alguem menor
        for (int j = i + 1; j < n; j++) {
            if (v[j] < v[menor]) menor = j;
        }
        
        if (menor != i) {
            printf("Troca v[%d]=%d com v[%d]=%d -> ", i, v[i], menor, v[menor]);
            trocar(&v[i], &v[menor]);
            mostrarVetorSimples(v, n);
            printf("\n");
        }
    }
}

// 4. Quick Sort (Mantido o formato da tabela de teste de mesa)
void quickSort(int v[], int inicio, int fim, int n) {
    int i = inicio, j = fim;
    int pivo = v[(inicio + fim) / 2];

    printf("\n[Quick Sort] Particao (ini: %d, fim: %d) | Pivo: %d\n", inicio, fim, pivo);
    printf(" ini | fim |  i |  j | w(i<=j) | w(v[i]<p) | w(v[j]>p) | if(i<=j) (troca)\n");
    printf("-------------------------------------------------------------------------\n");

    while (1) {
        if (i > j) {
            printf(" %3d | %3d | %2d | %2d |    F    |     -     |     -     |    -\n", inicio, fim, i, j);
            break;
        }

        while (v[i] < pivo) {
            printf(" %3d | %3d | %2d | %2d |    T    |     T     |     -     |    -\n", inicio, fim, i, j);
            i++;
        }
        
        int flagJ = 0;
        while (v[j] > pivo) {
            if (flagJ) printf(" %3d | %3d | %2d | %2d |    T    |     -     |     T     |    -\n", inicio, fim, i, j);
            j--;
            flagJ = 1;
        }

        printf(" %3d | %3d | %2d | %2d |    T    |     F     |     F     |    %c\n", 
               inicio, fim, i, j, (i <= j) ? 'T' : 'F');

        if (i <= j) {
            trocar(&v[i], &v[j]);
            printf("   -> Trocou v[%d] e v[%d]. Vetor: ", i, j);
            mostrarVetorSimples(v, n);
            printf("\n");
            i++;
            j--;
        }
    }

    if (inicio < j) quickSort(v, inicio, j, n);
    if (i < fim) quickSort(v, i, fim, n);
}

// 5. Merge Sort
void merge(int v[], int inicio, int meio, int fim, int n) {
    int i = inicio, j = meio + 1, k = 0;
    int aux[100];

    // Intercala comparando os lados
    while (i <= meio && j <= fim) {
        if (v[i] <= v[j]) aux[k++] = v[i++];
        else aux[k++] = v[j++];
    }
    
    // Copia as sobras
    while (i <= meio) aux[k++] = v[i++];
    while (j <= fim) aux[k++] = v[j++];

    // Passa do vetor auxiliar para o original
    for (i = inicio, k = 0; i <= fim; i++, k++) {
        v[i] = aux[k];
    }
    
    printf("Intercalou (%d..%d): ", inicio, fim);
    mostrarVetorSimples(v, n);
    printf("\n");
}

void mergeSort(int v[], int inicio, int fim, int n) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        mergeSort(v, inicio, meio, n);
        mergeSort(v, meio + 1, fim, n);
        merge(v, inicio, meio, fim, n);
    }
}

// ---------------------------------------------------------
// Logica de Negocio (Menus e Interacoes)
// ---------------------------------------------------------

// Processa a escolha da ordenacao e salva em arquivo
void escolherEOrdenar(int numeros[], int quantidade) {
    int opcao;
    int copia[100];

    // Usa uma copia para manter os dados originais no 'dados.txt' intactos
    for (int i = 0; i < quantidade; i++) copia[i] = numeros[i];

    printf("\n--- Algoritmos ---\n");
    printf("1 - Bubble Sort\n");
    printf("2 - Insertion Sort\n");
    printf("3 - Selection Sort\n");
    printf("4 - Quick Sort\n");
    printf("5 - Merge Sort\n");
    printf("Escolha: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1: bubbleSort(copia, quantidade); break;
        case 2: insertionSort(copia, quantidade); break;
        case 3: selectionSort(copia, quantidade); break;
        case 4: quickSort(copia, 0, quantidade - 1, quantidade); break;
        case 5: mergeSort(copia, 0, quantidade - 1, quantidade); break;
        default: printf("Opcao invalida!\n"); return;
    }

    printf("\nResultado Final: ");
    mostrarVetorComIndices(copia, quantidade);

    salvarVetorEmArquivo("ordenado.txt", copia, quantidade);
    printf("-> Dados ordenados salvos em 'ordenado.txt'!\n");
}

// Permite alterar um elemento direto pelo indice e reordena
void alterarValorEReordenar(int numeros[], int quantidade) {
    int posicao, novoValor;

    printf("\nVetor atual:\n");
    mostrarVetorComIndices(numeros, quantidade);

    printf("\nPosicao (1 a %d) que deseja alterar: ", quantidade);
    scanf("%d", &posicao);

    if (posicao < 1 || posicao > quantidade) {
        printf("Posicao invalida!\n");
        return;
    }

    printf("Novo valor para v[%d]: ", posicao - 1);
    scanf("%d", &novoValor);

    numeros[posicao - 1] = novoValor;
    salvarVetorEmArquivo("dados.txt", numeros, quantidade);
    
    printf("\nValor atualizado. Selecione como deseja reordenar:\n");
    escolherEOrdenar(numeros, quantidade);
}

// ---------------------------------------------------------
// Main
// ---------------------------------------------------------
int main() {
    int numeros[100];
    int quantidade = 0;
    int opcaoMenu;

    lerArquivoDados("dados.txt", numeros, &quantidade);

    do {
        printf("\n========================================\n");
        printf(" Dados atuais (n = %d):\n", quantidade);
        mostrarVetorComIndices(numeros, quantidade);
        printf("========================================\n");
        printf("1 - Ordenar e gerar 'ordenado.txt'\n");
        printf("2 - Alterar valor e reordenar\n");
        printf("3 - Recriar 'dados.txt' com novos valores\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcaoMenu);

        switch (opcaoMenu) {
            case 1: escolherEOrdenar(numeros, quantidade); break;
            case 2: alterarValorEReordenar(numeros, quantidade); break;
            case 3: 
                criarArquivoDados("dados.txt");
                lerArquivoDados("dados.txt", numeros, &quantidade);
                break;
            case 0: printf("\nSaindo...\n"); break;
            default: printf("\nOpcao invalida.\n"); break;
        }
    } while (opcaoMenu != 0);

    return 0;
}
