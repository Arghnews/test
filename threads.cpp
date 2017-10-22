#include <iostream>
#include <sstream>
#include <thread>
#include <functional>
#include <chrono>
#include <mutex>
#include <queue>
#include <deque>
#include <iterator>
#include <utility>

void sleep(const unsigned long ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

// std::queue is not meant to be subclassed/inherited from
// methods are not virtual
// therefore this is a bit of a monster

// need to read up further on public/private inherit keyword
// still forget/don't understand
template <
    typename T, 
    typename Container = std::deque<T>,
    typename Parent = std::queue<T,Container> >
class Safe_Q : Parent {
    public:
        Safe_Q() {}

        bool empty() const {
            return size() == 0;
        }

        std::size_t size() const {
            return this->size();
        }

        T& front() {
            return this->front();
        }

        const T& front() const {
            return this->front();
        }

        void push(const T& item) {
            std::unique_lock<std::mutex> lock(m_mut);
            sleep(10);
            std::cout << "Have mutex, adding " << item << "\n";
            std::cout << this->size() << "\n";
            Parent::push(item);
            std::cout << this->size() << "\n";
        }

        using iterator = typename Container::iterator;
        iterator begin() {
            return Parent::c.begin();
        }
        iterator end() {
            return Parent::c.end();
        }
        //auto begin() -> decltype(std::declval<Container>().cbegin()) {
        //auto begin() -> decltype(typename Container::const_iterator()) {
        using const_iterator = typename Container::const_iterator;
        const_iterator begin() const {
            return Parent::c.cbegin();
        }
        const_iterator end() const {
            return Parent::c.cend();
        }

        std::ostream& print() const {
            std::ostream& os = std::cout;
            if (this->empty()) {
                return os;
            }
            auto i = this->begin();
            os << *i++;
            for (; i != end(); ++i) {
                os << ", " << *i;
            }
            return os;
        }

        friend std::ostream& operator<<(std::ostream& os, const Safe_Q<T,Container>& q) {
            return q.print();
        }

    private:
        std::mutex m_mut;
};

int main() {

    std::cout << "Hi from main" << "\n";

    std::mutex mut;

    Safe_Q<int> q;
    q.push(3);
    q.push(4);
    q.push(5);
    std::cout << q << "\n";
    //std::cout << q.front() << "\n";

}

