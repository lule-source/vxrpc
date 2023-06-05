#pragma once
#include <google/protobuf/service.h>
#include <string>

class VxrpcController : public google::protobuf::RpcController
{
public:
    VxrpcController();
    void Reset();
    bool Failed() const;
    std::string ErrorText() const;
    void SetFailed(const std::string &reason);

    // TODO
    void StartCancel();
    bool IsCanceled() const;
    void NotifyOnCancel(google::protobuf::Closure *callback);

private:
    bool v_failed;         // RPC方法执行过程中的状态
    std::string v_errText; // RPC方法执行过程中的错误信息
};