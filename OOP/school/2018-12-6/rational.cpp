#include <iostream>
#include <sstream>
#include <string>


using namespace std;


class RationalException {};

class Rational {
	long nominator, denominator;
	
	long gcd(long a, long b) {
		long r = a % b;
		while(r!=0) {
			a = b;
			b = r;
			r = a % b;
		}
		return b;
	}
	
	void reduce() {
		if(this->nominator == 0) {
			this->denominator = 1;
		} else {
			long tempnum = (this->nominator < 0)? -this->nominator: this->nominator;
			long r = gcd(tempnum, this->denominator);
			
			this->nominator /= r;
			this->denominator /= r;
		}
	}
	
	void standardize() {
		if(this->denominator < 0) {
			this->nominator = - this->nominator;
			this->denominator = - this->denominator;
		}
		reduce();
	}

public:
	Rational(long num, long den) {
		if(den == 0) {
			throw RationalException();
		}
		
		this->nominator = num;
		this->denominator = den;
		
		standardize();
	}
    Rational& set_nominator(long nominator){
        this->nominator = nominator;
        return *this;
    }
    Rational& set_denominator(long denominator){
        this->denominator = denominator;
        return *this;
    }
    long get_nominator() const{
        return this->nominator;
    }
    long get_denominator() const{
        return this->denominator;
    }
	
	
    Rational& add(const Rational& other){
        this->nominator = (this->nominator * other.denominator) + (other.nominator * this->denominator);
        this->denominator = this->denominator * other.denominator;
        this->standardize();
        return *this;
    }
    Rational& subtract(const Rational& other){
        this->nominator = (this->nominator * other.denominator) - (other.nominator * this->denominator);
        this->denominator = this->denominator * other.denominator;
        this->standardize();
        return *this;
    }
    Rational& multiply(const Rational& other){
        this->nominator = this->nominator * other.nominator;
        this->denominator = this->denominator * other.denominator;
        this->standardize();
        return *this;
    }
    Rational& divide(const Rational& other){
        this->nominator = this->nominator * other.denominator;
        this->denominator = this->denominator * other.nominator;
        this->standardize();
        return *this;
    }

    Rational& operator+=(const Rational& other){
        return this->add(other);
    }
    Rational& operator-=(const Rational& other){
        return this->subtract(other);
    }
    Rational& operator*=(const Rational& other){
        return this->multiply(other);
    }
    Rational& operator/=(const Rational& other){
        return this->divide(other);
    }
	
};
    
istream& operator>>(istream& in, Rational& r) {
    char c;
    long nominator, denominator;

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
        r.set_nominator(nominator).set_denominator(denominator);
    }

    return in;
}
ostream& operator<<(ostream& out, const Rational& r){
    out << r.get_nominator() << "/" << r.get_denominator();
    return out;
}

//no time for separate parser class ;)

int main() {
    string line;
    getline(cin, line);
   // cout << "line: " << line << endl;
    while(line != "quit"){
        Rational r1(0, 1), r2(0,1);
        istringstream iss(line);
        char operation;
        cout << "> ";
        iss >> r1 >> operation;
       // cout << "rational: " << r1 << "operation: " << operation << endl;
        while(operation != '='){
            iss >> r2; 
           // cout << "rational2: " << r2 << endl;
            switch(operation){
                case '+':
                    r1 += r2;
                    break;
                case '-':
                    r1 -= r2;
                    break;
                case '*':
                    r1 *= r2;
                    break;
                case '/':
                    r1 /= r2;
                    break;
            }
            iss >> operation;
        } 
    
        cout << r1 << endl;
        getline(cin, line); 
    }
    return 0;
}
