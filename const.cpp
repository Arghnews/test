#include <sstream>
#include <iostream>

class Conster {
    private:
        int c;
    public:
        Conster() = default;
        Conster(int i) : c(i) {}
        int& operator[] (int i) {
            std::cout << "Non const called\n";
            return c;
        }
        const int& operator[] (int i) const {
            std::cout << "Const called\n";
            return c;
        }
    friend std::ostream& operator<<(std::ostream& o, const Conster& c);
};

std::ostream& operator<<(std::ostream& o, const Conster& c) {
    return o << c.c;
}

int main() {
    Conster c{};
    std::cout << c << "\n";
}
