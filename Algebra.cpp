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
        double _exponent;

    public:
        Monomial(double coeff, double exponent) {
            this->_coeff = coeff;
            this-> _exponent = exponent;
        }

        double evaluateAt(double x) {
            return _coeff * (pow(x, _exponent));
        }
        
        Monomial operator+(Monomial& other) {
            if(other._exponent != this->_exponent) {
                throw "Incompatible exponents! Use alike exponents";
            } else {
                Monomial mon = Monomial((this->_coeff + other._coeff), this->_exponent);
                return mon;
            }
        }

        std::string to_string() {
            std::string ret;
            // floor((x * 100) + 0.5)/100;

            if(this->_coeff == int(this->_coeff)){
                ret = std::to_string(int(_coeff));
            } else {
                ret = std::to_string((((std::floor(_coeff) * 100) + 0.5) / 100));
            }
           
            ret += "x^";

            if(this->_exponent == int(this->_exponent)){
                ret += std::to_string(int(_exponent));
            } else {
                ret += "(";
                ret += std::to_string((((std::floor(_exponent) * 100) + 0.5) / 100));
                ret += ")";
            }
            return ret;
        }

        double exp() {
            return this->_exponent;
        }

        double coeff() {
            return this->_coeff;
        }

    };

    class Polynomial : public Expr {

    // collection (sum) of monomials for more complex expressions

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
    
}

int main(int argc, char const *argv[])
{
    std::cout << "Monomial test: " << std::endl;
    std::cout << "---------------------------------" << std::endl;
    
    Algebra::Monomial m2x3 = Algebra::Monomial(2, 3);
    std::cout << m2x3.to_string() << std::endl;

    std::cout << "2x^3 at 2 - Expect 16: " << m2x3.evaluateAt(2) << std::endl;
    std::cout << "2x^3 at 3 - Expect 54: " << m2x3.evaluateAt(3) << std::endl;
    std::cout << "2x^3 at 2.2 - Expect 21.296...: " << m2x3.evaluateAt(2.2) << std::endl;

    Algebra::Monomial m2_2x3 = Algebra::Monomial(2.2, 3);
    std::cout << m2_2x3.to_string() << std::endl;

    std::cout << "2.2x^3 at 2 - Expect 17.6: " << m2_2x3.evaluateAt(2) << std::endl;
    std::cout << "2.2x^3 at 3 - Expect 59.4: " << m2_2x3.evaluateAt(3) << std::endl;
    std::cout << "2.2x^3 at 2.2 - Expect 23.42...: " << m2_2x3.evaluateAt(2.2) << std::endl;

    Algebra::Monomial m2x2_8 = Algebra::Monomial(2, 2.8);
    std::cout << m2x2_8.to_string() << std::endl;

    std::cout << "2x^2.8 at 2 - Expect 13.928...: " << m2x2_8.evaluateAt(2) << std::endl;
    std::cout << "2x^2.8 at 3 - Expect 43.348...: " << m2x2_8.evaluateAt(3) << std::endl;
    std::cout << "2x^2.8 at 2.2 - Expect 18.189...: " << m2x2_8.evaluateAt(2.2) << std::endl;
    
    Algebra::Monomial m4_2x3 = m2x3 + m2_2x3;

    std::cout << "(2.2x^3 + 2x^3) at 2 - Expect 33.6: " << m4_2x3.evaluateAt(2) << std::endl;
    
    std::cout << "---------------------------------" << std::endl << std::endl;

    std::cout << "Polynomial Test:" << std::endl;
    std::cout << "---------------------------------" << std::endl;

    return 0;
}
