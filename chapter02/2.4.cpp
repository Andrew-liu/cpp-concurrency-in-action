//
// Created by Andrew_liu on 16/4/18.
//
#include <iostream>
#include <thread>
#include <numeric>
#include <vector>
#include <time.h>

using namespace std;

template <typename Iterator, typename T>
struct AccumulateBlock {
    void operator()(Iterator first, Iterator last, T& result) {
        result = std::accumulate(first, last, result);
    }
};

template <typename Iterator, typename T>
T ParallelAccumulate(Iterator first, Iterator last, T init) {
    unsigned long const length = std::distance(first, last);
    if (!length) {
        return init;
    }

    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length + min_per_thread - 1) / min_per_thread;  // 启动线程的最大数量
    unsigned long const hardware_threads = thread::hardware_concurrency();  // 硬件支持线程数
    unsigned long const num_threads = min(hardware_threads != 0 ? hardware_threads : 2, max_threads);  // 启动线程的数量
    unsigned long const block_size = length / num_threads;

    vector<T> results(num_threads);
    vector<thread> threads(num_threads - 1);  // 减一是因为已经有一个主线程

    Iterator block_start = first;
    for (unsigned long i = 0; i < (num_threads - 1); ++i) {  // 启动线程
        Iterator block_end = block_start;
        advance(block_end, block_size);  // 每个线程分别计算一块, 并将结果存储在对应的位置上
        threads[i] = thread(
                AccumulateBlock<Iterator, T>(),
                block_start,
                block_end,
                ref(results[i])
        );
        block_start = block_end;
    }
    // 最终的块处理
    AccumulateBlock<Iterator, T>()(block_start, last, results[num_threads - 1]);
    // 对所有线程join
    for_each(threads.begin(), threads.end(), mem_fn(&thread::join));
    // 累加每个线程产生的结果
    return accumulate(results.begin(), results.end(), init);
};


int main() {
    time_t t_start, t_end;
    std::vector<int> v(500000000, 1);

    t_start = time(NULL);
    auto sum = ParallelAccumulate(v.begin(), v.end(), 0);
    cout << "sum = " << sum << endl;
    t_end = time(NULL);
    cout << "parallel spend time: " << difftime(t_end, t_start) << endl;  // 1s

    t_start = time(NULL);
    sum = accumulate(v.begin(), v.end(), 0);
    cout << "sum = " << sum << endl;
    t_end = time(NULL);
    cout << "normal spend time: " << difftime(t_end, t_start) << endl;  // 2s
    return 0;
}