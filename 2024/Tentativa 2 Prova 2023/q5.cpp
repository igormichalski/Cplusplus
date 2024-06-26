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

        matriz = (int**) malloc(i * sizeof(int));
        for(int k=0; k<i; k++)
            matriz[k] = (int *) malloc(j * sizeof(int));
    }

    ~Matriz(){
        for(int k=0; k<i; k++)
            free(matriz[k]);
        free(matriz);
    }

    void setData(int x, int y, int data){
        matriz[x][y] = data;
    }

    int getData(int x, int y){
        return matriz[x][y];
    }

};

int main(){

    Matriz *M = new Matriz(2,2);

    M->setData(0,0,1);
    M->setData(0,1,2);
    M->setData(1,0,3);
    M->setData(1,1,4);

    cout <<
    M->getData(0,0) << " " <<
    M->getData(0,1) << endl <<
    M->getData(1,0) << " " <<
    M->getData(1,1) << endl;

    delete M;

    return 0;
}