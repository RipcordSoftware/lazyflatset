[![Build Status](https://travis-ci.org/RipcordSoftware/lazyflatset.svg)](https://travis-ci.org/RipcordSoftware/lazyflatset)
[![Coverage Status](https://coveralls.io/repos/RipcordSoftware/lazyflatset/badge.svg)](https://coveralls.io/r/RipcordSoftware/lazyflatset)
[![License](http://img.shields.io/:license-mit-blue.svg)](http://doge.mit-license.org)

# lazyflatset
Like Boost's flat_set, but lazy. 

When we say lazy we mean fast. `lazyflatset` started off attempting to solve tragic `flat_set` performance with descending and random inserts. We've attempted to solve that by adding a small unsorted collection and sorted nursery collection while still maintaining the spirit of both std::set and set::vector interfaces.

## Performance

<div>
    <a href="https://plot.ly/~craigminihan/71/" target="_blank" title="std::set, std::unordered_set vs rs::lazyflatset(128, 32768) - 5m rows - Debian 8.1 - i7-4820k" style="display: block; text-align: center;"><img src="https://plot.ly/~craigminihan/71.png" alt="std::set, std::unordered_set vs rs::lazyflatset(128, 32768) - 5m rows - Debian 8.1 - i7-4820k" style="max-width: 100%;width: 1944px;"  width="1944" onerror="this.onerror=null;this.src='https://plot.ly/404.png';" /></a>
    <script data-plotly="craigminihan:71" src="https://plot.ly/embed.js" async></script>
</div>

We compile with GCC 4.9 on Debian. It'll probably work with any C++11 compiler.

See the [Boost docs](http://www.boost.org/doc/libs/1_58_0/doc/html/container/non_standard_containers.html#container.non_standard_containers.flat_xxx) for more info on why flat sets are interesting.
