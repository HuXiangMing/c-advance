// 3-01 Socket_Server.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <thread>
#include <vector>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif


//在“附加依赖项”中添加 ws2_32.lib。
//或者#pragma comment (lib, "Ws2_32.lib")
//#pragma comment (lib, "Ws2_32.lib")


class Client
{
public:
	Client(int id, int socket, sockaddr_in address) : id_(id), socket_(socket), address_(address) {}
	int getId() const { return id_; }
	int getSocket() const { return socket_; }
	sockaddr_in getAddress() const { return address_; }

private:
	int id_;
	int socket_;
	sockaddr_in address_;
};




class Server
{
public:
	Server(int port) : server_port(port), server_socket(-1)
	{
		init();
	}
	~Server() 
	{
		if (server_socket != -1)
			closesocket(server_socket);

		WSACleanup();//WSACleanup函数清理socket库。

	};

	bool init()
	{
		//1 创建socket
		if (!creat_tcp_socket()) return false;

		//2 绑定IP地址和端口号。
		if (!bind_socket(server_port)) return false;

		//3  IP 地址和端口号上启动监听
		if (!listen_client()) return false;

		//4 等待连接
		std::cout << "服务器打开成功，等待客户端的连接" << errno << std::endl;
		if (!accept_client()) return false;
	}

private:

	int server_socket;
	unsigned int server_port;
	unsigned int	next_clientID;
	std::vector<std::shared_ptr<Client>> clients;

	//创建socket
	bool creat_tcp_socket()
	{
		//在 Windows 上使用网络通信 API 之前，需要使用 WSAStartup函数初始化socket库；在程序结束时需要使用WSACleanup函数清理socket库
		WORD sockVersion = MAKEWORD(2, 2);
		WSADATA wsdata;
		if (WSAStartup(sockVersion, &wsdata) != 0)
		{
			std::cout << "Winsock库初始化失败" << errno << std::endl;
		}

		server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (server_socket == -1)
		{
			std::cout << "创建socket失败" << errno << std::endl;
			return false;
		}
		return true;
	}

	//绑定socket
	bool bind_socket(short port = 6000)
	{
		//1.初始化一个 IPv4 地址结构体 server_address
		sockaddr_in server_address;//IPv4 地址的结构体类型
		memset(&server_address, 0, sizeof(server_address)); //server_address的所有成员都初始化为 0,以确保其状态正确。
		server_address.sin_family = AF_INET; //server_address 的家族设为 IPv4(即 AF_INET)。
		//htonl 函数将一个长整型数值转换为网络字节序。
		server_address.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //server_address 的 IP 地址设为任意值(INADDR_ANY),表示该地址可以是任何有效的 IPv4 地址。
		server_address.sin_port = htons(port);

		//2.bind 用于将socket与指定的 IP 地址和端口号绑定
		if (bind(server_socket, (const struct sockaddr*)&server_address, sizeof(server_address)) == -1)
		{
			std::cout << "address绑定sockt失败" << std::endl;
			return false;
		}

		return true;
	}


	//开始监听客户端
	bool listen_client(unsigned int backlog = SOMAXCONN)//SOMAXCONN 是一个常量，它表示 TCP/IP 协议栈中允许的最大监听套接字数
	{
		if (listen(server_socket, backlog) == -1) 
		{
			std::cout << "监听sockt失败" << std::endl;
			return false;
		}

		return true;
	}



	//等待客户端的连接请求
	bool accept_client()
	{
		// 创建一个TCP socket对象，用于与客户端通信
		sockaddr_in client_address;
		int client_address_len = sizeof(client_address);

		const char* message = "您已连接服务器";
		while (true)
		{
			int client_socket = accept(server_socket, (sockaddr*)&client_address, &client_address_len);
			if (client_socket == -1)
			{
				std::cerr << "接受客户端连接失败" << std::endl;
				return false;
			}


			// 储存client
			int clientId = next_clientID++;
			std::shared_ptr<Client> client = std::make_shared<Client>(clientId, client_socket, client_address);


			// 在将客户端添加到列表之前，检查客户端是否已存在
			if (!clients.empty()) {
				auto iter = clients.begin();
				while (iter != clients.end()) {
					if (*iter == client) {
						// 如果找到了相同的客户端，则不添加新客户端
						std::cout << "Client " << clientId << " 已存在" << std::endl;
						closesocket(client_socket);
						return false;
					}
					else {
						++iter;
					}
				}
			}
			clients.push_back(client);

			//向客户端发送消息
			send_message(client_socket, message, strlen(message));//字符串结尾的'\0'字符也需要被包括在消息中。因此，该语句将发送不包含结尾'\0'字符的消息。
		}
		
	}





	//发送消息
	void send_message(int client_socket, const char* message, size_t message_len)
	{

		int bytes_sent = send(client_socket, message, message_len, 0);


		std::cout << "已发送消息：" << message << "。" << std::endl;
	}

	//发送消息
	//void send_message(int client_socket, const char* message, size_t message_len)
	//{
	//	//消息总长度
	//	int buffer_len = sizeof(int) + message_len;
	//	//创建一块缓冲区，用于储存消息长度和消息体
	//	char* buffer = new char[buffer_len];
	//
	//	//if (buffer_len < 4)return;
	//	//先写入消息头
	//	memcpy(buffer, &message_len, sizeof(int));
	//	//在写入消息体
	//	memcpy(buffer + sizeof(int), message, message_len);
	//
	//	//发送完整的消息
	//	int bytesSent = send(client_socket, buffer, buffer_len, 0);
	//	if (bytesSent == -1)
	//	{
	//		std::cerr << "发送消息失败" << std::endl;
	//		closesocket(client_socket);
	//		return;
	//	}
	//
	//	std::cout << "已向客户端发送消息：" << message << std::endl;
	//
	//	//释放内存
	//	delete[] buffer;
	//}

	//接收消息
	void receive_message(int client_socket)
	{
		//先读取消息头，获取长度
		int message_len = 0;
		int bytes_received = recv(client_socket, (char*)&message_len, sizeof(int), 0);

		if (bytes_received == -1)
		{
			std::cerr << "接收消息长度失败" << std::endl;
			closesocket(client_socket);
			return;
		}

		//根据消息长度夺取对应的消息体
		char* buffer = new char[message_len];
		bytes_received = recv(client_socket, buffer, message_len, 0);

		if (bytes_received == -1)
		{
			std::cerr << "接收消息长度失败" << std::endl;
			closesocket(client_socket);
			return;
		}

		std::cout << "已从客户端接收消息：" << buffer << std::endl;

		delete[] buffer;
	}
};

int main()
{
	Server server(5566);
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
