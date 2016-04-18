//
// Created by Andrew_liu on 16/4/18.
//
#include <iostream>
#include <thread>  // C++11线程库

using namespace std;

class BackgroundTask {
public:
    // 操作符重载, 使类变化callable
    void operator()() const {  // const成员函数中只能调用const函数
        do_something();
        do_something_else();
    }
private:
    void do_something() const {
        cout << "Do something..." << endl;
    }

    void do_something_else() const {
        cout << "Do something else..." << endl;
    }
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


class ThreadGuard {
public:
    explicit ThreadGuard(thread& t): t_(t) {}
    ~ThreadGuard() {
        if (t_.joinable()) {
            t_.join();
        }
        cout << "the thread has joined..." << endl;
    }
    ThreadGuard(const ThreadGuard& thread) = delete;
    ThreadGuard& operator=(const ThreadGuard& rhs) = delete;

private:
    thread& t_;
};

void do_something_throw_exception() {
    try {
        throw runtime_error{"There will throw a exception"};
    } catch (exception e) {
        cout << e.what() << endl;
    }

}


int main() {
    /*
    // 使用类作为线程的运行逻辑
    BackgroundTask background_back;
    thread three_one(background_back);
    three_one.join();  // 防止函数结束, 而线程依旧访问局部变量. join确保局部变量在线程完成后才销毁 并清理了线程相关的存储
    // 只能对一个线程使用一个join

    // 使用结构体作为线程的运行逻辑
    int local_para = 0;
    Func my_func(local_para);
    thread thread_two(my_func);
    thread_two.detach();
    */

    // 使用RAII来回收线程资源
    /*
        输出结果如下
        std::exception
        the thread has joined...
     */
    int some_local_para = 0;
    Func my_func(some_local_para);
    thread thread_three(my_func);
    ThreadGuard thread_guard(thread_three);
    do_something_throw_exception();  // 此处抛出异常, thread_throw依然能被安全销毁
    return 0;  // 不等待线程的结束直接退出
}