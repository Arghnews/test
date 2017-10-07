#include "amazing_library_component.hpp"

#include <iostream>

Component::Component(const int i) : i(i) {
}

std::ostream& operator<<(std::ostream& os, const Component& c) {
    return os << "component " << c.i;
}

