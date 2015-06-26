/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Ripcord Software Ltd
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
**/

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
    using const_iterator = typename base_collection::const_iterator;
    using value_type = Key;
    using reference = typename std::conditional<std::is_fundamental<Key>::value || std::is_pointer<Key>::value, value_type, value_type&>::type;
    using const_reference = typename std::conditional<std::is_fundamental<Key>::value || std::is_pointer<Key>::value, value_type, const value_type&>::type;
    
    LazyFlatSet(unsigned maxUnsortedEntries = 16, unsigned maxNurseryEntries = 1024) : 
            maxUnsortedEntries_(maxUnsortedEntries), maxNurseryEntries_(maxNurseryEntries) {
        unsorted_.reserve(maxUnsortedEntries);
    }
    
    void insert(const value_type& k) {
        auto iter = lower_bound_equals(coll_, k);
        if (iter != coll_.end()) {
            *iter = k;
        } else {
            iter = lower_bound_equals(nursery_, k);
            if (iter != nursery_.end()) {
                *iter = k;
            } else {            
                iter = search_unsorted(unsorted_, k);
                if (iter != unsorted_.end()) {
                    *iter = k;
                } else {
                    if (unsorted_.size() == maxUnsortedEntries_) {
                        flushUnsorted();
                    }

                    unsorted_.push_back(k);
                }
            }
        }
    }
    
    bool empty() const {
        return coll_.empty() && nursery_.empty() && unsorted_.empty();
    }
    
    void clear() {
        coll_.clear();
        nursery_.clear();
        unsorted_.clear();
    }
    
    void reserve(size_type n) {
        coll_.reserve(n);
    }
    
    size_type size() const {
        return coll_.size() + nursery_.size() + unsorted_.size();
    }

    void shrink_to_fit() {
        flush();
        nursery_.shrink_to_fit();
        coll_.shrink_to_fit();
    }
    
    size_type count(const value_type& k) const {
        size_type found = 0;
        
        auto iter = lower_bound_equals(coll_, k);
        if (iter != coll_.end()) {
            found = 1;
        } else {
            iter = lower_bound_equals(nursery_, k);
            if (iter != nursery_.end()) {
                found = 1;
            } else {
                iter = search_unsorted(unsorted_, k);
                if (iter != unsorted_.end()) {
                    found = 1;
                }
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
            iter = lower_bound_equals(nursery_, k);
            if (iter != nursery_.end()) {
                v = *iter;
                found = true;
            } else {
                iter = search_unsorted(unsorted_, k);
                if (iter != unsorted_.end()) {
                    v = *iter;
                    found = true;
                }
            }
        }
        
         return found;
    }
    
    const_reference operator[](size_type n) const {
        flush();
        return coll_[n];
    }
    
    const_iterator cbegin() const {
        flush();
        return coll_.cbegin();
    }
    
    const_iterator cend() const {
        flush();
        return coll_.cend();
    }    
    
    const value_type* data() const {
        flush();
        return coll_.data();
    }
    
    size_type erase(const value_type& k) {
        size_type count = 0;
        
        auto iter = lower_bound_equals(coll_, k);
        if (iter != coll_.end()) {
            coll_.erase(iter);
            count = 1;
        } else {
            iter = lower_bound_equals(nursery_, k);
            if (iter != nursery_.end()) {
                nursery_.erase(iter);
                count = 1;
            } else {
                iter = search_unsorted(unsorted_, k);
                if (iter != unsorted_.end()) {
                    unsorted_.erase(iter);
                    count = 1;
                }
            }
        }
        
        return count;
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
        flushUnsorted();
        flushNursery();
    }

    void flushUnsorted() const {
        const auto unsortedSize = unsorted_.size();
        if (unsortedSize > 0) {
            if ((nursery_.size() + unsortedSize) >= maxNurseryEntries_) {
                flushNursery();
            }

            sort(unsorted_);
            merge(unsorted_, nursery_);
            unsorted_.clear();
        }
    }
    
    void flushNursery() const {
        if (nursery_.size() > 0) {        
            merge(nursery_, coll_);
            nursery_.clear();
        }
    }

    void merge(base_collection& source, base_collection& target) const {
        if (source.size() > 0) {
            Less less;
            if (target.size() == 0 || less(target.back(), source.front())) {
                target.insert(target.end(), source.cbegin(), source.cend());
            } else if (less(source.back(), target.front())) {
                target.insert(target.begin(), source.cbegin(), source.cend());
            } else {
                target.insert(target.begin(), source.cbegin(), source.cend());
                std::inplace_merge(target.begin(), target.begin() + source.size(), target.end());
            }
        }
    }
    
    const unsigned maxUnsortedEntries_;
    const unsigned maxNurseryEntries_;
    
    mutable base_collection coll_;
    mutable base_collection nursery_;
    mutable base_collection unsorted_;
};
    
}

#endif
