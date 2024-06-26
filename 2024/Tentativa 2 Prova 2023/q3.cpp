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

class Milhas{
private:
    float medida;

public:
    Milhas(float medida){
        this->medida = medida;
    }
    Milhas(const Metros &m){
        this->medida = m.getMedida() / 1609.34;
    }

    float getMedida() const{
        return medida;
    }

    //Soma e Subtração
    Milhas operator+(const Milhas &m){
        return Milhas(medida + m.medida);
    }
    Milhas operator-(const Milhas &m){
        return Milhas(medida - m.medida);
    }

    //Pre
    Milhas& operator++(){
        medida++;
        return *this;
    }
    
    Milhas& operator--(){
        medida--;
        return *this;
    }

    //Pos
    Milhas operator++(int){
        Milhas aux = *this;
        medida++;
        return aux;
    }

    Milhas operator--(int){
        Milhas aux = *this;
        medida--;
        return aux;
    }

    //Bool
    bool operator==(const Milhas m){
        return medida == m.medida;
    }
    bool operator!=(const Milhas m){
        return medida != m.medida;
    }
    bool operator>=(const Milhas m){
        return medida >= m.medida;
    }
    bool operator<=(const Milhas m){
        return medida <= m.medida;
    }
    bool operator<(const Milhas m){
        return medida < m.medida;
    }
    bool operator>(const Milhas m){
        return medida > m.medida;
    }

    friend ostream& operator<<(ostream& os, const Milhas &m){
        os << m.medida << endl;
        return os;
    }

    operator Metros() {
        return Metros(medida * 1609.34);
    }

};

int main(){


    return 0;
}