[![Build Status](https://travis-ci.org/RipcordSoftware/lazyflatset.svg)](https://travis-ci.org/RipcordSoftware/lazyflatset)
[![Coverage Status](https://coveralls.io/repos/RipcordSoftware/lazyflatset/badge.svg)](https://coveralls.io/r/RipcordSoftware/lazyflatset)
[![License](http://img.shields.io/:license-mit-blue.svg)](http://doge.mit-license.org)

# lazyflatset
Like Boost's flat_set, but lazy. 

When we say lazy we mean fast. `lazyflatset` started off attempting to solve tragic `flat_set` performance with descending and random inserts. We've attempted to solve that by adding a small unsorted collection and sorted nursery collection while still maintaining the spirit of both std::set and set::vector interfaces.

See the [Boost docs](http://www.boost.org/doc/libs/1_58_0/doc/html/container/non_standard_containers.html#container.non_standard_containers.flat_xxx) for more info on why flat sets are interesting.

## Usage
Include the header and you are ready to go:

```C++
#include "lazyflatset.hpp"

int main() {
    rs::LazyFlatSet<unsigned> set;
    set.insert(42);
    return 0;
}
```

 You will need a decent C++ 11 compiler.

## Performance

The following chart shows lazyflatset vs std::set and set::unordered_set with 5m rows inserted. The rows are initially:
* ordered ascending
* ordered descending
* partially shuffled - the ordered data is split into equal partitions and shuffled independently, eg. {3142}{6587}
* fully shuffled

<div>
    <a href="https://plot.ly/~craigminihan/71/" target="_blank" title="std::set, std::unordered_set vs rs::lazyflatset(128, 32768) - 5m rows - Debian 8.1 - i7-4820k" style="display: block; text-align: center;"><img src="https://plot.ly/~craigminihan/71.png" alt="std::set, std::unordered_set vs rs::lazyflatset(128, 32768) - 5m rows - Debian 8.1 - i7-4820k" style="max-width: 100%;width: 1944px;"  width="1944" onerror="this.onerror=null;this.src='https://plot.ly/404.png';" /></a>
    <script data-plotly="craigminihan:71" src="https://plot.ly/embed.js" async></script>
</div>

set::set is implemented as a binary tree (ordered sparse nodes), std::unordered_set as a hash table (unordered vector) and lazyflatset (unordered/ordered/ordered vector).

## Compile and Build
We develop with Netbeans C++ IDE and GCC 4.9 on Debian. We expect it to work with any C++11 compiler including GCC 4.8 and clang 3.5.
