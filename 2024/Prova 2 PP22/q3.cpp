#include <iostream>
#include <vector>

using namespace std;

class Solido{
private:
    int x,y,z;

public:
    Solido(int x, int y, int z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Solido(){
        this->x = 0;
        this->y = 0;
        this->z = 0;  
    }

    virtual float area() const = 0;
    
    virtual float volume() const = 0;

    virtual ~Solido(){}
};


class Esfera : public Solido{
private:
    float pi = 3.14;
    float raio;

public:
    Esfera(float raio) : Solido(){
        this->raio = raio;
    }

    virtual float area() const override{
        return 4*pi*raio*raio; //314
    }

    virtual float volume() const override{
        return 4/3 * pi * raio * raio * raio;
    }

    ~Esfera(){}
};


class Cilindro : public Solido{
private:
    float pi = 3.14;
    float raio;
    float altura;

public:
    Cilindro(float raio, float altura) : Solido(){
        this->raio = raio;
        this->altura = altura;
    }

    virtual float area() const override{
        return 2* pi * raio * (raio + altura); //282,6
    }

    virtual float volume() const override{
        return pi * raio * raio * altura;
    }

    ~Cilindro(){}
};

class Conjunto{
private:
    vector<Solido *> vetor;

public:
    Conjunto(){}

    void inserir(Solido *U){
        vetor.push_back(U);
    }

    float areaTotal() const{ 
        float aux = 0;
        for(int i = 0; i<vetor.size(); i++){
            aux += vetor[i]->area();
        }
        return aux;
    }

    float volumeTotal() const{
        float aux = 0;
        for(int i = 0; i<vetor.size(); i++){
            aux += vetor[i]->volume();
        }
        return aux;
    }

    ~Conjunto(){}
};

int main(){

    Conjunto data;

    data.inserir(new Esfera(5)); 
    data.inserir(new Cilindro(5,4));

    cout << data.areaTotal() << endl;
    cout << data.volumeTotal() << endl;

    return 0;
}