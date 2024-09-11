#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <atomic>

using namespace std;

void increment(shared_ptr<atomic<int>> value)
{
    // Loop 1 million times, incrementing value
    for (unsigned int i = 0; i < 1000000; ++i)
        // Increment value
        (*value)++;
}

int main(int argc, char **argv)
{
    // Create a shared int value
    auto value = make_shared<atomic<int>>();

    // Create number of threads hardware natively supports
    auto num_threads = thread::hardware_concurrency();
    vector<thread> threads;
    for (unsigned int i = 0; i < num_threads; ++i)
        threads.push_back(thread(increment, value));

    // Join the threads
    for (auto &t : threads)
        t.join();

    // Display the value
    cout << "Value = " << *value << endl;
}