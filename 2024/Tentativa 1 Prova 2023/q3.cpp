#include <iostream>

using namespace std;

class Metros{
private:
    float medida;

public:
    Metros(float medida){
        this->medida = medida;
    }

    float getMedida() const {
        return medida;
    }

    //Soma e Subtração
    Metros operator+(Metros &outro){
        return Metros(medida + outro.medida);
    }

    Metros operator-(Metros &outro){
        return Metros(medida - outro.medida);
    }

    //Pre ? 
    

    //Pos ?



    //Bool
    bool operator==(Metros &outro){
        return medida == outro.medida;
    }
    bool operator!=(Metros &outro){
        return medida != outro.medida;
    }
    bool operator<(Metros &outro){
        return medida < outro.medida;
    }
    bool operator>(Metros &outro){
        return medida > outro.medida;
    }
    bool operator<=(Metros &outro){
        return medida <= outro.medida;
    }
    bool operator>=(Metros &outro){
        return medida >= outro.medida;
    }

    friend ostream& operator<<(ostream& os, const Metros &M){
        os << M.medida;
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

    //Construtor de copia
    Milhas(const Metros &metros){
        this->medida = metros.getMedida() * 1609.34;
    }

    float getMedida() const {
        return medida;
    }

    //Soma e Subtração
    Milhas operator+(Milhas &outro){
        return Milhas(medida + outro.medida);
    }

    Milhas operator-(Milhas &outro){
        return Milhas(medida - outro.medida);
    }

    //Pre ? 
    

    //Pos ?



    //Bool
    bool operator==(Milhas &outro){
        return medida == outro.medida;
    }
    bool operator!=(Milhas &outro){
        return medida != outro.medida;
    }
    bool operator<(Milhas &outro){
        return medida < outro.medida;
    }
    bool operator>(Milhas &outro){
        return medida > outro.medida;
    }
    bool operator<=(Milhas &outro){
        return medida <= outro.medida;
    }
    bool operator>=(Milhas &outro){
        return medida >= outro.medida;
    }

    friend ostream& operator<<(ostream& os, const Milhas &M){
        os << M.medida;
        return os;
    }

    operator Metros() const{
        return Metros(medida / 1609.34);
    }

};


int main(){

    Metros metros(1);
    Milhas milhas = metros;
    cout << milhas << endl;

    Milhas M1(1609.34);
    Metros M2 = M1;
    cout << M2 << endl;
    
    return 0;
}