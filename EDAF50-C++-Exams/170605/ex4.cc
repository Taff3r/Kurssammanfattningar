#include <iostream>
#include <vector>
#include <string>

/*
 * 4. Implement a template function that will work for iterators, because pointers can be cast to iterators but not the other way around.
 */
template <typename ForwardIterator> 
bool is_strict_monotonic(ForwardIterator b, ForwardIterator e) {
    bool asc{true};
    bool desc{true};
    ForwardIterator next = b; 
    next++;
    while((asc || desc) && next != e) {
        if (!(*b < *next)) asc  = false;
        if (!(*next < *b)) desc = false;
        ++b;
        ++next;
    }
    return asc || desc; // do bitwise OR 1 + 1 = 1, 0 + 1 = 1 , 1 + 0 = 1, 0 + 0 = 0
}



int main() {
    int a[] = {1,2,3};
    int b[] = {3,2,1};
    int c[] = {2,2,1};
    std::cout << is_strict_monotonic(a, a+3) << std::endl;
    std::cout << is_strict_monotonic(b, b+3) << std::endl;
    std::cout << is_strict_monotonic(c, c+3) << std::endl;
    std::vector<std::string> l = {"a", "b", "c"};
    std::vector<std::string> l2 = {"c", "b", "c"};
    std::cout << is_strict_monotonic(l.begin(), l.end()) << std::endl;
    std::cout << is_strict_monotonic(l2.begin(), l2.end()) << std::endl;
}
