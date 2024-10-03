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
        std::unique_lock<std::mutex> lock(mtx); // Locks the mutex
        ++ count;
        std::cout<<"Count after increment: "<<count <<"\n";
        lock.unlock(); // Unlocks the mutex manually
    }
    
    int getCount() {
        std::unique_lock<std::mutex> lock(mtx);
        return count;
    }
};

void threadTask(Counter &counter) {
    for (int i=0; i<5; ++i)
        counter.increment();
}

int main() {
	Counter counter;
	
	std::thread t1(threadTask, std::ref(counter)); // Start first thread
	std::thread t2(threadTask, std::ref(counter)); // Start second thread
	
	t1.join();
	t2.join();
	
	std::cout<<"Final count: "<< counter.getCount() << "\n";
	
	return 0;
}
