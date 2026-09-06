#include<iostream>
#include <memory>
#define EPSILON -1
/*
Esse código é parte do projeto de implementação do Algoritmo de Thompson para a construção de autômatos finitos a
partir de expressões regulares. As expressões regulares são convertidas em autômatos finitos não determinísticos (AFND), 
facilitando a análise e o reconhecimento de padrões em cadeias de caracteres.
PS: O meu vscode tem uma IA que faz comentários e escritas de código automaticamente.
*/

class Estado{
    private:
        static int contadorDeEstados; // Contador global para atribuir IDs únicos aos estados
    public:
        int caracter; // Caracter que o estado reconhece (ou EPSILON para transições epsilon)
        std::shared_ptr<Estado> transicao1; // Ponteiro para o próximo estado (transição 1)
        std::shared_ptr<Estado> transicao2; // Ponteiro para o próximo estado (transição 2, usado em casos de união)
        int id; 

        Estado(int caracter){
            this->caracter = caracter;
            this->transicao1 = nullptr;
            this->transicao2 = nullptr;
            this->id = contadorDeEstados++;
        }

};

int Estado::contadorDeEstados = 0;

class Fragmento{
    
    public:
        std::shared_ptr<Estado> inicio;  // Ponteiro para o estado inicial do fragmento
        std::shared_ptr<Estado> fim;     // Ponteiro para o estado final do fragmento

        Fragmento(std::shared_ptr<Estado> inicio, std::shared_ptr<Estado> fim){
            this->inicio = inicio;
            this->fim = fim;
        }

        Fragmento(char caracter){
            this->inicio = std::make_shared<Estado>(caracter);
            this->fim = std::make_shared<Estado>(EPSILON);
            this->inicio->transicao1 = this->fim; 
        }

         static Fragmento unir(const Fragmento& f1, const Fragmento& f2) {
            std::shared_ptr<Estado> novoInicio = std::make_shared<Estado>(EPSILON);
            std::shared_ptr<Estado> novoFim = std::make_shared<Estado>(EPSILON);

            novoInicio->transicao1 = f1.inicio;
            novoInicio->transicao2 = f2.inicio;

            // Garante que os estados finais antigos viraram transições neutras
            f1.fim->caracter = EPSILON;
            f2.fim->caracter = EPSILON;

            f1.fim->transicao1 = novoFim;
            f2.fim->transicao1 = novoFim;

            return Fragmento(novoInicio, novoFim);
        }

        static Fragmento concatenar(const Fragmento& f1, const Fragmento& f2) {
            
            f1.fim->caracter = EPSILON; 
            
            f1.fim->transicao1 = f2.inicio; 
            return Fragmento(f1.inicio, f2.fim);
        }

        static Fragmento fecharKleene(const Fragmento& f) {
            std::shared_ptr<Estado> novoInicio = std::make_shared<Estado>(EPSILON);
            std::shared_ptr<Estado> novoFim = std::make_shared<Estado>(EPSILON);

            novoInicio->transicao1 = f.inicio;
            novoInicio->transicao2 = novoFim;

            f.fim->caracter = EPSILON; 
            f.fim->transicao1 = f.inicio;  
            f.fim->transicao2 = novoFim;   

            return Fragmento(novoInicio, novoFim);
        }

};