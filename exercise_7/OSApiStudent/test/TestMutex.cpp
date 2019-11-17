#include <iostream>
#include <osapi/Mutex.hpp>
#include <osapi/Conditional.hpp>
#include <osapi/Thread.hpp>
#include <osapi/Utility.hpp>

osapi::Mutex mtx1; //Global common Mutex

class TestMutex : public osapi::ThreadFunctor {
public:
    TestMutex(int id) : thread_id(id){}

    virtual void run(){

        for(;;){
            mtx1.lock();
            std::cout << "Mutex locked from " <<  thread_id << std::endl;
            mtx1.unlock();
            osapi::sleep(1500);
        }

    }
private:
    int thread_id;
};


int main(){
    {
        TestMutex tm1(1);
        TestMutex tm2(2);

        osapi::Thread thread1(&tm1);
        osapi::Thread thread2(&tm2);

        thread1.start();
        thread2.start();

        thread1.join();
        thread2.join();
    }
}
