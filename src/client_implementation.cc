#include "../include/client_implementation.h"

#include <grpcpp/client_context.h>

ClientImplementation::ClientImplementation(std::shared_ptr<grpc::Channel> channel) : m_stub(greeting::Greeting::NewStub(channel)) {}

std::string ClientImplementation::sendRequest(const std::string & str) {
    // create a request object that will be sent to the grpc service
    greeting::Request request;

    request.set_str_request(str);

    // create a responce object that will be recived from grpc service
    greeting::Response response;

    grpc::ClientContext context;

    // send request
    grpc::Status status = m_stub->sendRequest(&context, request, &response);

    if(!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return "";
    }
    
    return response.str_response();
}
