//
//  main.cpp
//  4.2
//
//  Created by Simon Fedotov on 21.04.16.
//  Copyright © 2016 Simon23Rus. All rights reserved.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

struct Slow {
    int first;
    int second;
    int stopper[999999];
};

struct Fast {
    int first;
    int stopper[999999];
    int second;
};

void incrementor(int &value, int bound) {
    for(int i = 0; i < bound; ++i) {
        ++value;
    }
}

double timeMeasure(int &first, int &second, int bound) {
    auto start = std::chrono::steady_clock::now();
    std::thread firstThread(incrementor, std::ref(first), bound);
    std::thread secondThread(incrementor, std::ref(second), bound);
    firstThread.join();
    secondThread.join();
    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() * 0.000001;
}

int main() {
    Slow slow;
    Fast fast;
    auto withPing = timeMeasure(slow.first, slow.second, 1e9);
    auto withoutPong = timeMeasure(fast.first, fast.second, 1e9);
    std::cout << "Time with Cache Ping - Pong: " << withPing << "seconds\n";
    std::cout << "Time without Cache Ping - Pong: " << withoutPong << "seconds\n";
    return 0;
}