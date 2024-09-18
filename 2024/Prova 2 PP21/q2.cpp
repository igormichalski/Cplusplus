#include <iostream>

using namespace std;

class Instrumento{
private:  
    string nome;

public:
    Instrumento(string nome){
        this->nome = nome;
    }

    virtual ~Instrumento(){

    }

    virtual void Som() const = 0; //Aqui criamos nossa class Abstrata. Ela força com que nas classes derivadas seja obrigatorio a implementação dessa função
};

class Bateria : public Instrumento{
private:

public:
    Bateria(string nome) : Instrumento(nome){ 

    }

    virtual void Som() const override{ //Aqui vemos a implementação da função que é obritorio!
        cout << "Tu, Pa, TU TU TU, PA" << endl;
    }
};


class Guitarra : public Instrumento{
private:

public:
    Guitarra(string nome) : Instrumento(nome){ 

    }

    virtual void Som() const override{ //Aqui vemos a implementação da função que é obritorio!
        cout << "Taran ranranran taranraran!" << endl;
    }
};



int main(){

    Instrumento *IgorBateria = new Bateria("Bateria Igor");
    Instrumento *gustavoGuitarra = new Guitarra("Guitarra Gustavo");
    
    //Parte extra (Polimorfismos)
    Instrumento *banda[2] = {IgorBateria, gustavoGuitarra} ;

    for(int i = 0; i < 2; i++)
        banda[i]->Som();

    delete IgorBateria;
    delete gustavoGuitarra;
    
    return 0;
}