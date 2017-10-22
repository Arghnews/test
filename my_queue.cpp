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
#include <string>

// TODO: variadic args pushing? can it be done? ie. q.push(5,6,7)
// TODO: initialiser list construction
// TODO: concat function
// TODO: write tests? :D

template <typename T>
class My_Queue {

    public:
        using container_type = std::deque<T>;
        using value_type = typename container_type::value_type;
        using size_type = typename container_type::size_type;
        using reference = typename container_type::reference;
        using const_reference = typename container_type::const_reference;
        using iterator = typename container_type::iterator;
        using const_iterator = typename container_type::const_iterator;
        using QT = My_Queue<T>;

        bool empty() const {
            return m_q.empty();
        }
        size_type size() const {
            return m_q.size();
        }
        void push(const T& item) {
            std::cout << "Copy push " << item << "\n";
            m_q.push_back(item);
        }
        void push(T&& item) {
            std::cout << "Move push " << item << "\n";
            m_q.push_back(std::move(item));
        }
        T& front() {
            return m_q.front();
        }
        const T& front() const {
            return m_q.front();
        }
        T& back() {
            return m_q.back();
        }
        const T& back() const {
            return m_q.back();
        }
        void pop() {
            m_q.pop_front();
        }
        template <typename... Args>
        void emplace(Args&&... args) {
            m_q.emplace_back(std::forward<Args>(args)...);
        }

        void swap(QT& q) noexcept {
            using std::swap;
            swap(m_q, q.underlying());
        }

        // haven't bothered with too many noexcepts at least yet
        // want to read up more first
        iterator begin() {
            return m_q.begin();
        }
        iterator end() {
            return m_q.end();
        }
        const_iterator begin() const {
            return m_q.cbegin();
        }
        const_iterator end() const {
            return m_q.cend();
        }

        My_Queue() {}
        My_Queue(const QT& q) : m_q(q.underlying()) {}
        My_Queue(QT&& q) : m_q(std::move(q.underlying())) {}

        /*QT& operator=(const QT& q) {
            m_q = q.underlying();
            return *this;
        }
        QT& operator=(QT&& q) {
            q = std::move(q.underlying());
            return *this;
        }*/
        QT& operator=(const QT&) = default;
        QT& operator=(QT&&) = default;

        friend void swap(QT& qa, QT qb) {
            using std::swap;
            swap(qa.underlying(), qb.underlying());
        }

        friend std::ostream& operator<<(std::ostream& os, const QT& q) {
            if (q.empty()) {
                return os;
            }
            auto i = q.begin();
            os << *i++;
            for (; i != q.end(); ++i) {
                os << ", " << *i;
            }
            return os;
        }

    protected:
        container_type& underlying() {
            return m_q;
        }
        const container_type& underlying() const {
            return m_q;
        }

    private:
        std::deque<T> m_q;
};

int main() {

    auto spacer = [] () { std::cout << "\n-----------\n"; };
    std::cout << "Hi" << "\n";
    My_Queue<std::string> q;
    std::string long_string = "hi there from whatever I am trying not to get SSOed away so I can see when moved from ya know";
    for (int i=0; i<2; ++i) {
        q.push(std::to_string(i) + long_string);
    }
    q.push(long_string);
    std::cout << "Original long string b4: " << long_string << "\n";
    q.push(std::move(long_string));
    std::cout << "Original long string after: " << long_string << "\n";
    std::cout << "-----\n\n";
    /*while (q.size() > 0) {
        std::cout << q.front() << "\n";
        q.pop();
    }*/
    const auto f = [] (const auto& my_q) {
        for (const auto& i: my_q) {
            std::cout << i << "\n";
        }
    };
    f(q);

    spacer();
    My_Queue<int> q1;
    My_Queue<int> q2;
    q1.push(1);
    q2.push(2);
    q1.swap(q2);
    std::cout << q1.front() << "\n";
    std::cout << q2.front() << "\n";

    spacer();
    My_Queue<std::pair<int,std::string>> q4;
    q4.emplace(3,"how cool to get to use forwarding!");
    std::cout << q4.front().first << " " << q4.front().second << "\n";

    spacer();
    My_Queue<int> q5;
    My_Queue<int> q6;
    q5.push(5);
    q6.push(6);
    q6 = q5;
    std::cout << q6.front() << "\n";
    using std::swap;
    swap(q5,q6);

    spacer();
    My_Queue<int> q7;
    q7.push(3);
    q7.push(4);
    q7.push(5);

    std::cout << q7 << "\n";
    std::cout << decltype(q7)(q7) << "\n";

}
