#include <iostream>

using namespace std;


class No {
public:
    int valor; 
    No* proximo; 

    // Construtor
    No(int v) : valor(v), proximo(nullptr) {}
};


class ListaEncadeada {
private:
    No* cabeca;

public:
    ListaEncadeada() : cabeca(nullptr) {}

    void adicionarNoInicio(int valor) {
        No* novoNo = new No(valor); 
        novoNo->proximo = cabeca;
        cabeca = novoNo;
    }
   
    void remover() {
        if (cabeca != nullptr) {
            No* temp = cabeca; 
            cabeca = cabeca->proximo; 
            delete temp;
        }
    }

    ~ListaEncadeada() {
        No* atual = cabeca;
        while (atual != nullptr) {
            No* proximo = atual->proximo;
            delete atual;
            atual = proximo;
        }
    }
    
    int operator[](int index){
        No *aux = cabeca;
        for(int i=0; i<index; i++){
            aux = aux->proximo;
        }
        return aux->valor;
    }
 
};


int main(){
    return 0;
}
