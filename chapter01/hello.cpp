#include <iostream>
#include <thread>  // C++11线程库

using namespace std;

void hello() {
    cout << "Hello Concurrent World" << endl;
}


int main() {

    // 最简单的多线程例子
    cout << "Hello, World!" << endl;
    thread t(hello);  // 通过函数构造一个线程对象
    t.join();
    return 0;  // 不等待线程的结束直接退出
}