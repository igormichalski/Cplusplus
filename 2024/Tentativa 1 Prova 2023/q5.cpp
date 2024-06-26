#include <iostream>

using namespace std;

class Matriz{
private:
    int **matriz;
    int i,j;

public:
    Matriz(int i, int j){
        this->i = i;
        this->j = j;

        //Alocando Matriz
        matriz = (int **) malloc(i * sizeof(int));
        for(int k = 0; k < i; k++){
            matriz[k] = (int*) malloc(j * sizeof(int));
        }
    }

    ~Matriz(){
        for(int k = 0; k < i; k++){
            free(matriz[k]);
        }
        free(matriz);
    }

    void setDado(int x, int y, int dado){
        matriz[x][y] = dado;
    }

    int getDado(int x, int y) const{
        return matriz[x][y];
    }

};

int main(){

    Matriz *M = new Matriz(2,2);

    M->setDado(0,0,1);
    M->setDado(0,1,2);
    M->setDado(1,0,3);
    M->setDado(1,1,4);

    cout << M->getDado(0,0) << " ";
    cout << M->getDado(0,1);
    cout << endl;
    cout << M->getDado(1,0) << " ";
    cout << M->getDado(1,1);

    return 0;
}