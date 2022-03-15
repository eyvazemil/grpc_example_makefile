LDFLAGS = -L/home/emil/.local/lib `pkg-config --libs protobuf grpc++`\
           -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed\
           -ldl

CXX = g++
CPPFLAGS += `pkg-config --cflags protobuf grpc++ grpc`
CXXFLAGS += -std=c++17

GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`

SERVER = server.out
CLIENT = client.out
OBJECTS_PB = build/greeting.pb.o build/greeting.grpc.pb.o
OBJECTS_SERVER = build/server.o build/server_implementation.o
OBJECTS_CLIENT = build/client.o build/client_implementation.o

# program arguments
IP = 0.0.0.0
PORT = 5000

all: build/greeting.pb.cc build/greeting.grpc.pb.cc $(OBJECTS_PB) $(OBJECTS_SERVER) $(OBJECTS_CLIENT) compile_server compile_client

compile_server: $(OBJECTS_PB) $(OBJECTS_SERVER)
	$(CXX) $(CXXFLAGS) $(OBJECTS_PB) $(OBJECTS_SERVER) $(LDFLAGS) -o $(SERVER)

compile_client: $(OBJECTS_PB) $(OBJECTS_CLIENT)
	$(CXX) $(CXXFLAGS) $(OBJECTS_PB) $(OBJECTS_CLIENT) $(LDFLAGS) -o $(CLIENT)

run_server:
	./server.out $(IP) $(PORT)

run_client:
	./client.out $(IP) $(PORT)

build/greeting.pb.cc: ./src/greeting.proto
	protoc --proto_path=./src --cpp_out=./build ./src/greeting.proto
	
build/greeting.grpc.pb.cc: ./src/greeting.proto
	protoc --proto_path=./src --grpc_out=./build --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) ./src/greeting.proto
	
build/server.o: ./src/server.cc ./src/server_implementation.h ./src/server_implementation.cc
	$(CXX) $(CXXFLAGS) -c ./src/server.cc -o $@ $(CPPFLAGS)

build/client.o: ./src/client.cc ./src/client_implementation.h ./src/client_implementation.cc
	$(CXX) $(CXXFLAGS) -c ./src/client.cc -o $@ $(CPPFLAGS)

build/server_implementation.o: ./src/server_implementation.h ./src/server_implementation.cc
	$(CXX) $(CXXFLAGS) -c ./src/server_implementation.cc -o $@ $(CPPFLAGS)

build/client_implementation.o: ./src/client_implementation.h ./src/client_implementation.cc
	$(CXX) $(CXXFLAGS) -c ./src/client_implementation.cc -o $@ $(CPPFLAGS)

clean:
	rm -f ./build/*.o ./build/*.pb.cc ./build/*.pb.h client.out server.out