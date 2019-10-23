enum {ID_PING};

struct Ping : Message{ //arv i structs: Ping arver fra Message
    std::string s;
};

MsgQueue mq(10);

struct Car{
    int id;
};

void* sender(void*){
    while(true){
        //std::cout << "Sending ping..." << std::endl;
        Ping* p = new Ping{"Davs"};
        mq.send(ID_PING, p);
        sleep(1);
    }

    return nullptr;
}

void* receiver(void* data){
    Car* c = static_cast<Car*>(data);
    for(;;){
        unsigned long id;
        Message *msg = mq.receive(id);
        //std::cout << "Handling incoming message" << std::endl;
        dispatcher(id, msg);
        delete(msg);
    }
    return nullptr;
}

void handleIDPing(Car* c, Ping* p){
    std::cout << "Car ID :#" << c->id << " ''" << p->s << "'" <<std::endl;
}

void dispatcher(Car* c,unsigned long id, Message* msg){
    switch(id){
        case ID_PING:
            handleIDPing(c, static_cast<Ping*>(msg));
        default:
            std::cout << "Unknown event..." << std::endl;
    }
}



int main(){
    pthread_t id1, id2;
    pthread_create(id1, nullptr, receiver, new Car(42));
    pthread_create(id2, nullptr, receiver, nullptr);
    pthread_join(id1);
    pthread_join(id2);

    return 0;
}
