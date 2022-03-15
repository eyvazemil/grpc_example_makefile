#ifndef SERVER_IMPLEMENTATION_H
#define SERVER_IMPLEMENTATION_H

#include "../build/greeting.grpc.pb.h"

#include <string>
#include <grpcpp/grpcpp.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using greeting::Greeting;
using greeting::Request;
using greeting::Response;

class ServerImplementation final : public greeting::Greeting::Service {
public:
    grpc::Status sendRequest(grpc::ServerContext * context, 
        const greeting::Request * request, greeting::Response * response
    ) override;
};

#endif // SERVER_IMPLEMENTATION_H
