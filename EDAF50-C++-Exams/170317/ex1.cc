template <typename InputIterator, typename OutputIterator>
OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator result){
    InputIterator adj = first;
    *result++ = *first++;
    while (first != last) {
        *result++ = *first++ - *adj++;
    }
    return result;
}

#include <iostream>
#include <vector>
#include <algorithm>
#define uint unsigned int
void print(int v[], uint s){
    for (uint i = 0; i < s; ++i){
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
    if(s == 1){
        return;
    }
    int o[s];
    adjacent_difference(v, v+s, o);
    return print(o + 1, s - 1);
}
int main() {
    // Read
    int i;
    std::vector<int> numbers;
    while(std::cin >> i){
       numbers.push_back(i);
    }

    int v[numbers.size()];
    for(uint i = 0; i < numbers.size(); ++i){
       v[i] = numbers[i];
    }
    print(v, numbers.size());
}
