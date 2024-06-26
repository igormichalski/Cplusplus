#include <iostream>

using namespace std;

class Metros{
private:
    float medida;

public:
    Metros(float medida){
        this->medida = medida;
    }

    float getMedida() const{
        return medida;
    }

    //Soma e Subtração
    Metros operator+(const Metros &m){
        return Metros(medida + m.medida);
    }
    Metros operator-(const Metros &m){
        return Metros(medida - m.medida);
    }

    //Pre
    Metros& operator++(){
        medida++;
        return *this;
    }
    
    Metros& operator--(){
        medida--;
        return *this;
    }

    //Pos
    Metros operator++(int){
        Metros aux = *this;
        medida++;
        return aux;
    }

    Metros operator--(int){
        Metros aux = *this;
        medida--;
        return aux;
    }

    //Bool
    bool operator==(const Metros m){
        return medida == m.medida;
    }
    bool operator!=(const Metros m){
        return medida != m.medida;
    }
    bool operator>=(const Metros m){
        return medida >= m.medida;
    }
    bool operator<=(const Metros m){
        return medida <= m.medida;
    }
    bool operator<(const Metros m){
        return medida < m.medida;
    }
    bool operator>(const Metros m){
        return medida > m.medida;
    }

    friend ostream& operator<<(ostream& os, const Metros &m){
        os << m.medida << endl;
        return os;
    }

};

int main(){

    return 0;
}