#include <iostream>

using namespace std;

class Fracao{
private:
    int cima, baixo;

public:
    Fracao(int cima, int baixo){
        this->cima = cima;
        this->baixo = baixo;
    }

    ~Fracao(){ cout << "FIM" << endl; }

    int getCima() const{
        return cima;
    }

    int getBaixo() const{
        return baixo;
    }

    Fracao multiplicar(Fracao outra) const{
        return Fracao(cima * outra.cima, baixo * outra.baixo);
    }

    Fracao operator*(Fracao &outra) const{
        return Fracao(cima * outra.cima, baixo * outra.baixo);
    }

};

int main(){
    Fracao *meio = new Fracao(1,2);
    Fracao *UmTerco = new Fracao(1,3);

    Fracao *Resultado = new Fracao(*meio * *UmTerco);

    cout << Resultado->getCima() << "/" << Resultado->getBaixo() << endl;

    delete meio;
    delete UmTerco;
    delete Resultado;

    return 0;
}