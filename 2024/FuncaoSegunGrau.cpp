#include<iostream>
#include<cmath>
using namespace std;

class resultadoRaiz{
private:
    float x1;
    float x2;
    
public:

    resultadoRaiz(float x1, float x2){
    this->x1 = x1;
    this->x2 = x2;
    }
    
    ~resultadoRaiz(){}
    
    float getX1() const{
        return x1;
    }
    
    float getX2() const{
        return x2;
    }

};

class Vertice{
private:
    float x;
    float y;
    
public:
    Vertice(float x, float y){
        this->x = x;
        this->y = y;
    }
    
    ~Vertice(){}
    
    float getX() const {
        return x;
    }
    
    float getY() const{
        return y;
    }
 
};

class funcao{
private:
    int a;
    int b;
    int c;
    
public:
    funcao(){
        a = 0;
        b = 0;
        c = 0;
    }
    
    funcao(int a, int b, int c){
        this->a = a;
        this->b = b;
        this->c = c;
    }
    
    ~funcao(){}
    
    float delta() const{
        return (b*b)-(4*a*c);
    }
    
    
    resultadoRaiz Raiz() const{
        float x1, x2;
        x1 = ((-1*b) + sqrt(delta())) / (2*a);
        x2 = ((-1*b) - sqrt(delta())) / (2*a);
        
        return resultadoRaiz(x1,x2);
    }
    
    Vertice calcularVertice() const{
        float x, y;
        x = (-1*b) / (2*a);
        y = (-1*delta())/(4*a);
        return Vertice(x,y);
    }

};

int main()
{
    funcao Teste(1,2,-3);
    
    resultadoRaiz Raiz = Teste.Raiz();
    Vertice V = Teste.calcularVertice();
    
    cout << "X1:" << Raiz.getX1() << endl << "X2" << Raiz.getX2() << endl;
    
    cout << "(" << V.getX() << "," << V.getY() << ")" << endl;
    
    return 0;
}