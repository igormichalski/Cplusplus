#include <iostream>

using namespace std;

class Cilindro{
private:
    int raio, altura;

public:
    Cilindro(int raio, int altura){
        this->raio = raio;
        this->altura = altura;    
    }

    float Volume() const{
        return 3.14 * raio * raio * altura;
    }

    float Area() const{
        return (2*(3.14 * raio * raio)) + (2*( 3.14 * raio * altura));
    }

};

int main(){

    Cilindro C(2,3);

    cout << C.Volume() << endl;
    cout << C.Area() << endl;

    return 0;
}