#ifndef CONFIG_H
#define CONFIG_H

#include "webserver.h"

using namespace std;

class Config
{
private:
    /* data */
public:
    Config();
    ~Config() {};

    void parse_arg(int argc, char *argv[]);

    int PORT;
    int LOGWrite;
    int TRIGMode;

    // listenfd触发方式
    int LISTENTrigmode;
    // connfd触发方式
    int CONNTrigmode;

    // 优雅关闭链接
    int OPT_LINGER;

    // 数据库连接池数量
    int sql_num;

    // 线程池线程数目
    int thread_num;

    // 是否关闭日志
    int close_log;

    // 并发模型选择
    int actor_model;
};

#endif
