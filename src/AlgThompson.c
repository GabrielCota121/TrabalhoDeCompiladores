#include <stdio.h>
#include <stdlib.h>
#define EPSILON -1
/*
Esse código é parte do projeto de implementação do Algoritmo de Thompson para a construção de autômatos finitos a
partir de expressões regulares. As expressões regulares são convertidas em autômatos finitos não determinísticos (AFND), 
facilitando a análise e o reconhecimento de padrões em cadeias de caracteres.
PS: O meu vscode tem uma IA que faz comentários e escritas de código automaticamente.
*/

typedef struct Estado {
    int id;
    int caracter; // Pensei na representação dos números da tabela ASCII, mas isso pode virar um char também, não sei a melhor opção
    struct Estado *transicao1;  
    struct Estado *transicao2; 
}Estado;

// Estrutura para um fragmento (subgrafo) do NFA
// Aqui está a árvore sintática que representa um fragmento do autômato finito não determinístico (AFND) construído a partir de uma expressão regular.

typedef struct Fragmento {
    Estado *inicio;  
    Estado *fim;   
} Fragmento;

int contadorDeEstados = 0; // Contador global para atribuir IDs únicos aos estados


// Função para criar um novo estado no autômato finito não determinístico (AFND).

Estado* criarEstado(int caracter) {
    Estado *novoEstado = (Estado *)malloc(sizeof(Estado));
    novoEstado->id = contadorDeEstados++;
    novoEstado->caracter = caracter;
    novoEstado->transicao1 = NULL;
    novoEstado->transicao2 = NULL;  
    return novoEstado;
}
// Quando você cria um novo estado sempre terá um epsilon para a transição para o próximo estado.
Fragmento criarFragmento(char caracter){
    Estado *inicio = criarEstado(caracter); 
    Estado *fim = criarEstado(EPSILON);     
    inicio->transicao1 = fim; 
    Fragmento f={inicio, fim};
    return f;
}

// Implementação das 3 operações básicas do Algoritmo de Thompson: concatenação, união e fechamento de Kleene.

//Regra 1: Concatenação: Conecta o final de um fragmento ao início de outro.

Fragmento concatenar(Fragmento a, Fragmento b) {
    a.fim->caracter = EPSILON; // Converte o estado final do primeiro fragmento em um estado de transição epsilon
    a.fim->transicao1 = b.inicio; // Conecta o estado final do primeiro fragmento ao estado inicial do segundo
    Fragmento f = {a.inicio, b.fim}; // O novo fragmento começa no início do primeiro e termina no final do segundo
    return f;
}
// Regra 2: União (ou alternância): Cria um novo estado inicial que se conecta aos estados iniciais dos dois fragmentos.

Fragmento uniao(Fragmento a, Fragmento b) {
    Estado *novoInicio = criarEstado(EPSILON); // Novo estado inicial com transição epsilon
    Estado *novoFim = criarEstado(EPSILON); // Novo estado final com transição epsilon
    novoInicio->transicao1 = a.inicio; // Conecta ao início do primeiro fragmento
    novoInicio->transicao2 = b.inicio; // Conecta ao início do segundo fragmento
    
    a.fim->transicao1 = novoFim; 
    b.fim->transicao1 = novoFim;
    Fragmento f = {novoInicio, novoFim}; // O novo fragmento começa no novo estado inicial e termina no novo estado final
    return f;
}

// Regra 3: Fechamento de Kleene: Cria um novo estado inicial e final, permitindo repetições do fragmento.

Fragmento fechamentoKleene(Fragmento a) {
    Estado *novoInicio = criarEstado(EPSILON);
    Estado *novoFim = criarEstado(EPSILON);

    novoInicio->transicao1 = a.inicio;   // opção 1: entra no fragmento
    novoInicio->transicao2 = novoFim;    // opção 2: pula direto (zero repetições)

    a.fim->transicao1 = a.inicio;        // ao terminar, pode voltar pro início...
    a.fim->transicao2 = novoFim;         // ...ou sair de vez

    Fragmento f = {novoInicio, novoFim};
    return f;
}

