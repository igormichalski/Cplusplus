#include <iostream>
#include <string>

using namespace std;


template <class Tipo> class Aposta{
private:
    Tipo numSorte;

public:
    Aposta(Tipo numSorte){
        this->numSorte = numSorte;
    }

    Tipo getNumSorte() const{
        return numSorte;
    }

};

int main() {

    Aposta<string> n1("Preto");

    Aposta<int> n2(15);

    cout << n1.getNumSorte() << endl;
    cout << n2.getNumSorte() << endl;

    return 0;
}
