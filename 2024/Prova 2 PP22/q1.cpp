#include <iostream>
#include <vector>

using namespace std;

template <class T> class VetorOrdenado{
private:
    vector<T> data;

public:
    VetorOrdenado(){}
    
    void inserir(T valor){
        data.push_back(valor);
        bublle();
    }

    void remover(T valor){   
        vector<T> temp = data;
        data.clear();
        for(int i=0; i<temp.size(); i++){
            if(valor != data[i])
                inserir(data[i]);
        }
    }

    T& operator[](int index){
        return data[index];
    }

    friend ostream& operator<<(ostream& os, const VetorOrdenado &v){
        for(int i=0; i<v.data.size(); i++)
            os << v.data[i] << endl;
        return os;
    }

    void bublle(){
        for(int i=0; i<data.size() - 1; i++)
            for(int j=0; j<data.size() - i - 1; j++){
                if(data[j] > data[j+1]){
                    T temp = data[j];
                    data[j] = data[j+1];
                    data[j+1] = temp;
                }
            }
    }

    ~VetorOrdenado(){}
};


int main(){

    VetorOrdenado<int> vetor;

    vetor.inserir(1);
    vetor.inserir(2);
    vetor.inserir(3);
    vetor.inserir(4);

    vetor[1] = 7;

    cout << vetor;

    cout << "[0] = " << vetor[0] << endl;

    return 0;
}