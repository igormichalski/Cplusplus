#include <iostream>
#include <vector>

using namespace std;

class Solido{
protected:
    float pi = 3.14;

public:
    Solido(){}

    virtual float area() const = 0;

    virtual float volume() const = 0;

    ~Solido(){
        cout << "Destruindo" << endl;
    }

};


class Esfera : public Solido{
private:
    float raio;

public:
    Esfera(float raio) : Solido(){
        this->raio = raio;
    }

    virtual float area() const override{
        return 4*pi*raio*raio; 
    }

    virtual float volume() const override{
        return 4/3*pi*raio*raio*raio;
    }
};

class Cilindro : public Solido{
private:
    float raio;
    float altura;

public:
    Cilindro(float raio, float altura) : Solido(){
        this->raio = raio;
        this->altura = altura;
    }

    virtual float area() const override{
        return 2*pi*raio*(raio+altura); 
    }

    virtual float volume() const override{
        return pi*raio*raio*altura;
    }
};

class ConjuntoSolidos{
private:
    vector<Solido*> vetor;

public:
    void adicionar(Solido *U){
        vetor.push_back(U);
    }

    float calculoArea() const{
        float areaTotal = 0;
        for(int i = 0; i < vetor.size(); i++){
            areaTotal += vetor[i]->area();
        }
        return areaTotal;
    }

    float calculoVolume() const{
        float volumeTotal = 0;
        for(int i = 0; i < vetor.size(); i++){
            volumeTotal += vetor[i]->volume();
        }
        return volumeTotal;
    }

    ~ConjuntoSolidos(){
        for(int i = 0; i < vetor.size(); i++){
            delete vetor[i];
        }
    }
};

int main(){

    //Adicionando class Cubo //Q4
    class Cubo : public Solido{
    private:
        float lado;

    public:
        Cubo(float lado){
            this->lado = lado;
        }

        virtual float area() const override{
        return 6*lado*lado; 
        }

        virtual float volume() const override{
            return lado*lado*lado;
        }
    };



    ConjuntoSolidos *I = new ConjuntoSolidos;
    ConjuntoSolidos A;

    A.adicionar(new Esfera(3));
    A.adicionar(new Cilindro(3,2));
    A.adicionar(new Cubo(3));
    cout << A.calculoArea() << endl;
    cout << A.calculoVolume() << endl;

    cout << endl;

    I->adicionar(new Esfera(3));
    I->adicionar(new Cilindro(3,2));
    I->adicionar(new Cubo(3));
    cout << I->calculoArea() << endl;
    cout << I->calculoVolume() << endl;

    delete I;

    return 0;
}