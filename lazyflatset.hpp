#ifndef RS_LAZY_FLAT_SET
#define RS_LAZY_FLAT_SET

#include <vector>
#include <algorithm>
#include <type_traits>

namespace rs {
    
template <class Key, class Less = std::less<Key>, class Equal = std::equal_to<Key>, class Alloc = std::allocator<Key>>
class LazyFlatSet {
public:
    using base_collection = typename std::vector<Key, Alloc>;
    using size_type = typename base_collection::size_type;
    using iterator = typename base_collection::iterator;
    using value_type = Key;
    using reference = typename std::conditional<std::is_fundamental<Key>::value || std::is_pointer<Key>::value, value_type, value_type&>::type;
    using const_reference = typename std::conditional<std::is_fundamental<Key>::value || std::is_pointer<Key>::value, value_type, const value_type&>::type;
    
    LazyFlatSet(unsigned maxUnsortedEntries = 32) : maxUnsortedEntries_(maxUnsortedEntries) {
        unsorted_.reserve(maxUnsortedEntries);
    }
    
    void insert(const value_type& k) {
        auto iter = lower_bound_equals(coll_, k);
        if (iter != coll_.end()) {
            *iter = k;
        } else {
            iter = search_unsorted(unsorted_, k);
            if (iter != unsorted_.end()) {
                *iter = k;
            } else {            
                if (unsorted_.size() == maxUnsortedEntries_) {
                    flush();
                }

                unsorted_.push_back(k);
            }
        }
    }
    
    bool empty() const {
        return coll_.empty() && unsorted_.empty();
    }
    
    void clear() {
        coll_.clear();
        unsorted_.clear();
    }
    
    void reserve(size_type n) {
        coll_.reserve(n);
    }
    
    size_type size() const {
        return coll_.size() + unsorted_.size();
    }
    
    size_type count(const value_type& k) const {
        size_type found = 0;
        
        auto iter = lower_bound_equals(coll_, k);
        if (iter != coll_.end()) {
            found = 1;
        } else {
            iter = search_unsorted(unsorted_, k);
            if (iter != unsorted_.end()) {
                found = 1;
            }
        }
        
         return found;
    }
    
    bool find(const value_type& k, value_type& v) {
        auto found = false;
        
        auto iter = lower_bound_equals(coll_, k);
        if (iter != coll_.end()) {
            v = *iter;
            found = true;
        } else {
            iter = search_unsorted(unsorted_, k);
            if (iter != unsorted_.end()) {
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
    void sort(base_collection& coll) const {
        std::sort(coll.begin(), coll.end(), Less{});
    }
    
    iterator lower_bound(base_collection& coll, const value_type& k) const {
        return std::lower_bound(coll.begin(), coll.end(), k, Less{});
    }
    
    iterator lower_bound_equals(base_collection& coll, const value_type& k) const {
        auto iter = lower_bound(coll, k);
        return iter != coll.end() && Equal{}(*iter, k) ? iter : coll.end();
    }
    
    iterator upper_bound(base_collection& coll, const value_type& k) const {
        return std::upper_bound(coll.begin(), coll.end(), k, Less{});
    }
    
    iterator upper_bound_equals(base_collection& coll, const value_type& k) const {
        auto iter = upper_bound(coll, k);
        return iter != coll.end() && Equal{}(*iter, k) ? iter : coll.end();
    }
    
    iterator search_unsorted(base_collection& coll, const value_type& k) const {
        return std::search_n(coll.begin(), coll.end(), 1, k, Equal{});
    }
    
    void flush() const {
        if (unsorted_.size() > 0) {        
            sort(unsorted_);
            merge(unsorted_, coll_);
            unsorted_.clear();
        }
    }

    // TODO: optimize the range insert
    // TODO: review iterator invalidation
    void merge(base_collection& source, base_collection& target) const {
        auto sourceStart = source.cbegin(), sourceIter = sourceStart;
        auto targetStart = upper_bound(target, *sourceIter++);            
        for (; sourceIter != source.cend(); ++sourceIter) {
            auto targetIter = upper_bound(target, *sourceIter);
            if (targetStart != targetIter) {
                target.insert(targetStart, sourceStart, sourceIter);
                sourceStart = sourceIter;
                targetStart = targetIter;
            }
        }

        if (sourceStart != sourceIter) {
            target.insert(targetStart, sourceStart, sourceIter);
        }
    }
    
    const unsigned maxUnsortedEntries_;
    
    mutable base_collection coll_;
    mutable base_collection unsorted_;
};
    
}

#endif