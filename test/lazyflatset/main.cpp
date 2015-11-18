#include <iostream>
#include <chrono>
#include <functional>

#include <vector>
#include <set>
#include <unordered_set>
#include <list>
#include <queue>

#include "../../lazyflatset.hpp"

using DataType = unsigned;
using SourceIterator = std::vector<DataType>::iterator;

using TestFunction = std::function<void(SourceIterator, SourceIterator)>;

void vectorHeadInsert(SourceIterator begin, SourceIterator end) {
    std::vector<DataType> data;
    data.insert(data.begin(), begin, end);
}

void vectorTailInsert(SourceIterator begin, SourceIterator end) {
    std::vector<DataType> data;
    data.insert(data.end(), begin, end);
}

void vectorHeadPush(SourceIterator begin, SourceIterator end) {
    std::vector<DataType> data;
    
    for (auto iter = begin; iter != end; ++iter) {
        data.insert(data.begin(), *iter);
    }
}

void vectorTailPush(SourceIterator begin, SourceIterator end) {
    std::vector<DataType> data;
    
    for (auto iter = begin; iter != end; ++iter) {
        data.push_back(*iter);
    }
}

void setInsert(SourceIterator begin, SourceIterator end) {
    std::set<DataType> data;
    data.insert(begin, end);
}

void unorderedSetInsert(SourceIterator begin, SourceIterator end) {
    std::unordered_set<DataType> data;
    data.insert(begin, end);
}

void priorityQueuePush(SourceIterator begin, SourceIterator end) {
    std::priority_queue <DataType> data;
    
    for (auto iter = begin; iter != end; ++iter) {
        data.push(*iter);
    }
}

void listTailInsert(SourceIterator begin, SourceIterator end) {
    std::list<DataType> data;
    data.insert(data.begin(), begin, end);
}

void lazyFlatSetInsert(SourceIterator begin, SourceIterator end) {
    rs::LazyFlatSet<DataType> data(128, 32 * 1024);
    
    for (auto iter = begin; iter != end; ++iter) {
        data.insert(*iter);
    }
}

void lazyFlatSetInsertNewItem(SourceIterator begin, SourceIterator end) {
    rs::LazyFlatSet<DataType> data(128, 32 * 1024);
    
    for (auto iter = begin; iter != end; ++iter) {
        data.insert(*iter, rs::LazyFlatSet<DataType>::insert_hint::new_item);
    }
}

void test(TestFunction func, SourceIterator begin, SourceIterator end, bool eol = false) {
    auto start = std::chrono::steady_clock::now();
    func(begin, end);
    auto duration = std::chrono::steady_clock::now() - start;
    auto durationMS = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    
    std::cout << durationMS.count();
    
    if (eol) {
        std::cout << std::endl;
    } else {
        std::cout << ", ";
    }
}

int main() {
    std::vector<DataType> data;
    const unsigned max = 5 * 1000 * 1000;
    for (unsigned i = 0; i < max; ++i) {
        data.push_back(i);
    }
    
    std::cout << R"("", "listTailInsert", "vectorTailInsert", "vectorTailPush", "vectorHeadInsert", "setInsert", "unorderedSetInsert", "priorityQueuePush", "lazyFlatSetInsert", "lazyFlatSetInsert[new_item]")" << std::endl;
    
    std::cout << R"("Ascending", )";
    
    test(listTailInsert, data.begin(), data.end());
    test(vectorTailInsert, data.begin(), data.end());
    test(vectorTailPush, data.begin(), data.end());
    test(vectorHeadInsert, data.begin(), data.end());
    //test(vectorHeadPush, data.begin(), data.end());
    test(setInsert, data.begin(), data.end());
    test(unorderedSetInsert, data.begin(), data.end());
    test(priorityQueuePush, data.begin(), data.end());
    test(lazyFlatSetInsert, data.begin(), data.end());
    test(lazyFlatSetInsertNewItem, data.begin(), data.end(), true);
    
    std::cout << R"("Descending", )";
    
    std::reverse(data.begin(), data.end());
    
    test(listTailInsert, data.begin(), data.end());
    test(vectorTailInsert, data.begin(), data.end());
    test(vectorTailPush, data.begin(), data.end());
    test(vectorHeadInsert, data.begin(), data.end());
    //test(vectorHeadPush, data.begin(), data.end());
    test(setInsert, data.begin(), data.end());
    test(unorderedSetInsert, data.begin(), data.end());
    test(priorityQueuePush, data.begin(), data.end());
    test(lazyFlatSetInsert, data.begin(), data.end());
    test(lazyFlatSetInsertNewItem, data.begin(), data.end(), true);
    
    std::cout << R"("Partial shuffle", )";
    
    const unsigned blocks = 10000;
    const unsigned blockSize = max / blocks;
    auto iter = data.begin();
    for (unsigned i = 0; i < blocks; ++i) {
        auto iterEnd = iter + blockSize;
        std::random_shuffle(iter, iterEnd < data.end() ? iterEnd : data.end());
        iter += blockSize;
    }        
    
    test(listTailInsert, data.begin(), data.end());
    test(vectorTailInsert, data.begin(), data.end());
    test(vectorTailPush, data.begin(), data.end());
    test(vectorHeadInsert, data.begin(), data.end());
    //test(vectorHeadPush, data.begin(), data.end());
    test(setInsert, data.begin(), data.end());
    test(unorderedSetInsert, data.begin(), data.end());
    test(priorityQueuePush, data.begin(), data.end());
    test(lazyFlatSetInsert, data.begin(), data.end());
    test(lazyFlatSetInsertNewItem, data.begin(), data.end(), true);
    
    std::cout << R"("Full shuffle", )";
    
    std::random_shuffle(data.begin(), data.end());

    test(listTailInsert, data.begin(), data.end());
    test(vectorTailInsert, data.begin(), data.end());
    test(vectorTailPush, data.begin(), data.end());
    test(vectorHeadInsert, data.begin(), data.end());
    //test(vectorHeadPush, data.begin(), data.end());
    test(setInsert, data.begin(), data.end());
    test(unorderedSetInsert, data.begin(), data.end());
    test(priorityQueuePush, data.begin(), data.end());
    test(lazyFlatSetInsert, data.begin(), data.end());
    test(lazyFlatSetInsertNewItem, data.begin(), data.end(), true);
    
    return 0;
}