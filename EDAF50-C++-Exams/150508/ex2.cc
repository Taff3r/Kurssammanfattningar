#include <utility>
#include <iterator>
using std::pair;
template <typename I>
pair<typename std::iterator_traits<I>::value_type, unsigned int>
max_element(I begin, I end){
    using V = typename std::iterator_traits<I>::value_type;
    V max = *begin++;
    unsigned int count = 1;

    while (begin != end) {
        if (max == *begin){
            count++;
        }
        if (max < *begin){
            max = *begin;
            count = 1;
        }
        begin++;
    }

    std::pair<V, unsigned int> p;
    p.first = max;
    p.second = count;
    return p;
}
#include <vector>
#include <iostream>
int main(){
    std::vector<int> a = {1,2,3,4,4,4,4,2,5,1};
    std::pair<int, unsigned int> p = max_element(a.begin(), a.end());
    std::cout << p.first << " " << p.second << std::endl;
}
