#include "server_implementation.h"

grpc::Status ServerImplementation::sendRequest(grpc::ServerContext * context, 
    const greeting::Request * request, greeting::Response * response
) {
    response->set_str_response(std::string("Hello ") + request->str_request());

    return grpc::Status::OK;
}
