#include <iostream>
#include <thread>
#include <mutex>

const int MAX_NUMBER = 100;  // Print numbers up to 100

std::mutex mtx;
int currentNumber = 1;

void printNumbers(int threadId, int totalThreads) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);

        if (currentNumber > MAX_NUMBER) {
            break; // Stop when all numbers are printed
        }

        if ((currentNumber % totalThreads) == threadId) {
            std::cout << "Thread " << threadId << ": " << currentNumber << std::endl;
            currentNumber++;
        }
    }
}

int main() {
    
    const int totalThreads = std::thread::hardware_concurrency();;  // Number of threads supported 

    std::thread threads[totalThreads];

    for (int i = 0; i < totalThreads; ++i) {
        threads[i] = std::thread(printNumbers, i, totalThreads);
    }

    for (int i = 0; i < totalThreads; ++i) {
        threads[i].join();
    }

    return 0;
}
