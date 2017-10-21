#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <string>
#include <iterator>

static int runs = 0;

std::string p(const std::vector<int>& a);

std::vector<int> qs(const std::vector<int>& list, const int& pivot_pos) {
    const int& pivot = list[pivot_pos];
    std::vector<int> sorted;
    sorted.reserve(list.size());
    //std::vector<int> lower;
    //std::vector<int> higher;
    runs += 2;

    auto less_than = [&] (const int& elem) -> bool {
        //std::cout << elem << " vs " << pivot << "\n";
        return elem < pivot;
    };

    //auto marker = list.begin();
    //std::advance(marker, pivot_pos);
    //std::cout << "Marker at:" << *marker << "\n";

    std::copy_if(
            list.begin(),
            list.end(),
            std::back_inserter(sorted),
            less_than);

    auto greater_than = [&] (const int& elem) -> bool {
        //std::cout << elem << " vs " << pivot << "\n";
        return elem > pivot;
    };

    sorted.emplace_back(pivot);
    //std::advance(marker, 1);

    std::copy_if(
            //std::advance(list.begin(), pivot_pos + 1),
            list.begin(),
            list.end(), 
            std::back_inserter(sorted),
            greater_than);
    std::cout << p(sorted) << "\n";
    return sorted;
}

int main() {
    std::vector<int> list = { 7,6,5,4,3,2,1 };
    const int size = list.size();
    std::cout << "Started with: " << p(list) << "\n";
    for (int i=0; i<size; ++i) {
        list = qs(list, size - 1 - i);       
        std::cout << p(list) << "\n";
    }
    std::cout << "Runs:" << runs << "\n";
}

std::string p(const std::vector<int>& a) {
    std::string s;
    for (const auto bla: a) {
        s += std::to_string(bla) + " ";
    }
    return s;
}
