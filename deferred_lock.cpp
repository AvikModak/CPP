#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

class Counter {

private:
    int count;
    std::mutex mtx; // Mutex to protect access to 'count'
    
public:
    Counter() : count(0) {};
    
    void increment() {
        std::unique_lock<std::mutex> lock(mtx, std::defer_lock); // Deferred locking
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
        
        lock.lock(); // Lock manually when needed
        count ++;
        std::cout<<"Count after increment: "<<count <<"\n";
        // Lock will be automatically released when `lock` goes out of scope
    }
    
};

void threadTask(Counter &counter) {
    counter.increment();
}

int main() {
	Counter counter;
	
	std::thread t1(threadTask, std::ref(counter)); // Start first thread
	std::thread t2(threadTask, std::ref(counter)); // Start second thread
	
	t1.join();
	t2.join();
	
	return 0;
}
