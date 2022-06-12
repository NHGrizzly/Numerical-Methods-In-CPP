#include <cmath>
#include <map>

namespace Algebra {

// base namespace, change later

    class Monomial {

    // store and handle evaluation of simple functions
        
    private:
        double coeff;
        double exponent;

    public:
        Monomial(double coeff, double exponent) {
            this->coeff = coeff;
            this-> exponent = exponent;
        }

        double evaluateAt(double x) {
            return coeff * (pow(x, exponent));
        }
        
        Monomial& operator+(Monomial& other) {
            if(other.exponent != this->exponent){
                throw "Incompatible exponents!";
            } else {
                Monomial ret = Monomial((this->coeff + other.coeff), this->exponent);
                return ret;
            }
        }

    };

    class Polynomial {
    private:
        std::map<double, Monomial> monos;

    public:
        double evaluateAt(double x) {
            double sigma = 0;
            
            std::map<double, Monomial>::iterator it = monos.begin(); // start at the beginning

            while(it != monos.cend()) {
                sigma += it->second.evaluateAt(x);

                it++; // go to next monomial
            }

            return sigma;
        }

    };
    
}