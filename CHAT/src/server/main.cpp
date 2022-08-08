#include<iostream>
#include<signal.h>
#include "chatserver.hpp"
#include "chatservice.hpp"

using namespace std;

void resetHandler(int){	//这个int就算你不用也加上
    ChatService::instance()->reset();
    exit(0);
}

int main(){
		//捕捉 Ctrl+C 信号
    signal(SIGINT,resetHandler);

    EventLoop loop;
    InetAddress addr("127.0.0.1",7000);
    ChatServer server(&loop,addr,"ChatServer");

    server.start();
    loop.loop();
    return 0;
}
