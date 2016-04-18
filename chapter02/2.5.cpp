//
// Created by Andrew_liu on 16/4/18.
//
#include <iostream>
#include <thread>
using namespace std;


// 每个线程都有一个属性为id, 线程对象可以通过get_id()函数获取id
thread::id master_thread;  // 默认值表示没有线程

void SomeCorePartOfAlgorithm() {
    cout << this_thread::get_id() << endl;
    if (this_thread::get_id() == master_thread) {
        cout << "This is in the master thread..." << endl;
    } else {
        cout << "master thread id: " << master_thread << endl;
        cout << "This is other thread..." << endl;
    }
}

int main() {
    SomeCorePartOfAlgorithm();
    cout << this_thread::get_id() << endl;
}