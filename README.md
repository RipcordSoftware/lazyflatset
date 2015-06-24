[![Build Status](https://travis-ci.org/RipcordSoftware/lazyflatset.svg)](https://travis-ci.org/RipcordSoftware/lazyflatset)

# lazyflatset
Like Boost's flat_set, but lazy. 

When we say lazy we mean fast. `lazyflatset` started off attempting to solve tragic `flat_set` performance with descending and random inserts. We've attempted to solve that by adding a small unsorted collection and sorted nursery collection while still maintaining the spirit of both std::set and set::vector interfaces.

When we get round to it performance numbers will appear here. Results look pretty good with limited testing but your use case may not align with ours so your mileage may vary considerably.

We compile with GCC 4.9 on Debian. It'll probably work with any C++11 compiler.

See the [Boost docs](http://www.boost.org/doc/libs/1_58_0/doc/html/container/non_standard_containers.html#container.non_standard_containers.flat_xxx) for more info on why flat sets are interesting.
