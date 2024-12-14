
#include <random>

// Класс монетки
// 0 - решка
// 1 - орел
class Coin {
public:
    Coin(float, unsigned);
    int flip();
    int sum();
private:
    std::default_random_engine reng;
    std::discrete_distribution<int> dstr;
};

Coin::Coin(float p, unsigned seed) : dstr({1 - p, p}), reng(seed) {}
int Coin::flip() { return dstr(reng);}
int Coin::sum() {
    int count = 0;
    while(this->flip() == 1) {
        count++;
    }
    return count;
}
