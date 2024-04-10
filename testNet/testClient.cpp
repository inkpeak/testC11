#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<iostream>
#pragma comment(lib,"ws2_32.lib")
using std::endl;
using std::cout;

int testConn(SOCKET sock, sockaddr_in addr) {
	int ret = connect(sock, (sockaddr*)&addr, sizeof(addr)); 
	if (ret == -1) {
		WSACleanup();
		cout << "连接服务器失败" << endl;
		return -1;
	}
	else
	{
		cout << "连接服务器成功" << endl;
	}
}

int testSend(SOCKET sock, char  buf[],int ret) { 
	cout << strlen(buf) << endl; 
	cout << sizeof(buf) << endl;
	ret=send(sock, buf, ret, 0); //将接收到的数据发回服务器
	cout << strlen(buf) << endl;
	cout << sizeof(buf) << endl;
	if (ret <= 0) {
		WSACleanup();
		cout << "发送服务器数据失败" << endl;
		return -1;
	}
}

  
int testRecv(SOCKET sock, char  buf[0xFF]) {
	int ret = recv(sock, buf, 0xFF, 0);
	if (ret <= 0) {
		WSACleanup();
		cout << "接收服务器数据失败" << endl;
		 
	}
	else {
		cout << buf<< endl;
		return ret;
	}

}

 