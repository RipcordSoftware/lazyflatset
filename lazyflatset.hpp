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
        auto iter = std::lower_bound(coll_.begin(), coll_.end(), k, Less{});
        if (iter != coll_.end() && Equal{}(*iter, k)) {
            *iter = k;
        } else {
            iter = std::search_n(tempColl_.begin(), tempColl_.end(), 1, k, Equal{});
            if (iter != tempColl_.end()) {
                *iter = k;
            } else {            
                if (tempColl_.size() == maxUnsortedEntries_) {
                    flush();
                }

                tempColl_.push_back(k);
            }
        }
    }
    
    bool empty() const {
        return coll_.empty() && tempColl_.empty();
    }
    
    void clear() {
        coll_.clear();
        tempColl_.clear();
    }
    
    void reserve(size_type n) {
        coll_.reserve(n);
    }
    
    size_type size() const {
        return coll_.size() + tempColl_.size();
    }
    
    size_type count(const value_type& k) const {
        size_type found = 0;
        
        auto iter = std::lower_bound(coll_.begin(), coll_.end(), k, Less{});
        if (iter != coll_.end() && Equal{}(*iter, k)) {
            found = 1;
        } else {
            iter = std::search_n(tempColl_.begin(), tempColl_.end(), 1, k, Equal{});
            if (iter != tempColl_.end()) {
                found = 1;
            }
        }
        
         return found;
    }
    
    bool find(const value_type& k, value_type& v) {
        auto found = false;
        
        auto iter = std::lower_bound(coll_.begin(), coll_.end(), k, Less{});
        if (iter != coll_.end() && Equal{}(*iter, k)) {
            v = *iter;
            found = true;
        } else {
            iter = std::search_n(tempColl_.begin(), tempColl_.end(), 1, k, Equal{});
            if (iter != tempColl_.end()) {
                v = *iter;
                found = true;
            }
        }
        
         return found;
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
            auto start = tempColl_.cbegin(), sourceIter = start;
            auto targetIter1 = std::upper_bound(coll_.cbegin(), coll_.cend(), *sourceIter++, Less{});            
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