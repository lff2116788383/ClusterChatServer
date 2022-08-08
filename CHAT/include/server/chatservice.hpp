#ifndef CHATSERVICE_H_
#define CHATSERVICE_H_

#include<muduo/net/TcpConnection.h>
#include<unordered_map>
#include<functional>
#include<mutex>

#include "json.hpp"
#include "usermodel.hpp"
#include "offlinemessagemodel.hpp"
#include "friendmodel.hpp"


using json = nlohmann::json;
using namespace std;
using namespace muduo;
using namespace muduo::net;


//处理消息的事件回调方法类型
using MsgHandler = std::function<void(const TcpConnectionPtr &conn,json &js,Timestamp time)>;

//聊天服务器业务
class ChatService{
public:
    //单例模式
    static ChatService* instance();
    
    void login(const TcpConnectionPtr &conn,json &js,Timestamp time);
    void reg(const TcpConnectionPtr &conn,json &js,Timestamp time);
    void clientCloseException(const TcpConnectionPtr &conn);
    void reset();
    void onechat(const TcpConnectionPtr &conn,json &js,Timestamp time);
    
    //添加好友
    void addFriend(const TcpConnectionPtr &conn,json &js,Timestamp time);


    //获取消息对应的处理器
    MsgHandler getHandle(int msgid);
    
private:

    ChatService();

    //存储消息id和对应的处理方法
    unordered_map<int,MsgHandler> _msgHanderMap;

    //存储在线用户连接
    unordered_map<int,TcpConnectionPtr> _userConnMap;
    
    //数据操作类的对象
    UserModel _usermodel;

    //定义互斥锁
    mutex _connMutex;
    OfflineMessageModel _offlineMsgmodel;
    FriendModel _friendmodel;
};


#endif
