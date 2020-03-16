/**
 *
 * Mitt svar:
 * print1(a) => Bar
 * print1(&b) => Qux
 * print1(&c) => Bar
 *
 * print2(*a) => Bar
 * print2(b) => Qux
 * print2(c) => Bar
 *
 * print3(*a) => Foo
 * print3(b) => Foo
 * print3(b) => Foo
 */ 

#include <iostream>
struct Foo {
    virtual void print() const {std::cout << "Foo" << std::endl;}
};

struct Bar : Foo {
    virtual void print() const override {std::cout << "Bar" << std::endl;}
};

struct Qux : Bar {
    virtual void print() const override {std::cout << "Qux" << std::endl;}
};

void print1(const Foo* f){
    f->print();
}
void print2(const Foo& f){
    f.print();
}

void print3(Foo f){
    f.print();
}



int main () {
    Foo* a = new Bar;
    Bar& b = *new Qux;
    Bar  c = *new Qux;

    print1(a);
    print1(&b);
    print1(&c);
    std::cout << std::endl;
    print2(*a);
    print2(b);
    print2(c);
    std::cout << std::endl;
    print3(*a);
    print3(b);
    print3(c);
    std::cout << std::endl;
}
