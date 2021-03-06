#include <time.h>

#include <ticktack/benchmark.hpp>

using namespace ticktack;

//!=============================================================================
//! Common usage.
BENCHMARK(DatetimeGeneration, strftime) {
    std::time_t time = std::time(0);
    std::tm tm;
    localtime_r(&time, &tm);
    char buffer[64];
    strftime(buffer, 64, "%Y-%m-%d %H:%M:%S", &tm);
    compiler::do_not_optimize(buffer);
}

//!=============================================================================
//! Baseline support.
BENCHMARK_BASELINE(VectorRelative, push_back) {
    std::vector<int> v;
    for (int i = 0; i < 10000; ++i) {
        v.push_back(i);
    }
}

//! This benchmark will be compared with the upper one.
BENCHMARK_RELATIVE(VectorRelative, push_back_reserved) {
    std::vector<int> v;
    v.reserve(10000);
    for (int i = 0; i < 10000; ++i) {
        v.push_back(i);
    }
}

//!=============================================================================
//! Sometimes you want to perform iterations yourself. In that case the library
//! provides you iteration count parameter.
BENCHMARK(VectorAccepted, insert_front, n) {
    std::vector<int> v;
    for (iteration_type::value_type i = 0; i < n.v; ++i) {
        v.insert(v.begin(), i);
    }
}

//!=============================================================================
//! Sometimes you want to perform iterations yourself and you know iteration
//! count. In that case you should return iteration count from function.
BENCHMARK_RETURN(VectorReturned, insert_front) {
    std::vector<int> v;
    iteration_type iters(10000);
    for (iteration_type::value_type i = 0; i < iters.v; ++i) {
        v.insert(v.begin(), i);
    }
    return iters;
}

//!=============================================================================
//! Benchmark with bound parameters.
void insert_front(std::size_t n) {
    std::vector<int> v;
    v.reserve(n);
    for (int i = 0; i < 10000; ++i) {
        v.insert(v.begin(), i);
    }
}
BENCHMARK_BOUND(VectorParam, insert_front, 100);
BENCHMARK_BOUND(VectorParam, insert_front, 1000);
BENCHMARK_BOUND(VectorParam, insert_front, 10000);

//! Benchmark with multiple bound parameters.
void insert_front_multi(std::size_t n, double pi) {
    std::vector<int> v;
    v.reserve(n);
    for (int i = 0; i < 10000; ++i) {
        v.insert(v.begin(), i);
    }
}
BENCHMARK_BOUND(VectorParam, insert_front_multi, 100, 3.1415);
BENCHMARK_BOUND(VectorParam, insert_front_multi, 1000, 2 * 3.1415);
BENCHMARK_BOUND(VectorParam, insert_front_multi, 10000, 3 * 3.1415);

//!=============================================================================
//! Benchmark with bound parameters and iteration count provided.
void insert_front_provided(iteration_type iters, std::size_t n) {
    std::vector<int> v;
    v.reserve(n);
    for (int i = 0; i < iters.v; ++i) {
        v.insert(v.begin(), i);
    }
}
BENCHMARK_BOUND(VectorParam, insert_front_provided, 100);
BENCHMARK_BOUND(VectorParam, insert_front_provided, 1000);
BENCHMARK_BOUND(VectorParam, insert_front_provided, 10000);

//!=============================================================================
//! Benchmark with bound parameters and iteration count returned.
iteration_type insert_front_returned(std::size_t n) {
    iteration_type iters(10000);
    std::vector<int> v;
    v.reserve(n);
    for (int i = 0; i < iters.v; ++i) {
        v.insert(v.begin(), i);
    }
    return iters;
}
BENCHMARK_BOUND(VectorParam, insert_front_returned, 100);
BENCHMARK_BOUND(VectorParam, insert_front_returned, 1000);
BENCHMARK_BOUND(VectorParam, insert_front_returned, 10000);
