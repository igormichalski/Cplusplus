#include <iostream>

using namespace std;

//Crie uma class Celsius e seus operadores

class Celsius{
private:
    float temperatura;

public:
    Celsius(float temperatura){
        this->temperatura = temperatura;
    }

    void setTemperatura(float temperatura){
        this->temperatura = temperatura;
    }

    float getTemperatura() const{
        return temperatura;
    }

    //Soma e Sub
    Celsius operator+(const Celsius &outro){
        return Celsius(temperatura + outro.temperatura);
    }

    Celsius operator-(const Celsius &outro){
        return Celsius(temperatura - outro.temperatura);
    }

    //Pre --&
    Celsius &operator++(){
        ++temperatura;
        return *this;
    }

    Celsius &operator--(){
        --temperatura;
        return *this;
    }

    //Pos
    Celsius operator++(int){
        Celsius temp = *this;
        temp.temperatura++;
        return temp;
    }

    Celsius operator--(int){
        Celsius temp = *this;
        temp.temperatura--;
        return temp;
    }

    //bool
    bool operator==(const Celsius &outro){
        return temperatura == outro.temperatura;
    }
    bool operator!=(const Celsius &outro){
        return temperatura != outro.temperatura;
    }
    bool operator>=(const Celsius &outro){
        return temperatura >= outro.temperatura;
    }
    bool operator<=(const Celsius &outro){
        return temperatura <= outro.temperatura;
    }
    bool operator>(const Celsius &outro){
        return temperatura > outro.temperatura;
    }
    bool operator<(const Celsius &outro){
        return temperatura < outro.temperatura;
    }

};


class Fahrenheit{
private:
    float temperatura;

public:
    Fahrenheit(float temperatura){
        this->temperatura = temperatura;
    }
    Fahrenheit(const Celsius &outro){  //Celsius To Fahrenheit
        this->temperatura = (outro.getTemperatura() * (9.0/5.0)) + 32;
    }

    void setTemperatura(float temperatura){
        this->temperatura = temperatura;
    }

    float getTemperatura() const{
        return temperatura;
    }

    //Soma e Sub
    Fahrenheit operator+(const Fahrenheit &outro){
        return Fahrenheit(temperatura + outro.temperatura);
    }

    Fahrenheit operator-(const Fahrenheit &outro){
        return Fahrenheit(temperatura - outro.temperatura);
    }

    //Pre --&
    Fahrenheit &operator++(){
        ++temperatura;
        return *this;
    }

    Fahrenheit &operator--(){
        --temperatura;
        return *this;
    }

    //Pos
    Fahrenheit operator++(int){
        Fahrenheit temp = *this;
        temp.temperatura++;
        return temp;
    }

    Fahrenheit operator--(int){
        Fahrenheit temp = *this;
        temp.temperatura--;
        return temp;
    }

    //bool
    bool operator==(const Fahrenheit &outro){
        return temperatura == outro.temperatura;
    }
    bool operator!=(const Fahrenheit &outro){
        return temperatura != outro.temperatura;
    }
    bool operator>=(const Fahrenheit &outro){
        return temperatura >= outro.temperatura;
    }
    bool operator<=(const Fahrenheit &outro){
        return temperatura <= outro.temperatura;
    }
    bool operator>(const Fahrenheit &outro){
        return temperatura > outro.temperatura;
    }
    bool operator<(const Fahrenheit &outro){
        return temperatura < outro.temperatura;
    }

    operator Celsius(){
        return Celsius((temperatura - 32) * (5.0/9.0));       //Fahrenheit para Celsius
    }

};


class Kelvin{
private:
    float temperatura;

public:
    Kelvin(float temperatura){
        this->temperatura = temperatura;
    }
    Kelvin(const Celsius &outro){  //Celsius To Kelvin
        this->temperatura = outro.getTemperatura() + 273.15;
    }

    Kelvin(const Fahrenheit &outro){  //Fah To Kelvin
        this->temperatura = ((outro.getTemperatura() - 32) * (5.0/9.0)) + 273.15; 
    }

    void setTemperatura(float temperatura){
        this->temperatura = temperatura;
    }

    float getTemperatura() const{
        return temperatura;
    }

    //Soma e Sub
    Kelvin operator+(const Kelvin &outro){
        return Kelvin(temperatura + outro.temperatura);
    }

    Kelvin operator-(const Kelvin &outro){
        return Kelvin(temperatura - outro.temperatura);
    }

    //Pre --&
    Kelvin &operator++(){
        ++temperatura;
        return *this;
    }

    Kelvin &operator--(){
        --temperatura;
        return *this;
    }

    //Pos
    Kelvin operator++(int){
        Kelvin temp = *this;
        temp.temperatura++;
        return temp;
    }

    Kelvin operator--(int){
        Kelvin temp = *this;
        temp.temperatura--;
        return temp;
    }

    //bool
    bool operator==(const Kelvin &outro){
        return temperatura == outro.temperatura;
    }
    bool operator!=(const Kelvin &outro){
        return temperatura != outro.temperatura;
    }
    bool operator>=(const Kelvin &outro){
        return temperatura >= outro.temperatura;
    }
    bool operator<=(const Kelvin &outro){
        return temperatura <= outro.temperatura;
    }
    bool operator>(const Kelvin &outro){
        return temperatura > outro.temperatura;
    }
    bool operator<(const Kelvin &outro){
        return temperatura < outro.temperatura;
    }

    operator Celsius(){
        return Celsius(temperatura - 273.15);  //Kelvin para Celsius
    }

    operator Fahrenheit(){
        return Fahrenheit(((temperatura - 273.15) * (9.0/5.0)) + 32);  //Kelvin para Fah
    }

};



int main(){

    Celsius T1(100);
    Fahrenheit T2(50);
    Kelvin T3(150);

    cout << "Celsius: " << T1.getTemperatura() << endl;
    cout << "Fahrenheit: " << T2.getTemperatura() << endl;
    cout << "Kelvin: " << T3.getTemperatura() << endl << endl;

    Celsius C1 = T2; //Fahrenheit -> Celsius
    Fahrenheit C2 = T1; //Celsius - > Fahrenheit

    Kelvin C3 = T1; //Celsius - > Kelvin
    Celsius C4 = T3; //Kelvin - > Celsius

    Fahrenheit C5 = T3; //Kelvin -> Fahrenheit
    Kelvin C6 = T2; //Fahrenheit -> Kelvin

    cout << "Fahrenheit -> Celsius: " << C1.getTemperatura() << endl;
    cout << "Celsius - > Fahrenheit: " << C2.getTemperatura() << endl;
    cout << "Celsius - > Kelvin: " << C3.getTemperatura() << endl;
    cout << "Kelvin - > Celsius: " << C4.getTemperatura() << endl;
    cout << "Kelvin - > Fahrenheit: " << C5.getTemperatura() << endl;
    cout << "Fahrenheit - > Kelvin: " << C6.getTemperatura() << endl;

    return 0;
}
