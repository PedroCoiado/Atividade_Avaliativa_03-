# Atividade Avaliativa 03 - Ordenação + Manipulação de Arquivos em C

Programa em C que une **algoritmos de ordenação** com **manipulação de arquivos**. O usuário grava números em um arquivo, escolhe o algoritmo de ordenação, acompanha o **passo a passo** na tela e salva o resultado em um novo arquivo.

## Funcionalidades

| # | Requisito da atividade | Como o programa atende |
|---|---|---|
| 1 | Criar e gravar arquivo com dados desordenados | `criarArquivoDados()` grava os valores digitados em `dados.txt` |
| 2 | Ler os dados do arquivo | `lerArquivoDados()` carrega `dados.txt` no vetor (se não existir, pede a criação) |
| 3 | Escolher o tipo de ordenação | `escolherEOrdenar()` oferece Bubble, Insertion, Selection, Quick e Merge Sort |
| 4 | Ordenar e salvar em novo arquivo | O resultado é gravado em `ordenado.txt` |
| 5 | Alterar um valor e reordenar | `alterarValorEReordenar()` atualiza `dados.txt` e reordena |

## Arquivos

| Arquivo | Descrição |
|---|---|
| `main.c` | Código-fonte completo |
| `dados.txt` | Valores originais (desordenados) |
| `ordenado.txt` | Valores ordenados (gerado pelo programa) |

## Como compilar e executar

```bash
gcc main.c -o programa
./programa
```

No Windows:

```bash
gcc main.c -o programa.exe
programa.exe
```

## Menu principal

```
1 - Ordenar e gerar 'ordenado.txt'
2 - Alterar valor e reordenar
3 - Recriar 'dados.txt' com novos valores
0 - Sair
```

Algoritmos disponíveis ao ordenar:

```
1 - Bubble Sort
2 - Insertion Sort
3 - Selection Sort
4 - Quick Sort
5 - Merge Sort
```

## Estrutura do código

| Função | Papel |
|---|---|
| `trocar()` | Troca dois valores usando ponteiros |
| `mostrarVetorComIndices()` / `mostrarVetorSimples()` | Exibem o vetor na tela |
| `criarArquivoDados()` | Cria `dados.txt` com valores digitados |
| `lerArquivoDados()` | Lê o arquivo e atualiza a quantidade por referência |
| `salvarVetorEmArquivo()` | Grava qualquer vetor em arquivo |
| `bubbleSort()`, `insertionSort()`, `selectionSort()`, `quickSort()`, `mergeSort()` | Algoritmos de ordenação, todos com passo a passo |
| `escolherEOrdenar()` | Menu de algoritmos e gravação em `ordenado.txt` |
| `alterarValorEReordenar()` | Altera uma posição, salva e reordena |

## Decisões de projeto

- A ordenação trabalha sobre uma **cópia** do vetor, então `dados.txt` permanece com os valores originais.
- Limite de **100 elementos** (vetores de tamanho fixo).
- O **Quick Sort** exibe uma tabela de teste de mesa (`ini`, `fim`, `i`, `j` e as condições dos `while`/`if`).
- Os demais algoritmos mostram o vetor a cada troca, inserção ou intercalação.
- Se `dados.txt` não existir, o programa solicita a criação automaticamente.
- Ao alterar um valor, o usuário informa a posição de 1 a n (o programa converte para o índice real).

## Conceitos aplicados

- Manipulação de arquivos (`fopen`, `fscanf`, `fprintf`, `fclose`)
- Ponteiros e passagem de parâmetros por referência
- Vetores
- Recursividade (Quick Sort e Merge Sort)
- Modularização com funções
- Menu interativo com `do...while` e `switch`

## Base teórica

Planos de aula utilizados: **8, 9, 11 e 12**.

## Autor

| Aluno | RGM | Curso |
|---|---|---|
| Guilherme Hiroshi dos Santos Okamoto | 47554703 | Engenharia de Software |
| Gustavo Gomes Silva | 47436808 | Engenharia de Software |
| Pedro Henrique Ruola Coiado | 47589124 | Ciência da Computação |
