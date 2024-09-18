#include <iostream>
#include <vector>

using namespace std;

template <class T> class Vetor{
private:
    vector<T> data;

public:
    Vetor(){}

    void inserir(T valor){
        if(data.size() == 0){
            data.push_back(valor);
        }else{
            int meio = data.size()/2;
            vector<T> temp = data;
            data.clear();
            for(int i=0; i<temp.size(); i++){
                if(meio != i){
                    data.push_back(temp[i]);
                }else{
                    data.push_back(valor);
                    data.push_back(temp[i]);
                }
            }
        }        
    }

    T& operator[](int index){
        return data[index];
    }

    friend ostream& operator<<(ostream &os, const Vetor &v){
        for(int i=0; i< v.data.size(); i++)
            os << v.data[i] << endl;
        return os;
    }

    ~Vetor(){}
};

int main(){

    Vetor<string> vetor;

    vetor.inserir("1");
    vetor.inserir("2");
    vetor.inserir("3");
    vetor.inserir("4");
    vetor.inserir("5");

    //vetor[0] = 100;

    cout << vetor;

    //cout << "[4] =" << vetor[4] << endl;


    return 0;
}