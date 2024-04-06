// example_server.cpp
#include "test.pb.h"
#include <brpc/server.h>

// 实现.proto文件中定义的ExampleService
class ExampleServiceImpl : public example::ExampleService {
public:
  ExampleServiceImpl(){};
  virtual ~ExampleServiceImpl(){};

  virtual void Echo(google::protobuf::RpcController *cntl_base,
                    const example::EchoRequest *request,
                    example::EchoResponse *response,
                    google::protobuf::Closure *done) {
    brpc::ClosureGuard done_guard(done);

    // 简单地返回请求中的消息
    response->set_response("Echo: " + request->message());
  }
};

int main(int argc, char *argv[]) {
  brpc::Server server;

  ExampleServiceImpl example_service_impl;

  // 添加服务
  if (server.AddService(&example_service_impl,
                        brpc::SERVER_DOESNT_OWN_SERVICE) != 0) {
    LOG(ERROR) << "Failed to add service";
    return -1;
  }

  // 启动服务
  brpc::ServerOptions options;
  if (server.Start(8000, &options) != 0) {
    LOG(ERROR) << "Failed to start EchoServer";
    return -1;
  }

  // 等待服务结束
  server.RunUntilAskedToQuit();
  return 0;
}
