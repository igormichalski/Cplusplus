#include<iostream>
using namespace std;

class Matriz{
private:
    float data[2][2];

public:
    Matriz(){
        for(int i=0; i<2; i++){
            for(int j=0; j<2; j++){
                this->data[i][j] = 0;
            }
        }
    }
    
    ~Matriz(){}
    
    void setValor(int i, int j, float data){
        if(i>=0 && j>=0)
            this->data[i][j] = data;
    }
    
    float determinante() const {
        return (data[0][0] * data[1][1]) - (data[0][1] * data[1][0]);
    }

    Matriz &operator+(Matriz &outra){
        Matriz temp;
        for(int i=0; i<2; i++){
            for(int j=0; j<2; j++){
                temp[i][j] = this->data[i][j] + outra[i][j];
            }
        }
        
        return temp;
    }
    
    float* operator[](int i){
        return data[i];
    }
    
    Matriz &operator*(Matriz &outra){
        Matriz temp;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    temp[i][j] += this->data[i][k] * outra[k][j];
                }
            }
        }
        return temp;
    }
    
    Matriz inversa(float det) const{
        Matriz temp;

        if (det != 0.0) {
            temp[0][0] = data[1][1] / det;
            temp[0][1] = -data[0][1] / det;
            temp[1][0] = -data[1][0] / det;
            temp[1][1] = data[0][0] / det;
        }else{
            cout << "Não existe inversa" << endl;
        }
       return temp; 
    }

};


int main()
{
    Matriz M;
    Matriz M2;
    
    M.setValor(0,0,1);
    M.setValor(0,1,2);
    M.setValor(1,0,3);
    M.setValor(1,1,4);
    
    M2.setValor(0,0,1);
    M2.setValor(0,1,2);
    M2.setValor(1,0,3);
    M2.setValor(1,1,4);
    
    Matriz M3;
    
    M3 = M * M2;
    
    Matriz Minv;
    Minv = M.inversa(M.determinante());
    
    for(int i=0; i<2; i++){
        for(int j=0; j<2; j++){
            cout << Minv[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}