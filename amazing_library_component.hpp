#ifndef THIS_AMAZING_LIBRARY_COMPONENT
#define THIS_AMAZING_LIBRARY_COMPONENT

#include <iosfwd>

class Component {
    public:
        Component(const int i);
    private:
        int i;
    friend std::ostream& operator<<(std::ostream&, const Component&);
};

#endif
