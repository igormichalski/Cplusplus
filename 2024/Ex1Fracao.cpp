#include <iostream>

using namespace std;

class FacNumber{
private:
    int num, den;

public:
    FacNumber(const int num=0, const int den=1): num(num),den(den)
    {}
    ~FacNumber()
    {}

    void setDen(const int den){
        this->den = den;
    }
    void setNum(const int num){
        this->num = num;
    }
    int getDen() const {
        return den;
    }
    int getNum() const {
        return num;
    }
    FacNumber mult(FacNumber other) const {
        return FacNumber(num * other.num, den * other.den);
    }
};

int main(){
    FacNumber numfrac(5,2), numfrac2(1,6), fracOther;

    cout<<numfrac.getNum()<<'/'<<numfrac.getDen()<<endl;

    cout << numfrac2.getNum() << "/" << numfrac2.getDen() << endl;

    fracOther = numfrac2.mult(numfrac); // Multiplica frações

    cout << fracOther.getNum() << "/" << fracOther.getDen() << endl;

    return 0;
}