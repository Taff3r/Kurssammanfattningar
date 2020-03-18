# Does the class own a pointer?
If so:
+ Does it define a *destructor*, *copy constructor*, and *copy assignment operator*?

# Does a function take an object by value?
If so:
+ Does the object define a copy assignment operator?

# Does the function affect the internal state of the object?
If not:
+ The function should be declared `const`!
If it does:
+ Do not declare it const!
# Does the function change the value of the arguments?
If not:
+ Declare them as `const`!

# Is the object to be used in a std:: algo with iterators as arguments?
If so:
+ Does the object define an iterator with the `begin` and `end` functions?

# Are you implementing template with iterators as arguments?
If so:
+ Are you taking the iterators by value or by reference?
+ Are you using the proper tags for the iterators?
    - Input iterators can only move forward, and can only be read from.
    - Output iterators can only move forward, and can only be written to.
    - Forward iterators can only move forward, and can be both written to and read from.

# Are you implementing an iterator for your class?
If so follow these steps:
+ **Before** the definition of your class make a forwards declaration of the iterator:
```c++
class SimpleVIterator;
```
- Then in your class declare the iterator as a `friend`.
```c++
    friend class SimpleVIterator<T>;
```
- Then define the type `iterator` as the iterator class.

```c++
typedef SimpleVIterator<T> iterator;
iterator begin() {retrun SimpleVIterator<T>(*this, 0)}
```
- In the implementation of your iterator make sure the iterator extends the correct kind of iterator.
```c++
template <typename T>
class SimpleVIterator : public std::iterator<std::forward_iterator_tag, void, void, void, void> {
    //...
};
```
- Make sure the iterator has a `reference` to your object and takes it as a referece to the constructor.

```c++
SimpleVIterator(SimpleV<T>& v, size_t pos): v(v), pos(pos) {}

// ...


private:
    SimpleV<T>& v;
    size_t pos;
```
- Make sure the iterator(for forward_iterators) has implemented the following operations and functions.
    + `T& operator[] (size_t pos)`
    + `SimpleVIterator& operator++ ()`
    + `T& operator *  ()`
    + `bool operator != (const SimpleVIterator& rhs)`
    + `SimpleVIterator& operator = (const SimpleVIterator& rhs)`


# Are you comparing objects?
If so:
+ Does the object define behaviour for the following operators? :
    - `<`
    - `>`
    - `==`
    - `!=`
