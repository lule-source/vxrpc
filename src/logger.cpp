#include "logger.h"
#include <time.h>
#include <iostream>

Logger& Logger::GetInstance()
{
    static Logger logger;
    return logger;
}

Logger::Logger()
{
    std::thread writeLogTask([&](){
        for (;;)
        {
            // 获取当前的日期，然后取日志信息，写入相应的日志文件
            time_t now = time(nullptr);
            tm *nowtm = localtime(&now);

            char file_name[128];
            sprintf(file_name, "%d-%d-%d-log.txt", nowtm->tm_year+1900, nowtm->tm_mon+1, nowtm->tm_mday);

            FILE *pf = fopen(file_name, "a+");
            if (pf == nullptr)
            {
                std::cout << "logger file : " << file_name << " open error!" << std::endl;
                exit(EXIT_FAILURE);
            }

            std::string msg = v_lckQue.Pop();

            char time_buf[128] = {0};
            sprintf(time_buf, "%d:%d:%d =>[%s] ", 
                    nowtm->tm_hour, 
                    nowtm->tm_min, 
                    nowtm->tm_sec,
                    (v_loglevel == INFO ? "info" : "error"));
            msg.insert(0, time_buf);
            msg.append("\n");

            fputs(msg.c_str(), pf);
            fclose(pf);
        }
    });
    writeLogTask.detach();
}

// 设置日志级别 
void Logger::SetLogLevel(LogLevel level)
{
    v_loglevel = level;
}

void Logger::Log(std::string msg)
{
    v_lckQue.Push(msg);
}