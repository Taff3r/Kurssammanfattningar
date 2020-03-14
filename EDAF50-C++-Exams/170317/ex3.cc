template <typename BackInsertable>
class back_inserter_iterator {
public:
    explicit back_inserter_iterator(BackInsertable& c): c(c) {};
    template <typename V>
    back_inserter_iterator<BackInsertable>& operator = (const V& e){
        c.push_back(e);
        return *this;
    }
    back_inserter_iterator& operator *(){return *this;}
    back_inserter_iterator& operator ++(){return *this;}
    back_inserter_iterator& operator ++(int){return *this;}
private:
   BackInsertable& c; 
};

template <typename BackInsertable>
inline back_inserter_iterator<BackInsertable> back_inserter(BackInsertable& c){
    return back_inserter_iterator<BackInsertable>(c);
}

