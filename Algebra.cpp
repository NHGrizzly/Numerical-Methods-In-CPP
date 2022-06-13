#include <cmath>
#include <map>
#include <iostream>

namespace Algebra {

// base namespace, change later

    class Expr {

    };

    class Monomial : public Expr {

    // base unit to store and handle evaluation of simple functions
        
    private:
        double _coeff;
        double exponent;

    public:
        Monomial(double coeff, double exponent) {
            this->_coeff = coeff;
            this-> exponent = exponent;
        }

        double evaluateAt(double x) {
            return _coeff * (pow(x, exponent));
        }
        
        Expr operator+(Monomial& other);

        double exp() {
            return this->exponent;
        }

        double coeff() {
            return this->_coeff;
        }

    };

    class Polynomial : public Expr {

    // sum of monomials for more complex expressions

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

        void insert(Monomial m) {
            this->monos.emplace(m.exp(), m);
        }

        Expr operator+(Monomial m) {
            if(this->monos.count(m.exp())) {
                Monomial n = monos.at(m.exp());
                this->monos.erase(m.exp()); // better solution possible here
                this->monos.emplace(m.exp(), Monomial(m.exp(), n.coeff() + m.coeff()));
                return *this;
            }
        }
    };

    Expr Monomial::operator+(Monomial& other) {
        if(other.exponent != this->exponent){
            Polynomial poly;
            poly.insert(*this);
            poly.insert(other);
            return poly;
        } else {
            Monomial mon = Monomial((this->_coeff + other._coeff), this->exponent);
            return mon;
        }
    }
    
}

int main(int argc, char const *argv[])
{
    std::cout << "Monomial test: " << std::endl;
    std::cout << "---------------------------------" << std::endl;

    Algebra::Monomial m2x3 = Algebra::Monomial(2, 3);

    std::cout << "2x^3 at 2 - Expect 16: " << m2x3.evaluateAt(2) << std::endl;
    std::cout << "2x^3 at 3 - Expect 54: " << m2x3.evaluateAt(3) << std::endl;
    std::cout << "2x^3 at 2.2 - Expect 21.296...: " << m2x3.evaluateAt(2.2) << std::endl;

    Algebra::Monomial m2_2x3 = Algebra::Monomial(2.2, 3);

    std::cout << "2.2x^3 at 2 - Expect 17.6: " << m2_2x3.evaluateAt(2) << std::endl;
    std::cout << "2.2x^3 at 3 - Expect 59.4: " << m2_2x3.evaluateAt(3) << std::endl;
    std::cout << "2.2x^3 at 2.2 - Expect 23.42...: " << m2_2x3.evaluateAt(2.2) << std::endl;

    Algebra::Monomial m2x2_8 = Algebra::Monomial(2, 2.8);

    std::cout << "2x^2.8 at 2 - Expect 13.928...: " << m2x2_8.evaluateAt(2) << std::endl;
    std::cout << "2x^2.8 at 3 - Expect 43.348...: " << m2x2_8.evaluateAt(3) << std::endl;
    std::cout << "2x^2.8 at 2.2 - Expect 18.189...: " << m2x2_8.evaluateAt(2.2) << std::endl;
    
    std::cout << "---------------------------------" << std::endl << std::endl;

    std::cout << "Polynomial Test:" << std::endl;
    std::cout << "---------------------------------" << std::endl;

    

    return 0;
}
