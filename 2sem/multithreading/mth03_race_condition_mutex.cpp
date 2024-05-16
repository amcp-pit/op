#include <iostream> 
#include <thread>
#include <mutex> 
int main() { 
    unsigned long long g_count = 0; 
    std::mutex g_count_mutex; 
    std::thread thr1([&]() { 
          for(auto i = 0; i < 1'000'000; ++i) { 
               g_count_mutex.lock(); g_count += 1; g_count_mutex.unlock(); 
          } 
    }); 
    std::thread thr2([&]() { 
           for(auto i = 0; i < 1'000'000; ++i) { 
               g_count_mutex.lock(); g_count += 1; g_count_mutex.unlock(); 
          } 
    });
    thr1.join(); 
    thr2.join(); 
    std::cout << g_count << std::endl; 
    return 0; 
}

