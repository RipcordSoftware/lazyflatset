if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
    make CC=${_CC} CXX=${_CXX} all && make CC=${_CC} CXX=${_CXX} test && ./coverage.sh ${_COV}
elif [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
    make CC=${_CC} CXX=${_CXX} all && make CC=${_CC} CXX=${_CXX} test
fi
