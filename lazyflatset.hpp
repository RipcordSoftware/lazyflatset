#ifndef RS_LAZY_FLAT_SET
#define RS_LAZY_FLAT_SET

#include <vector>
#include <algorithm>
#include <type_traits>

namespace rs {
    
template <class Key, class Less = std::less<Key>, class Equal = std::equal_to<Key>, class Alloc = std::allocator<Key>>
class LazyFlatSet {
public:
    using size_type = typename std::vector<Key>::size_type;
    using value_type = Key;
    using reference = typename std::conditional<std::is_fundamental<Key>::value || std::is_pointer<Key>::value, value_type, value_type&>::type;
    using const_reference = typename std::conditional<std::is_fundamental<Key>::value || std::is_pointer<Key>::value, value_type, const value_type&>::type;
    
    LazyFlatSet(unsigned maxUnsortedEntries = 32) : maxUnsortedEntries_(maxUnsortedEntries) {
        tempColl_.reserve(maxUnsortedEntries);
    }
    
    void insert(const value_type& k) {
        auto found = std::lower_bound(coll_.begin(), coll_.end(), k, Less{});
        if (found != coll_.end() && Equal{}(*found, k)) {
            *found = k;
        } else {
            auto found = std::search_n(tempColl_.begin(), tempColl_.end(), 1, k, Equal{});
            if (found != tempColl_.end()) {
                *found = k;
            } else {            
                if (tempColl_.size() == maxUnsortedEntries_) {
                    flush();
                }

                tempColl_.push_back(k);
            }
        }
    }
    
    bool empty() {
        return coll_.empty() && tempColl_.empty();
    }
    
    void clear() {
        coll_.clear();
        tempColl_.clear();
    }
    
    void reserve(size_type n) {
        coll_.reserve(n);
    }
    
    size_type size() {
        return coll_.size() + tempColl_.size();
    }
    
    const_reference operator[](size_type n) const {
        flush();
        return coll_[n];
    }
    
private:
    void flush() const {
        if (tempColl_.size() > 0) {        
            std::sort(tempColl_.begin(), tempColl_.end(), Less{});

            // TODO: optimize the range insert
            auto targetIter1 = coll_.cend();
            auto start = tempColl_.cbegin(), sourceIter = start;
            for (; sourceIter != tempColl_.cend(); ++sourceIter) {
                auto targetIter2 = std::upper_bound(coll_.cbegin(), coll_.cend(), *sourceIter, Less{});
                if (targetIter1 != targetIter2) {
                    coll_.insert(targetIter1, start, sourceIter);
                    start = sourceIter;
                    targetIter1 = targetIter2;
                }
            }

            if (start != sourceIter) {
                coll_.insert(targetIter1, start, sourceIter);
            }

            tempColl_.clear();
        }
    }   
    
    const unsigned maxUnsortedEntries_;
    
    mutable std::vector<Key, Alloc> coll_;
    mutable std::vector<Key, Alloc> tempColl_;
};
    
}

#endif