#include<iostream>
using namespace std;

class Pontos{
private:
    int x;
    int y;

public:
    Pontos(){
        x=0;
        y=0;
    }
    
    Pontos(int x, int y){
        this->x = x;
        this->y = y;
    }
    
    ~Pontos(){}
    
    void setPonto(int x, int y){
        this->x = x;
        this->y = y;
    }
    
    void translacao(int x, int y){
        this->x += x;
        this->y += y;
    }
    
    void distancia(Pontos outro) const{
        cout << "Distancia X:" << x - outro.x << endl;
        cout << "Distancia Y:" << y - outro.y << endl;
    }
    
    int getX() const{
        return x;
    }
    
    int getY() const{
        return y;
    }

};


int main()
{
    Pontos T(2,4);
    
    Pontos G(1,6);
    
    T.distancia(G);
    
    
    return 0;
}