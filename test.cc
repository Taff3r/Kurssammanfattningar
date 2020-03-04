#include <iostream>
#include <memory>
struct Foo {
    const int myNumber = 3;
    void printMyNumber(){
        std::cout << this->myNumber << std::endl;
    }
};

int main(){
    Foo* ptr = new Foo;
    auto uPtr = std::make_unique<Foo>();
    Foo foo;
    ptr->printMyNumber();
    uPtr->printMyNumber();
    foo.printMyNumber();
    delete ptr;
}
