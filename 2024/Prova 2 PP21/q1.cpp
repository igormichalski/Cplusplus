
#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;

class VetorOrdenado{
private:
    vector<int> meuVetor; //Melhor trocar para data dps

    void inserirOrdenado(int x){
        meuVetor.push_back(x);
        sort(meuVetor.begin(), meuVetor.end());
    }

    void removerOrdenado(int x){
        if (meuVetor.empty()){  // testa se o vetor está vazio
            cout << "Vetor vazio!" << endl;
        }else{
            //Remove
            for(int i = 0; i < meuVetor.size(); i++){
                if(meuVetor[i] == x){
                    vector<int>::iterator aux = meuVetor.begin() + i; //Cria um vetor iterator para que possamos remover ele
                    meuVetor.erase(aux);
                    i=0;
                }
            }
            sort(meuVetor.begin(), meuVetor.end()); 
        }
    }

    void mostrar() const{
         if (meuVetor.empty()){  // testa se o vetor está vazio
            cout << "Vetor vazio!" << endl;
        }else{
            for(int i = 0; i < meuVetor.size(); i++){
                cout << "Imprimindo o vetor...: " << meuVetor[i] << endl;
            }
        }
    }

    int getValor(int index) const{
        return meuVetor[index];
    }

public:
    VetorOrdenado(){
        //Como meuVector é inicializado sozinho aqui não preciso colocar nada
    }

    ~VetorOrdenado(){
        cout << "Destruido!!" << endl;
    }

    void inserir(int x){
       inserirOrdenado(x);
    }

    void remover(int x){
        removerOrdenado(x);
    }

    void imprimir() const{
        mostrar();
    }

    int valor(int index) const{
        return getValor(index);
    }

};

int main(){    
    VetorOrdenado V;

    V.inserir(1);
    V.inserir(2);
    V.inserir(5);
    V.inserir(6);
    V.inserir(2);

    V.remover(2);

    V.imprimir();

  return 0;
}