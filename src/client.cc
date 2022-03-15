#include "client_implementation.h"

#include <grpcpp/create_channel.h>
#include <string>

void run(const std::string &, const std::string &);

int main(int argc, char ** argv) {
    // read command line arguments
    std::string str_ip = std::string(argv[1]);
    std::string str_port = std::string(argv[2]);

    // run the client side
    run(str_ip, str_port);

    return 0;
}

void run(const std::string & str_ip, const std::string & str_port) {
    std::string str_address = str_ip + ":" + str_port;

    ClientImplementation client(grpc::CreateChannel(
        str_address, grpc::InsecureChannelCredentials())
    );

    std::string str_response = client.sendRequest("Test");

    std::cout << "Answer reseived from server: " << str_response << std::endl;
}
