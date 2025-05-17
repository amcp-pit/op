#include <iostream> 
#include <thread>
#include <atomic> 

int main() { 
    std::atomic<unsigned long long> g_count { 0 }; 
    std::thread thr1([&]() 
       { 
           for(auto i = 0; i < 1'000'000; ++i) g_count.fetch_add(1); 
        }); 
    std::thread thr2([&]() 
       { 
           for(auto i = 0; i < 1'000'000; ++i) g_count.fetch_add(1); 
       });
    thr1.join(); 
    thr2.join(); 
    std::cout << g_count << std::endl; 
    return 0; 
}
