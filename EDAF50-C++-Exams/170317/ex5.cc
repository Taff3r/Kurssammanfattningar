
Foo& Foo:operator=(const Foo& that){
    // Call the = operator on super class first
    SuperFoo::operator=(that);
    // Assign as usual
    *fBar1 = *that.fBar1;
    *fBar2 = *that.fBar2;
    return *this;
}
