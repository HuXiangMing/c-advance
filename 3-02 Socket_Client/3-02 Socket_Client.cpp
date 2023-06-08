// 3-02 Socket_Client.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。


#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <ctime>
#include <thread>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

class Client
{
public:
    Client(const std::string& server_ip, int server_port):
        server_ip(server_ip), server_port(server_port), client_socket(-1), connected(false) {}

    ~Client()
    {
        stop();
    }

    bool start()
    {

        //初始化 Winsock 库。
        WORD sockVersion = MAKEWORD(2, 2);
        WSADATA wsdata;
        if (WSAStartup(sockVersion, &wsdata) != 0)
        {
            std::cout << "Winsock库初始化失败" << errno << std::endl;
            return false;
        }

        // 创建socket
        client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (client_socket == -1)
        {
            std::cout << "创建socket失败: " << errno << std::endl;
            return false;
        }

        // 连接到服务器
        sockaddr_in server_address;
        memset(&server_address, 0, sizeof(server_address));
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(server_port);

        //inet_pton()将点分十进制数形式的IP地址转换为网络字节序的32位二进制值
        if (inet_pton(AF_INET, server_ip.c_str(), &server_address.sin_addr) == 0)
        {
            std::cout << server_ip <<"IP地址不合法，无法转换" << errno << std::endl;
            closesocket(client_socket);
            client_socket = -1;
            return false;
        }
        
        //连接服务器
        if (connect(client_socket, (sockaddr*)&server_address, sizeof(server_address)) == -1)
        {
            std::cout << "连接服务器失败: " << errno << std::endl;
            closesocket(client_socket);
            client_socket = -1;
            return false;
        }

        std::cout << "连接服务器成功" << std::endl;
        connected = true;


        receive_message(client_socket);
        //send_message("服务器你好");



        // 启动接收消息线程
        //std::thread receive_thread(&Client::receive, this);
        //receive_thread.detach();
        //
        return true;
    }

    void stop() {
        if (connected) {
            connected = false;
            closesocket(client_socket);
            client_socket = -1;
        }
    }


    void send_message(const char*message)
    {
        send(client_socket, message, strlen(message), 0);
        std::cout << "消息已经发出:" << message <<std::endl;

        //等待接收
    }
   

private:

    std::string server_ip;     // 服务器IP地址
    int server_port;           // 服务器端口号
    int client_socket;         // 客户端socket
    bool connected;            // 是否已连接服务器





    //接收消息
    void receive_message(int client_socket)
    {
        //先读取消息头，获取长度
        int message_len = 0;
        int total_bytes_received = 0;//接收到的字节长度

        while (total_bytes_received < sizeof(int))
        {
            int bytes_received = recv(client_socket, ((char*)&message_len) + total_bytes_received, sizeof(int) - total_bytes_received, 0);

            if (bytes_received <= 0)
            {
                std::cerr << "接收消息长度失败" << std::endl;
                closesocket(client_socket);
                return;
            }

            total_bytes_received += bytes_received;
        }
        message_len = ntohl(message_len);

        //根据消息长度夺取对应的消息体
        char* buffer = new char[message_len];
        total_bytes_received = 0;

        while (total_bytes_received < message_len)
        {
            int bytes_received = recv(client_socket, buffer + total_bytes_received, message_len - total_bytes_received, 0);

            if (bytes_received <= 0)
            {
                std::cerr << "接收消息体失败" << std::endl;
                closesocket(client_socket);
                delete[] buffer;
                return;
            }

            total_bytes_received += bytes_received;
        }



        std::string str = buffer;

        std::cout << "已从客户端接收消息：" << buffer <<"。" << std::endl;

        delete[] buffer;
    }

};

int main()
{
    //std::string server_address = "127.0.0.1";
    std::string server_address = "192.168.10.117";
    int server_port = 5566;
    Client client(server_address, server_port);
    client.start();
    while (true)
    {
        //// 获取当前时间
        //time_t now = time(0);
        //// 将时间转换为结构体tm
        //struct tm* localTime = localtime(&now);
        //client.send_message(asctime(localTime));
        //
        //std::this_thread::sleep_for(std::chrono::microseconds(100));
    
    }
    std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
