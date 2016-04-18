//
// Created by Andrew_liu on 16/4/18.
//
#include <iostream>
#include <thread>  // C++11线程库

using namespace std;

void Func(int i, string const& s) {
    cout << i << endl;
    cout << s << endl;
}

void UpdateDataForWidget(int id, string& data) { // 参数为引用
    data += "hello world";
    cout << id << endl;
    cout << data << endl;
}

void Oops(int some_param) {
    char buffer[1024];
    sprintf(buffer, "%i", some_param);
    thread thread_one(Func, 3, string(buffer));  // 先转换为string
    thread_one.join();
}

void OopsAgain(int id) {
    string data = "Welcome concurrency!";
    // thread并不知道参数是引用类型, 所以如果不加std:ref会直接error
    thread thread_two(UpdateDataForWidget, id, std::ref(data));
    thread_two.join();
    cout << "data after thread: " << data << endl;
}

int main() {
//    Oops(1024);
    OopsAgain(1024);
}