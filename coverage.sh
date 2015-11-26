#!/bin/bash

GCOV_TOOL=
if [ "$1" != "" ]; then
    GCOV_TOOL="--gcov-tool $1"
fi

lcov --directory test/lazyflatset/build/Debug/GNU-Linux-x86/ --capture --output-file coverage.info ${GCOV_TOOL}
lcov --remove coverage.info 'test/*' '/usr/*' 'externals/*' --output-file coverage.info ${GCOV_TOOL}
lcov --list coverage.info ${GCOV_TOOL}
if [ "$CI" = "true" ] && [ "$TRAVIS" = "true" ]; then
    coveralls-lcov coverage.info
else
    rm -rf coverage
    mkdir -p coverage
    cd coverage
    genhtml ../coverage.info
    cd ..
fi
