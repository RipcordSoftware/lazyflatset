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
#include <functional>

namespace rs {
    
template <class Value, class Less>
struct LazyFlatSetQuickSort;

template <class Value, class Less = std::less<Value>, class Equal = std::equal_to<Value>, class Sort = LazyFlatSetQuickSort<Value, Less>, class Alloc = std::allocator<Value>>
class LazyFlatSet {
public:
    using base_collection = typename std::vector<Value, Alloc>;
    using size_type = typename base_collection::size_type;
    using iterator = typename base_collection::iterator;
    using const_iterator = typename base_collection::const_iterator;
    using value_type = Value;
    using reference = typename std::conditional<std::is_fundamental<Value>::value || std::is_pointer<Value>::value, value_type, value_type&>::type;
    using const_reference = typename std::conditional<std::is_fundamental<Value>::value || std::is_pointer<Value>::value, value_type, const value_type&>::type;
    using less_type = Less;
    using equal_type = Equal;
    using compare_type = typename std::function<int(const_reference)>;        
    
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
    
    template <typename... Args>
    void emplace(Args&&... args) {
        if (unsorted_.size() == maxUnsortedEntries_) {
            flushUnsorted();
        }

        unsorted_.emplace_back(std::forward<Args>(args)...);
        
        auto iter = lower_bound_equals(coll_, unsorted_.back());
        if (iter != coll_.end()) {
            *iter = std::move(unsorted_.back());
            unsorted_.pop_back();
        } else {
            iter = lower_bound_equals(nursery_, unsorted_.back());
            if (iter != nursery_.end()) {
                *iter = std::move(unsorted_.back());
                unsorted_.pop_back();
            } else if (unsorted_.size() > 1) {
                auto newItemIter = unsorted_.end() - 1;
                
                iter = search_unsorted(unsorted_, unsorted_.back());
                if (iter != newItemIter) {
                    *iter = std::move(unsorted_.back());
                    unsorted_.pop_back();
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
    
    size_type count_fn(compare_type compare) const {
        size_type found = 0;
        
        auto index = search(coll_, compare);
        if (index != search_end) {
            found = 1;
        } else {
            index = search(nursery_, compare);
            if (index != search_end) {
                found = 1;
            } else {
                index = search_unsorted(unsorted_, compare);
                if (index != search_end) {
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
    
    value_type* find_fn(compare_type compare) {
        value_type* value = nullptr;
        
        auto index = search(coll_, compare);
        if (index != search_end) {
            value = &coll_[index];            
        } else {
            index = search(nursery_, compare);
            if (index != search_end) {
                value = &nursery_[index];                
            } else {
                index = search_unsorted(unsorted_, compare);
                if (index != search_end) {
                    value = &unsorted_[index];
                }
            }
        }
        
         return value;
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
    const size_type search_end = -1;
    
    void sort(base_collection& coll) const {
        Sort{}(coll.begin(), coll.end());
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
    
    size_type search(base_collection& coll, compare_type compare) const {
        const auto size = coll.size();
        
        if (size > 0) {
            size_type min = 0;
            size_type max = size - 1;
            const auto data = coll.data();

            while (max >= min) {
                auto mid = ((max - min) / 2) + min;

                const auto& item = data[mid];
                auto diff = compare(item);
                if (diff == 0) {
                    return mid;
                } else if (diff < 0) {
                    max = mid - 1;
                } else {
                    min = mid + 1;
                }
            }
        }
        
        return search_end;
    }
    
    size_type search_unsorted(base_collection& coll, compare_type compare) const {
        const auto data = coll.data();
        
        for (size_type i = 0, size = coll.size(); i < size; ++i) {
            if (compare(data[i]) == 0) {
                return i;
            }
        }
        
        return search_end;
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
                std::inplace_merge(target.begin(), target.begin() + source.size(), target.end(), less);
            }
        }
    }
    
    const unsigned maxUnsortedEntries_;
    const unsigned maxNurseryEntries_;
    
    mutable base_collection coll_;
    mutable base_collection nursery_;
    mutable base_collection unsorted_;
};

template <class Value, class Less>
struct LazyFlatSetQuickSort {
    void operator()(typename LazyFlatSet<Value>::iterator first, typename LazyFlatSet<Value>::iterator last) {
        std::sort(first, last, Less{});
    }
};

}

#endif
