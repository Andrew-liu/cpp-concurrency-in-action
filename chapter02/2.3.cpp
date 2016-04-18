//
// Created by Andrew_liu on 16/4/18.
//
#include <iostream>
#include <thread>
#include <vector>
using namespace std;

void SomeFunction() {
    cout << "Some function.." << endl;
}

void SomeOtherFunction() {
    cout << "Some other function..." << endl;
}

class ScopedThread {
public:
    explicit ScopedThread(std::thread t): t_(std::move(t)) {
        // 构造函数中判断是否可以join
        if (!t_.joinable()) {
            throw std::logic_error("No thread");
        }
    }

    ~ScopedThread() {
        t_.join();
        cout << "Scoped Thread join..." << endl;
    }
    ScopedThread(ScopedThread const&) = delete;
    ScopedThread& operator=(ScopedThread const&) = delete;

private:
    std::thread t_;
};


struct Func {
    int& i_;
    Func(int& i): i_(i) {}
    void operator()() {
        for (unsigned j = 0; j < 10000; ++j) {
            do_something(i_);
        }
    }
    void do_something(int i) {
//        cout << i << endl;
    }
};

void DoWork(unsigned id) {
    cout << id << endl;
}

// 创建多个线程
void MultiThread() {
    vector<thread> threads;
    for (unsigned i = 0; i < 20; i++) {
        threads.push_back(thread(DoWork,i ));
    }
    for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));  //对每个线程join
}


int main() {
    /*
    // thread支持移动操作

    thread thread_one(SomeFunction);
    thread thread_two = std::move(thread_one);  // 将thread_one的执行线程的所有权转移给thread_two
    thread_one = std::thread(SomeOtherFunction);  // 创建临时对象, movable操作隐式调用
    thread thread_three;  // 创建thread_three,
    thread_three = std::move(thread_two);  // thread_two的执行线程所有转移给thread_three

    // thread_three的执行线程所有权转义给thread_one, 此时thread_one先terminate()终止执行SomeOtherFunction,
    // 终止操作调用thread析构函数, 最后将SomeFunction线程的所有权准给thread_one
    thread_one = std::move(thread_three);
     */

    /*
    int local_para;
    Func func(local_para);
    thread thread_four(func);
    ScopedThread thread_five(thread_four);  // ? 这里有个错误, 在构造函数中会调用 thread(const thread&);这个私有构造器
     */

    MultiThread();
}
