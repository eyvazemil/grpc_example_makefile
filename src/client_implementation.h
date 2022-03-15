#ifndef CLIENT_IMPLEMENTATION_H
#define CLIENT_IMPLEMENTATION_H

#include "../build/greeting.grpc.pb.h"

#include <string>
#include <grpcpp/grpcpp.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using greeting::Greeting;
using greeting::Request;
using greeting::Response;

class ClientImplementation {
public:
    ClientImplementation(std::shared_ptr<grpc::Channel> channel);
    std::string sendRequest(const std::string & str_request);

private:
    std::unique_ptr<greeting::Greeting::Stub> m_stub;
};

#endif // CLIENT_IMPLEMENTATION_H
