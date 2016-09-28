make all CXX=g++-4.9 && make test CXX=g++-4.9 && ./coverage.sh gcov-4.9

if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
    make CC=${_CC} CXX=${_CXX} all && make CC=${_CC} CXX=${_CXX} test && ./coverage.sh ${_COV}
elif [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
    make CC=${_CC} CXX=${_CXX} all && make CC=${_CC} CXX=${_CXX} test
fi
