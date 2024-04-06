// example_client.cpp
#include "test.pb.h"
#include <brpc/channel.h>

int main(int argc, char *argv[]) {
  brpc::Channel channel;

  // 初始化Channel，连接到本地的8000端口
  brpc::ChannelOptions options;
  options.protocol = brpc::PROTOCOL_HTTP;
  if (channel.Init("localhost:8000", &options) != 0) {
    LOG(ERROR) << "Failed to initialize channel";
    return -1;
  }

  example::ExampleService_Stub stub(&channel);

  // 创建一个请求和响应
  example::EchoRequest request;
  example::EchoResponse response;
  brpc::Controller cntl;

  // 设置请求的消息
  request.set_message("Hello BRPC");

  // 调用RPC方法
  stub.Echo(&cntl, &request, &response, NULL);

  if (!cntl.Failed()) {
    LOG(INFO) << "Received response from server: " << response.response();
  } else {
    LOG(ERROR) << "Failed to send request or receive response: "
               << cntl.ErrorText();
  }

  return 0;
}
