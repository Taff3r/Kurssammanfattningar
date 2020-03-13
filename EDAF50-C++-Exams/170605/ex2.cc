#include <iostream>
int main() {
    int covfefe_count = 34567890;
    std::cout << "Covfefe count: " + covfefe_count << std::endl;
}

// Segfaults happens when the pointer points to the wrong place in memory. A place which is not allocated for our program. 
// Since the result of "Covfefe count:" is char* (char pointer) we then add 34567890 bytes to that counter which changes the position of our pointer
// to a place outside our allocated memory.
// If you want to fix the program instead do `std::cout << "Covfefe count: " << covfefe_count << std::endl;`
