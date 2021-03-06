#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include<iostream>

// protobuf .h file
#include"proto_file.pb.h"

using namespace std;
#define PORT 8080
#define BUFSIZE 1024
   
int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }else
        cout<<"Socket create!\n";
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }else
        cout<<"Socket connect success!\n";

    // ===========================================
    // protobuf test
    cout<<"\n----------------------------\n";
    cout<<"client:\n";
    myPackage::DATA d2;
    char buf[BUFSIZE];

    recv(sock, buf, BUFSIZE, MSG_WAITALL);
    
	d2.ParseFromArray(buf, BUFSIZE);
	cout<<"x_axis: "<<d2.x_axis()<<endl;
    cout<<"y_axis: "<<d2.y_axis()<<endl;
    // ===========================================
    return 0;
}