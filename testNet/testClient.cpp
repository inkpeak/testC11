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
		cout << "���ӷ�����ʧ��" << endl;
		return -1;
	}
	else
	{
		cout << "���ӷ������ɹ�" << endl;
	}
}

int testSend(SOCKET sock, char  buf[],int ret) { 
	cout << strlen(buf) << endl; 
	cout << sizeof(buf) << endl;
	ret=send(sock, buf, ret, 0); //�����յ������ݷ��ط�����
	cout << strlen(buf) << endl;
	cout << sizeof(buf) << endl;
	if (ret <= 0) {
		WSACleanup();
		cout << "���ͷ���������ʧ��" << endl;
		return -1;
	}
}

  
int testRecv(SOCKET sock, char  buf[0xFF]) {
	int ret = recv(sock, buf, 0xFF, 0);
	if (ret <= 0) {
		WSACleanup();
		cout << "���շ���������ʧ��" << endl;
		 
	}
	else {
		cout << buf<< endl;
		return ret;
	}

}

 