#include <iostream>
#include <osapi/Mutex.hpp>
#include <osapi/Conditional.hpp>
#include <osapi/Thread.hpp>
#include <osapi/Utility.hpp>

osapi::Mutex mtx; //Global common Mutex

osapi::Conditional cond; //Global common cond
bool wait = false;  //Predicate

class TestConditionals1 : public osapi::ThreadFunctor {
public:
    TestConditionals1(int id) : thread_id(id){}

    virtual void run(){

        for(;;){
            mtx.lock();
            std::cout << "Mutex locked from " <<  thread_id << std::endl;
            while(!wait){
                cond.wait(mtx);
            }
            std::cout << "Wait over from " << thread_id << std::endl;
            wait = false;
            mtx.unlock();
            osapi::sleep(1500);
        }

    }
private:
    int thread_id;
};

class TestConditionals2 : public osapi::ThreadFunctor {
public:
    TestConditionals2(int id) : thread_id(id){}

    virtual void run(){

        for(;;){
            mtx.lock();
            std::cout << "Mutex locked from " <<  thread_id << std::endl;
            wait = true;
            std::cout << "Signaling waiting thread from " << thread_id << std::endl;
            cond.broadcast();
            mtx.unlock();
            osapi::sleep(1500);
        }

    }
private:
    int thread_id;
};


int main(){
    {
        TestConditionals1 tc1(1);
        TestConditionals2 tc2(2);

        osapi::Thread thread1(&tc1);
        osapi::Thread thread2(&tc2);

        thread1.start();
        thread2.start();

        thread1.join();
        thread2.join();
    }
}
