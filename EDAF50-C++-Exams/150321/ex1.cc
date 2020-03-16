#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>



//1b.
template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator my_remove_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred){
    while(first != last){
        if(pred(*first)){
            ForwardIterator copy = first;
            while(pred(*copy) && copy != last){
                copy++;
            }
            if(copy == last){
                return first;
            } else {
                *first = *copy;
            }
        }
        ++first;
    }
    return first;
}
int main() {
    std::vector<int> v = {0,1,2, -3 ,-1, 0, 0};
    // 1a.
    v.erase(my_remove_if(v.begin(), v.end(), [] (const int& i) {return i < 0;}), v.end());
    for(auto& i : v){
        std::cout << i << " ";
    }
}
