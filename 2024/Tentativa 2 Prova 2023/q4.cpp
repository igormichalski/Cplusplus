#include <iostream>

using namespace std;

template <class T> class No{
public:
    T dado;
    No<T> *proximo;

    No(T dado){
        this->dado = dado;
        proximo = nullptr;
    }
};

template <class T> class Lista{
private:
    No<T> *cabeca;
    int Tam;

public:
    Lista(){
        cabeca = nullptr;
        Tam = 10;
    }

    void inserir(T valor){
        if(Tam > 0){
            No<T> *novo = new No<T>(valor);
            novo->proximo = cabeca;
            cabeca = novo;
            Tam--;
        }
    }

    void remover(){
        if(Tam != 10){
            No<T> *aux = cabeca;
            cabeca = cabeca->proximo;
            delete aux;
            Tam++;
        }
    }

    //[]
    T& operator[](int index){
        if((index <= 10) && (index >=0)){
            No<T> *aux = cabeca;
            for(int i=0; i<index; i++){
                aux = aux->proximo;
            }
            return aux->dado;
        }
    }

    void imprimir() const{
        No<T> *aux = cabeca;
        while(aux != nullptr){
            cout << aux->dado << endl;
            aux = aux->proximo;
        }
    }

};



int main(){

    Lista<int> L;

    L.inserir(20);
    L.inserir(21);
    L.inserir(22);

    L[0] = 33;
    cout << "Teste: " << L[0] << endl;

    L.imprimir();

    return 0;
}