#include <iostream> 
#include <thread> 
int main() { 
    unsigned long long g_count = 0; 

    std::thread thr1([&]() 
        { 
            for(auto i = 0; i < 1'000'000; ++i) ++g_count; 
        }); 

    std::thread thr2([&]() 
        { 
            for(auto i = 0; i < 1'000'000; ++i) ++g_count; 
        }); 

    thr1.join(); 
    thr2.join(); 
    std::cout << g_count << std::endl; 
    return 0; 
}

