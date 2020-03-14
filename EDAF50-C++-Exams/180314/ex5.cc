class Foo {
public:
    // Solution 1 
    Foo() = default;
    Foo(int i) {x = i;}
private:
    int x;
};
#include <iostream>
class Bar {
public:
    // Solution 2
    Bar(int i) : a{i}{}
private:
    Foo a;
};

/*
 * 5a. 
 * In the constructor of Bar it tries to call the constructor Foo() without any arguments.
 * The solution is to either to add  a default constructor for Foo. OR Use the correct initzilation list in construtor for Bar.
 */
