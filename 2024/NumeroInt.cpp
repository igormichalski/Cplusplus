#include<iostream>
#include<cmath>
using namespace std;

class NumeroInt{
private:
    int numero;
    
public:
    NumeroInt(){
        numero = 0;
    }
    
    NumeroInt(int mumero){
    this->numero = numero;
    }

    int getNumero() const{
        return numero;
    }
    
    void setNumero(int numero){
        this->numero = numero;
    }
    
    int raiz() const{
        return sqrt(numero);
    }
    
    int potencia() const{
        return numero * numero;
    }
    
    NumeroInt operator+(NumeroInt outro) const {
        return NumeroInt(numero + outro.numero);
    }
    

};


int main()
{
    NumeroInt um(1);
    NumeroInt dez(10);
    
    cout << um.getNumero() << endl;
    cout << dez.getNumero() << endl;
    
    NumeroInt onze;
    
    onze = um+dez;
    
    cout << onze.getNumero() << endl;
    
    
    
    return 0;
}