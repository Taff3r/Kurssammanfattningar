class A {
public:
    A(int i) {x = i;}
    int x;
};

class B {
public:
    B(int i) : a(i){}
    A a;
};
