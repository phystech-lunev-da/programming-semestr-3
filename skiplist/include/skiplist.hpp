
#include <iterator>

template<typename T> 
class SkipList {
    SkipList();

    SkipList(const SkipList&);
    SkipList(SkipList&&);

    bool empty();
    unsigned size();
    void insert(T);



};