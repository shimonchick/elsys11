#include <iostream>
#include <sstream>
using namespace std;

class RationalException{
    private:
        string message;
    public:
        RationalException(string error): message(error){}
        
        string get_message() const {
            return message;
        }

};
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


    public:

        Rational(long num, long den){
            this->nominator = num;
            this->denominator = den;
            
            if(den == 0){
                throw RationalException("Denominator can't be zero");
            }
            
            standardize();
        }

        int get_nominator() const {
            return this->nominator;
        }
        int get_denominator() const {
            return this->denominator;
        }

        Rational& set_nominator(const int nominator){
            this->nominator = nominator;
            return *this;
        }
        Rational& set_denominator(const int denominator){
            this->denominator = denominator;
            return *this;
        }

        Rational& add(const Rational& other){
            this->nominator = (this->nominator * other.denominator) + (other.nominator * this->denominator) ;
            this->denominator = this->denominator * other.denominator;
            this->standardize();
            return *this;
        }

        Rational& subtract(const Rational& other){ 
            this->nominator = (this->nominator * other.denominator) - (other.nominator * this->denominator) ;
            this->denominator = this->denominator * other.denominator;
            this->standardize();
            return *this;
        }
        Rational& multiply(const Rational& other){
            this->nominator *= other.nominator;
            this->denominator *= other.denominator;
            this->standardize();
            return *this;
        }
        Rational& divide(const Rational& other){
            Rational r = Rational(other.denominator, other.nominator);
            this->multiply(r);
            return *this;
        }
       // 
       // Rational add(const Rational& r1, const Rational& r2){
       //     Rational r3(0, 1);
       //     r3.add(r1);
       //     r3.add(r2);
       //     return r3;
       // }
       // Rational sub(const Rational& r1, const Rational& r2){
       //     Rational r3(0, 1);
       //     r3.add(r1);
       //     r3.sub(r2);
       //     return r3;
       // }
       // Rational multiply(const Rational& r1, const Rational& r2){
       //     Rational r3(1, 1);
       //     r3.multiply(r1);
       //     r3.multiply(r2);
       //     return r3;
       // }
       // Rational divide(const Rational& r1, const Rational& r2){
       //     Rational inverse(r2.get_denominator(), r2.get_nominator());
       //     return multiply(r1, inverse);
       // }

        Rational& operator+=(const Rational& other){
            return add(other);
                        
        }
        Rational& operator-=(const Rational& other){
            return subtract(other);
        }
        Rational& operator*=(const Rational& other){
            return multiply(other); 
        }
        Rational& operator/=(const Rational& other){
            return divide(other);
        }


};

istream& operator>>(istream& in, Rational& rational) {
    char c;
    int nominator, denominator;
    in >> c;
    if (c != '(') {
        in.clear(ios_base::badbit);
        return in;
    }
    in >> nominator >> c;
    if (c != '/') {
        in.clear(ios_base::badbit);
        return in;
    }
    in >> denominator >> c;
    if (c != ')') {
        in.clear(ios_base::badbit);
        return in;
    }
    if (in.good()) {
        rational.set_nominator(nominator).set_denominator(denominator);
    }
    return in;
}

ostream& operator<<(ostream& out, const Rational& rational){
    out << "(" << rational.get_nominator() <<"/"<<rational.get_denominator()<<")";
    return out;
}

class RationalCalculator{
    private:
        istream& stream;
    public:
        RationalCalculator(istream& stream_param): stream(stream_param){}
        
        void parse(){
            string line;
            char operation;
            Rational first(1, 1);
            Rational second(1, 1);
            getline(stream, line);
            while(line != "q"){
                //cout << "reading line" << endl;
                istringstream stringstream(line);
                stringstream >> first >> operation;
                while(operation != '='){
                    stringstream >> second;
                    switch(operation){
                        case '+':
                            first += second;
                            break;
                        case '-':
                            first -= second;
                            break;
                        case '*':
                            first *= second;
                            //cout << "after multiplication" <<first <<endl;
                            break;
                        case '/':
                            first /= second;
                            //cout << "after division" << first << endl;
                            break;
                    }
                    stringstream >> operation;
                }
                
                cout <<"> " <<first <<endl; 
                getline(stream, line);
            }
            cout <<">";
        }
};

int main(){
    try{
        RationalCalculator rational_calculator(cin);
        rational_calculator.parse();
    } catch(RationalException e){
        cout << e.get_message();
    }
    return 0;
    
}

