#include <mutex>
#include <thread>

using namespace std;

void f_mtx() {
    int value = 0;
    mutex mtx;

    auto increment = [&]() {
        int i = 1000000;
        while (i--) {
            mtx.lock();
            ++value;
            mtx.unlock();
        }
    };

    thread t0(increment);
    thread t1(increment);

    t0.join();
    t1.join();
}

void f_free() {
    int value = 0;

    auto increment = [&]() {
        int i = 1000000;
        while (i--) ++value;
    };

    thread t0(increment);
    thread t1(increment);

    t0.join();
    t1.join();

}

int main() {
    clock_t now;

    now = clock();
     f_free();
    printf("free: %.4fs\n", double(clock() - now) / CLOCKS_PER_SEC);

    now = clock();
    f_mtx();
    printf("mutex: %.4fs\n", double(clock() - now) / CLOCKS_PER_SEC);

    return 0;
}

