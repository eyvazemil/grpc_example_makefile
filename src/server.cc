#include "server_implementation.h"

#include <string>
#include <iostream>

void run(const std::string &, const std::string &);

int main(int argc, char ** argv) {
    // read command line arguments
    std::string str_ip = std::string(argv[1]);
    std::string str_port = std::string(argv[2]);

    // run grpc greeting service
    run(str_ip, str_port);
    
    return 0;
}

void run(const std::string & str_ip, const std::string & str_port) {
    std::string str_address = str_ip + ":" + str_port;
    ServerImplementation service;

    grpc::ServerBuilder builder;

    builder.AddListeningPort(str_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on port: " << str_address << std::endl;

    server->Wait();
}
