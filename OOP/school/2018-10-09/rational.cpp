#include <iostream>
using namespace std;

class RationalException{};

class Rational{
    private:
        long nominator;
        long denominator;
        
        long gcd(long a, long b){
            long r = a% b;
            while(r!= 0){
                a = b;
                b = r;
                r = a % b;
            }
            
            return b;
        }

        void reduce(){
            if(nominator == 0){
                denominator  = 1;
            } else {
                long tempnum = (nominator < 0) ? -nominator : nominator ;
                long r = gcd(tempnum, denominator);

                nominator /= r;
                denominator /= r;

            }
        }
        
        void standardize(){
            if(denominator  < 0){
                denominator = -denominator;
                nominator = -nominator;
            }
            reduce();
            
        }

    Rational add(Rational r1, Rational r2){
        Rational r3(0, 1);
        r3.add(r1);
        r3.add(r2);
        return r3;
    }
    Rational sub(Rational r1, Rational r2){
        Rational r3(0, 1);
        r3.add(r1);
        r3.sub(r2);
        return r3;
    }

    public:

        Rational(long num, long den){
            this->nominator = num;
            this->denominator = den;
            
            if(den == 0){
                throw RationalException();
            }
            
            standardize();
        }

        

        void add(Rational other){
            this->nominator = (this->nominator * other.denominator) + (other.nominator * this->denominator) ;
            this->denominator = this->denominator * other.denominator;
            this->standardize();
        }

        void sub(Rational other){ 
            this->nominator = (this->nominator * other.denominator) - (other.nominator * this->denominator) ;
            this->denominator = this->denominator * other.denominator;
            this->standardize();
        }
        void multiply(Rational other){
            this->nominator *= other.nominator;
            this->denominator *= other.nominator;
            this->standardize();
        }
        void division(Rational other){
            Rational r = Rational(other.denominator, other.nominator);
            this->multiply(r);
        }
        
        void dump(){
            cout << "(" << nominator << "/" << denominator << ")" << endl;
        }

        Rational operator+(Rational other){
            return add(*this, other);
        }
        Rational operator+=(Rational other){
            return add(*this, other);
                        
        }
        Rational operator-(Rational other){
            return sub(*this, other);
        }


};



int main(){
    Rational r1(5,4), r2(2,4), r3(3, -6);
   // r3 = sub(r1, r2);
    //r3.dump();
    //r3 = add(r1, r2);
    //r3.dump();
    Rational r4 = r1 + r2;
    r4.dump();



    r2.add(r1);
    r2.dump();
    r2.sub(r1);
    r2.dump();
    return 0;
    
}
