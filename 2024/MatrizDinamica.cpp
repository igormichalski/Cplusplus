#include <iostream> 
#include <sstream>

using namespace std;

class Matriz{
private:
    int **matriz;
    int i,j;

public:
    Matriz(int i, int j){
        matriz = (int **) malloc(i * sizeof(int));
        for (int k = 0; k < i; k++) {
            matriz[k] = (int *) malloc(j * sizeof(int));
        }
        this->i = i;
        this->j = j;
    }

    ~Matriz(){
        for (int k = 0; k < i; k++) {
            free (matriz[k]);
        }
        free(matriz);
    }

    void setValor(int x, int y, int valor){
        if(x <= i)
            if(y <= j)
                matriz[x][y] = valor;
    }

    int getValor(int x, int y) const{
        if(x <= i)
            if(y <= j)
                return matriz[x][y];
    }

};


int main (){

    Matriz *M = new Matriz(2,3);

    M->setValor(0,0,1);
    M->setValor(0,1,2);
    M->setValor(0,2,3);
    M->setValor(1,0,4);
    M->setValor(1,1,5);
    M->setValor(1,2,6);

    cout << M->getValor(0,0);
    cout << M->getValor(0,1);
    cout << M->getValor(0,2);
    cout << M->getValor(1,0);
    cout << M->getValor(1,1);
    cout << M->getValor(1,2);

    delete M;

}