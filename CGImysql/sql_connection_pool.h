#ifndef _CONNECTION_POOL_
#define _CONNECTION_POOL_

#include <stdio.h>
#include <list>
#include <mysql/mysql.h>
#include <error.h>
#include <string.h>
#include <iostream>
#include <string>
#include "../lock/locker.h"
#include "../log/log.h"

using namespace std;

class connection_pool
{
public:
    MYSQL *GetConnection(); // 获取数据库连接
    bool ReleaseConnection(MYSQL *conn);
    int GetFreeConn();  // 获取空闲连接
    void DestroyPool(); // 销毁所有连接

    // 单例模式
    static connection_pool *GetInstance();

    void init(string url, string User, string PassWord, string DataBaseName, int Port, int MaxConn, int close_log);

private:
    connection_pool();
    ~connection_pool();

    int m_MaxConn;  // 最大连接数目
    int m_CurConn;  // 当前已使用的连接数目
    int m_FreeConn; // 当前空闲连接数目
    locker lock;
    list<MYSQL *> connList; // 连接池
    sem reserve;

public:
    string m_url;  // 主机地址
    string m_Port; // 数据库端口号
    string m_User;
    string m_PassWord;
    string m_DatabaseName;
    int m_close_log; // 日志开关
};

/*
用于管理数据库连接的获取和释放
这个类的目的是提供一种安全和自动管理数据库连接的方式。通过使用这个类,
您可以确保数据库连接总是被正确地返回到连接池,
即使发生异常或者函数提前返回
 */
class connectionRAII
{
private:
    MYSQL *conRAII;
    connection_pool *pollRAII;

public:
    connectionRAII(MYSQL **con, connection_pool *connPool);
    ~connectionRAII();
};

#endif
