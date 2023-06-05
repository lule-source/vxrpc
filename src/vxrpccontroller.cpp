#include "vxrpccontroller.h"

MprpcController::MprpcController()
{
    m_failed = false;
    m_errText = "";
}

void MprpcController::Reset()
{
    v_failed = false;
    v_errText = "";
}

bool MprpcController::Failed() const
{
    return v_failed;
}

std::string MprpcController::ErrorText() const
{
    return v_errText;
}

void MprpcController::SetFailed(const std::string &reason)
{
    v_failed = true;
    v_errText = reason;
}

void MprpcController::StartCancel() {}
bool MprpcController::IsCanceled() const { return false; }
void MprpcController::NotifyOnCancel(google::protobuf::Closure *callback) {}