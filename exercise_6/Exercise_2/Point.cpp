#include "MsgQueue.h"
#include <pthread.h>
#include <unistd.h>
#include <iostream>

enum {ID_POINTS};

struct Point3D : public Message {
	Point3D(int a, int b, int c) : x(a), y(b), z(c) {}
	int x;
	int y;
	int z;
};

void printPoint3DVars(Point3D *p){
	std::cout << "Point x,y,z: " << p->x << "," << p->y << "," << p->z << std::endl;
}

void handleMsg(unsigned long id, Message* msg){
	switch(id){
        case ID_POINTS:
            printPoint3DVars(static_cast<Point3D*>(msg));
			break;
        default:
            std::cout << "Unknown event..." << std::endl;
			break;
    }
}

void* senderFunction(void* arg){

	MsgQueue* mq = static_cast<MsgQueue*>(arg);

    for(;;){
        Point3D* point = new Point3D(1,2,3);
        mq->send(ID_POINTS, point);
        sleep(1);
    }

    return nullptr;
}

void* receiverFunction(void* arg){

	MsgQueue* mq = static_cast<MsgQueue*>(arg);

    for(;;){
		unsigned long id = 0;
        Message* msg = mq->receive(id);
		handleMsg(id, msg);
        delete msg;
    }

    return nullptr;
}

int main(){

	MsgQueue msgQueue(10);

	pthread_t send_thread, receive_thread;

	pthread_create(&send_thread, NULL, senderFunction, &msgQueue);
	pthread_create(&receive_thread, NULL, receiverFunction, &msgQueue);

	pthread_join(send_thread, NULL);
	pthread_join(receive_thread, NULL);

	return 0;
}
