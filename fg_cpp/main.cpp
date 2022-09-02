#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

int f(int num) {
    this_thread::sleep_for(chrono::seconds(5));
    return num % 2 == 0;
}

int g(int num) {
    this_thread::sleep_for(chrono::seconds(5));
    return num % 3 == 0;
}

int main() {
    int a, b;
    cin >> a >> b;

    int f_result, g_result;

    auto f_l = [&f_result, &a]() {
        f_result = f(a);
    };
    auto g_l = [&g_result, &b]() {
        g_result = g(b);
    };

    thread thread_1( f_l);
    thread thread_2(g_l);

    thread_1.join();
    thread_2.join();

    bool answer = f_result && g_result;

    cout << answer << endl;

    return 0;
}
