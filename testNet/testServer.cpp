#include<WinSock2.h>
#include <WS2tcpip.h>
#include<iostream>
#pragma comment(lib,"ws2_32")
//vs环境下必须定义，否则无法使用inet_addr函数
#define _WINSOCK_DEPRECATED_NO_WARNINGS  1;
using namespace std;

//1.网络环境初始化
/*
* 初始化网络环境的函数，其函数原型
int WSAStartup(
	WORD wVersionRequested, //版本号，使用MAKEWORD宏生成
	LPWSADATA lpWSAData //数据
);
//返回值：0代表成功，否则失败
第一个wVersionRequested参数就是用来指定准备加载动态库的版本号，
高字节为库文件的副版本，低字节指定主版本，而MAKEWORD(X,Y)宏
用于生成该参数，其中X为高字节，Y为低字节。

而第二个lpWSAData 为指向WSADATA结构体的指针

typedef struct WSAData {
	WORD  			wVersion; //期望调用者使用的socket版本
	//（或实际返回的socket版本，可根据此参数判断返回的版本号是否正确
	//，可通过HIBYTE宏取得高字节，LOBYTE宏取得低字节）
	WORD  			wHighVersion; //本机Dll支持的最高版本
	unsigned short  iMaxSockets;//一个进程最多可以打开的套接字数量（2.0版本后忽略此值）
	unsigned short  iMaxUdpDg; //一个进程发送或接收的最大数据报长度
	char FAR* lpVendorInfo; //厂商专有信息（2.0版本后忽略此值）
	char    		szDescription[WSADESCRIPTION_LEN + 1]; //DLL的描述信息
	char    		szSystemStatus[WSASYS_STATUS_LEN + 1];//DLL的状态信息
};
*/ 
int test01() {
	WSADATA data;
	int ret = WSAStartup(MAKEWORD(2, 2), &data);
	if (ret) {
		cout << "初始化网络错误！" << endl;

		return ret;
	}
}

//2.创建服务器套接字 socket
/*
SOCKET socket(
int af,	//地址类型，常用IPv4地址：AF_INET，和IPv6地址：AF_INET6
int type, //套接字类型，常用TCP协议：SOCK_STREAM,UDP协议：SOCK_DGRAM
int protocol //协议类型，一般填0，自动选择即可
);
//返回值，INVALID_SOCKET失败，该宏实则定义为-1，否则成功
*/ 
SOCKET test02() {
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		cout << "创建套接字失败";
		WSACleanup();
	}
	return sock;
}

/*int bind(
SOCKET s, //创建的socket
sockaddr * name, //包含地址和端口的结构体
int namelen //sockaddr 结构长度
);
//返回值：返回SOCKET_ERROR失败，该宏被定义为-1，否则成功，返回值为0
*/

//3.绑定本机IP和端口：bind
sockaddr_in test03(SOCKET sock,const char str_addr[],int host) {
	sockaddr_in addr;
	addr.sin_family = AF_INET; //地址为IPv4协议
	addr.sin_port = htons(host); //端口为9999
	//addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); //绑定到本机的ip地址
	//在vs2013版本后使用inet_pton，使用inet_addr会报错c4996,需要修改项目配置

	inet_pton(AF_INET, str_addr, &addr.sin_addr.s_addr);
	//inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);
	int ret = bind(sock, (sockaddr*)&addr, sizeof(addr)); //绑定
	if (ret == -1) {
		cout << "绑定地址端口失败";
	}
	return addr;
}

//4.监听客户端：listen
/*int listen(
SOCKET s, //要监听的socket
int backlog //等待连接的最大队列长度
);
//返回值：返回SOCKET_ERROR失败，该宏被定义为-1，否则成功，返回值为0
*/
int test04(SOCKET sock) {
	int ret = listen(sock, 5);
	if (ret == -1) {
		cout << "监听套接字失败";
		WSACleanup();
		return -1;
	}
	else {
		cout<<"开始监听" << endl;
	}
}

//5.等待客户端连接：accept
/*SOCKET accept(
SOCKET s, //接收的socket
sockaddr* addr, //接收到客户端的地址信息
int * addrlen //地址信息长度
);
//返回值：返回INVALID_SOCKET失败，该宏定义为-1，否则成功返回客户端的套接字，可进行发送和接收消息
*/
SOCKET test05(SOCKET sock) {
	sockaddr addrCli;
	int len = sizeof(addrCli);
	SOCKET sockCli = accept(sock, &addrCli, &len);
	if (sockCli == -1) {
		cout << "接收客户端连接失败";
		WSACleanup(); 
	}
	else {
		cout << "接收客户端连接成功";
	}
	return sockCli;
}

//6.发送消息：send
/*int send(
SOCKET s,
char * buf,//要发送的内容
int len, //内容长度
int flags //一般为0，拷贝到程序中就立即删除内核中的数据,或MSG_DONTROUTE:要求传输层不要将数据路由出去，MSG_OOB：标志数据应该被带外发送
);
//返回值：-1（或宏SOCKET_ERROR）表示发送失败，否则返回发送成功的字节数
*/

int test06(SOCKET sock, SOCKET sockCli) {
	char buf[0xFF] = "我是服务器";
	int ret = send(sockCli, buf, strlen(buf)+1, 0);
	if (ret == -1) {
		cout << "发送信息失败";
		WSACleanup();
		return -1;
	}
}

/*int recv(
SOCKET s, //套接字
 char * buf, //接受数据的缓存区
int len, //缓存区大小
int flags //标志，一般填0，将消息拷贝到应用程序中，将内核中的数据删除，
还可以填MSG_PEEK,只取数据，不从内核中删除数据，MSG_OOB：处理带外数据
);
//返回值：小于等于0都表示出错，大于0则表示接收成功的数据大小
*/

//7.接收消息：recv 
int test07(SOCKET sockCli, char  buf[]) {
	int ret = recv(sockCli, buf, 0xFF, 0);
	if (ret <= 0) {
		cout << "接受客户端数据失败";
		WSACleanup();
		return -1;
	}
	else
	{
		cout << buf << endl;
	}
}

//8.关闭socket：closesocket
/*
int closesocket(
SOCKET s //要关闭的socket
);
*/
//9.清除网络环境：WSACleanup 无任何参数，直接调用即可
