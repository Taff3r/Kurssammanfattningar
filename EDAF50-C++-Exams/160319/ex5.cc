#include <cstddef>
#include <algorithm>
#include <iostream>
#include <iostream>
#include <iterator>

template <typename InputIterator, typename OutputIterator, typename Comperator>
OutputIterator my_remove_copy_if(InputIterator first, InputIterator last, OutputIterator out, Comperator c){
    while(first!=last){
        if(!c(*first)){
            *out++ = *first++;
        } else {
            ++first;
        }
    }
    return out;
}
int k = 0;
bool ltc(int x) {return x < k;}
int mainOld() {
   int a[] = {5, 10, -3, 2, -8, 11};
   const size_t SIZE = sizeof(a) / sizeof(int);
   int b[SIZE];
   std::cin >> k;
   int* last = std::remove_copy_if(a, a + SIZE, b, ltc);
   int* first = b;
   while(first != last) {
       std::cout << *first ++ << std::endl; // 5 10, 2, 11
   }
   return 1;
}
int newMain() {
    int c;
    int a[] = {5, 10, -3, 2, -8, 11};
    const size_t SIZE = sizeof(a) / sizeof(int);
    int b[SIZE];
    std::cin >> c;

    int* last = std::remove_copy_if(a, a+SIZE, b, [&c] (const int& x) { return x < c;});
    int* first = b;

    while(first != last) {
        std::cout << *first ++ << std::endl;
    }

    return 0;
}

int printMain() {
    int c;
    int a[] = {5, 10, -3, 2, -8, 11};
    const size_t SIZE = sizeof(a) / sizeof(int);
    std::cin >> c;
    my_remove_copy_if(a, a+SIZE, std::ostream_iterator<int>(std::cout, " "), [&c] (const int& x) { return x < c;});
    return 0;

}
int main() {
    printMain();
}


