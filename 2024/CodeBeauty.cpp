#include <iostream>
#include <list>
using namespace std;

class CanalYoutube { //Class Base
private:
    string email;
    int totalInscritos;
    list<string> videosPublicados;
protected: //igual o private, mas da pra acessar em outra class
    string nomeCanal;
    int qualidade;
public:
    //Construtor Padrão
    CanalYoutube(string nome, string emailCadastro){
        nomeCanal = nome;
        email = emailCadastro;
        totalInscritos = 0;
        qualidade = 0;
        //lista não é passada porque quando criamos um canal do yt não publicamos videos ainda
    }

    //GETRS E SETRS
//   ??

    //METODOS (servem para acessar as variaveis que estão em private, podendo alterar, mostrar e outros)
    void Sub(){
        totalInscritos++;
    }
    void Unsub(){
        if(totalInscritos>0)
            totalInscritos--;
    }
    void PublicarVideo(string nome){
        videosPublicados.push_back(nome);
    };
    void RemoverVideo(string nome){
        videosPublicados.remove(nome);
    };
    void imprimir( ){
        int i = 1;
        cout << "Nome Canal: " << nomeCanal << endl;
        cout << "Email: " << email << endl;
        cout << "Inscritos: " << totalInscritos << endl;
        cout << "Videos Publicados: " << endl;
        for(string NomeVideo : videosPublicados) {
            cout << i << " = " << NomeVideo << endl;
            i++;
        }
        cout << endl;
    }
    void Estatisticas(){
        if(qualidade<5){
            cout << nomeCanal << "Tu precisa melhorar!" << endl;
        }else{
            cout << nomeCanal << "Tu ta muito bom!" << endl;
        }
    }

};

class CanaisComida: public CanalYoutube { //Class Derivada (CanalYoutube)
public:
    CanaisComida(string nome, string emailCadastro) : CanalYoutube(nome, emailCadastro){
    //Chamamos o construtor da class Base
    } //construtor

    //METODOS que só essa clase tem
    void verVideo(){
        cout << "o Canal de " << nomeCanal << " foi assistido!!" << endl;
        qualidade++;
    }
};

class CanaisCorrida: public CanalYoutube { //Class Derivada (CanalYoutube)
public:
    CanaisCorrida(string nome, string emailCadastro) : CanalYoutube(nome, emailCadastro){
        //Chamamos o construtor da class Base
    } //construtor

    //METODOS que só essa clase tem
    void verVideo(){
        cout << "o Canal de " << nomeCanal << " a velocidade esta no peito e foi assistido!!" << endl;
        qualidade++;
    }
};

int main() {
    CanaisComida ytComida("Cozinhandoo2", "igor@comp.uems");
    CanaisCorrida ytCorrida("VEloCIDADE", "ronaldoDiogo@comp.uems");

    ytComida.verVideo();
    ytComida.verVideo();
    ytComida.verVideo();
    ytComida.verVideo();
    ytComida.verVideo();
    ytComida.verVideo();

    ytCorrida.verVideo();

    //Basicamente o polimorfismo mostra que podemos criar um ponteiro do
    // tipo CLASS BASE e nele termos o endereço de uma CLASS DERIVADA
    CanalYoutube *yt1= &ytComida;
    CanalYoutube *yt2= &ytCorrida;

    yt1->Estatisticas();
    yt2->Estatisticas();


}
