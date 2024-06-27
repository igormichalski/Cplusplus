    //Implemente uma classe para representar matrizes de números complexos (n x m), usando
    //alocação dinâmica. Forneça métodos para alterar e ler as células da matriz, além de
    //métodos para a adição e subtração de matrizes de números complexos. Escreva uma
    //aplicação para testar as funcionalidades implementadas.


    #include <iostream>

    using namespace std;

    class NumComplexo{
    private:
        int real;
        int imaginario;
        char i;

    public:
        NumComplexo(int real, int imaginario){
            this->real = real;
            this->imaginario = imaginario;
            this->i = 'i';
        }

        int getReal() const{
            return real;
        }

        int getImaginario() const{
            return imaginario;
        }

        char getI() const{
            return i;
        }

        friend NumComplexo operator+(const NumComplexo &a, const NumComplexo &b) {
            return NumComplexo(a.real + b.real, a.imaginario + b.imaginario);
        }

        friend ostream& operator<<(ostream &os, const NumComplexo &N){
            os << N.getReal() << " + " << N.getImaginario() << N.getI();   
            return os;    
        }

    };


    class Matriz{
    private:
        NumComplexo **matriz;
        int i, j;

    public:
        Matriz(int i, int j){
            this->i = i;
            this->j = j;
            matriz = (NumComplexo **) malloc(i * sizeof(NumComplexo));
            for(int k=0; k<i; k++)
                matriz[k] = (NumComplexo *) malloc( j * sizeof(NumComplexo));
        }

        ~Matriz(){
            for(int k=0; k<i; k++)
                free(matriz[k]);
            free(matriz);
        }

        NumComplexo getNumComplexo(int x, int y) const{
            return matriz[x][y];
        } 

        void setNumComplexo(int x, int y, const NumComplexo &N){
            matriz[x][y] = N;
        }

        Matriz* operator+(const Matriz &M) const {
            Matriz *resultado = new Matriz(2, 2);
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j) {
                    resultado->setNumComplexo(i, j, matriz[i][j] + M.getNumComplexo(i,j));
                }
            }
            return resultado;
        }

        friend ostream& operator<<(ostream& os, const Matriz &M){
            os << M.getNumComplexo(0,0) << " | " << M.getNumComplexo(0,1) << endl
            << M.getNumComplexo(1,0) << " | " << M.getNumComplexo(1,1) << endl;
            return os;
        }


    };

    int main(){

        //So funciona com matriz 2x2.

        Matriz *M = new Matriz(2,2);
        Matriz *M2 = new Matriz(2,2);

        NumComplexo Igor(4,5);
        NumComplexo Kauan(9,5);
        NumComplexo Nicolas(48,7);
        NumComplexo Agatha(6,7);

        M->setNumComplexo(0,0,Igor);
        M->setNumComplexo(0,1,Kauan);
        M->setNumComplexo(1,0,Nicolas);
        M->setNumComplexo(1,1,Agatha);

        cout << "M" << endl;
        cout << *M;

        M2->setNumComplexo(0,0,Igor);
        M2->setNumComplexo(0,1,Kauan);
        M2->setNumComplexo(1,0,Nicolas);
        M2->setNumComplexo(1,1,Agatha);

        cout << "M2" << endl;
        cout << *M2;

        Matriz *M3 = *M + *M2;

        cout << "M3" << endl;
        cout << *M3;

        delete M;
        delete M2;
        delete M3;

        return 0;
    }