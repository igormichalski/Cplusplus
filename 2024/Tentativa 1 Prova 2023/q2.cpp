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

int main(){

    Metros M1(1);

    cout << "Teste Soma e Sub" << endl;
    //Teste Soma e Sub
    Metros M2 = M1 + M1;
    cout << M2 << endl;
    //Teste Sub
    M2 = M1 - M1;
    cout << M2 << endl;

    cout << "Teste Bool" << endl;
    bool saida; 
    saida = M2 == M1;
    cout << saida << endl;
    saida = M2 != M1;
    cout << saida << endl;
    saida = M2 < M1;
    cout << saida << endl;
    saida = M2 > M1;
    cout << saida << endl;
    saida = M2 <= M1;
    cout << saida << endl;
    saida = M2 >= M1;
    cout << saida << endl;
    
    return 0;
}