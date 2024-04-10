#include<WinSock2.h>
#include <WS2tcpip.h>
#include<iostream>
#pragma comment(lib,"ws2_32")
//vs�����±��붨�壬�����޷�ʹ��inet_addr����
#define _WINSOCK_DEPRECATED_NO_WARNINGS  1;
using namespace std;

//1.���绷����ʼ��
/*
* ��ʼ�����绷���ĺ������亯��ԭ��
int WSAStartup(
	WORD wVersionRequested, //�汾�ţ�ʹ��MAKEWORD������
	LPWSADATA lpWSAData //����
);
//����ֵ��0����ɹ�������ʧ��
��һ��wVersionRequested������������ָ��׼�����ض�̬��İ汾�ţ�
���ֽ�Ϊ���ļ��ĸ��汾�����ֽ�ָ�����汾����MAKEWORD(X,Y)��
�������ɸò���������XΪ���ֽڣ�YΪ���ֽڡ�

���ڶ���lpWSAData Ϊָ��WSADATA�ṹ���ָ��

typedef struct WSAData {
	WORD  			wVersion; //����������ʹ�õ�socket�汾
	//����ʵ�ʷ��ص�socket�汾���ɸ��ݴ˲����жϷ��صİ汾���Ƿ���ȷ
	//����ͨ��HIBYTE��ȡ�ø��ֽڣ�LOBYTE��ȡ�õ��ֽڣ�
	WORD  			wHighVersion; //����Dll֧�ֵ���߰汾
	unsigned short  iMaxSockets;//һ�����������Դ򿪵��׽���������2.0�汾����Դ�ֵ��
	unsigned short  iMaxUdpDg; //һ�����̷��ͻ���յ�������ݱ�����
	char FAR* lpVendorInfo; //����ר����Ϣ��2.0�汾����Դ�ֵ��
	char    		szDescription[WSADESCRIPTION_LEN + 1]; //DLL��������Ϣ
	char    		szSystemStatus[WSASYS_STATUS_LEN + 1];//DLL��״̬��Ϣ
};
*/ 
int test01() {
	WSADATA data;
	int ret = WSAStartup(MAKEWORD(2, 2), &data);
	if (ret) {
		cout << "��ʼ���������" << endl;

		return ret;
	}
}

//2.�����������׽��� socket
/*
SOCKET socket(
int af,	//��ַ���ͣ�����IPv4��ַ��AF_INET����IPv6��ַ��AF_INET6
int type, //�׽������ͣ�����TCPЭ�飺SOCK_STREAM,UDPЭ�飺SOCK_DGRAM
int protocol //Э�����ͣ�һ����0���Զ�ѡ�񼴿�
);
//����ֵ��INVALID_SOCKETʧ�ܣ��ú�ʵ����Ϊ-1������ɹ�
*/ 
SOCKET test02() {
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		cout << "�����׽���ʧ��";
		WSACleanup();
	}
	return sock;
}

/*int bind(
SOCKET s, //������socket
sockaddr * name, //������ַ�Ͷ˿ڵĽṹ��
int namelen //sockaddr �ṹ����
);
//����ֵ������SOCKET_ERRORʧ�ܣ��ú걻����Ϊ-1������ɹ�������ֵΪ0
*/

//3.�󶨱���IP�Ͷ˿ڣ�bind
sockaddr_in test03(SOCKET sock,const char str_addr[],int host) {
	sockaddr_in addr;
	addr.sin_family = AF_INET; //��ַΪIPv4Э��
	addr.sin_port = htons(host); //�˿�Ϊ9999
	//addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); //�󶨵�������ip��ַ
	//��vs2013�汾��ʹ��inet_pton��ʹ��inet_addr�ᱨ��c4996,��Ҫ�޸���Ŀ����

	inet_pton(AF_INET, str_addr, &addr.sin_addr.s_addr);
	//inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);
	int ret = bind(sock, (sockaddr*)&addr, sizeof(addr)); //��
	if (ret == -1) {
		cout << "�󶨵�ַ�˿�ʧ��";
	}
	return addr;
}

//4.�����ͻ��ˣ�listen
/*int listen(
SOCKET s, //Ҫ������socket
int backlog //�ȴ����ӵ������г���
);
//����ֵ������SOCKET_ERRORʧ�ܣ��ú걻����Ϊ-1������ɹ�������ֵΪ0
*/
int test04(SOCKET sock) {
	int ret = listen(sock, 5);
	if (ret == -1) {
		cout << "�����׽���ʧ��";
		WSACleanup();
		return -1;
	}
	else {
		cout<<"��ʼ����" << endl;
	}
}

//5.�ȴ��ͻ������ӣ�accept
/*SOCKET accept(
SOCKET s, //���յ�socket
sockaddr* addr, //���յ��ͻ��˵ĵ�ַ��Ϣ
int * addrlen //��ַ��Ϣ����
);
//����ֵ������INVALID_SOCKETʧ�ܣ��ú궨��Ϊ-1������ɹ����ؿͻ��˵��׽��֣��ɽ��з��ͺͽ�����Ϣ
*/
SOCKET test05(SOCKET sock) {
	sockaddr addrCli;
	int len = sizeof(addrCli);
	SOCKET sockCli = accept(sock, &addrCli, &len);
	if (sockCli == -1) {
		cout << "���տͻ�������ʧ��";
		WSACleanup(); 
	}
	else {
		cout << "���տͻ������ӳɹ�";
	}
	return sockCli;
}

//6.������Ϣ��send
/*int send(
SOCKET s,
char * buf,//Ҫ���͵�����
int len, //���ݳ���
int flags //һ��Ϊ0�������������о�����ɾ���ں��е�����,��MSG_DONTROUTE:Ҫ����㲻Ҫ������·�ɳ�ȥ��MSG_OOB����־����Ӧ�ñ����ⷢ��
);
//����ֵ��-1�����SOCKET_ERROR����ʾ����ʧ�ܣ����򷵻ط��ͳɹ����ֽ���
*/

int test06(SOCKET sock, SOCKET sockCli) {
	char buf[0xFF] = "���Ƿ�����";
	int ret = send(sockCli, buf, strlen(buf)+1, 0);
	if (ret == -1) {
		cout << "������Ϣʧ��";
		WSACleanup();
		return -1;
	}
}

/*int recv(
SOCKET s, //�׽���
 char * buf, //�������ݵĻ�����
int len, //��������С
int flags //��־��һ����0������Ϣ������Ӧ�ó����У����ں��е�����ɾ����
��������MSG_PEEK,ֻȡ���ݣ������ں���ɾ�����ݣ�MSG_OOB�������������
);
//����ֵ��С�ڵ���0����ʾ��������0���ʾ���ճɹ������ݴ�С
*/

//7.������Ϣ��recv 
int test07(SOCKET sockCli, char  buf[]) {
	int ret = recv(sockCli, buf, 0xFF, 0);
	if (ret <= 0) {
		cout << "���ܿͻ�������ʧ��";
		WSACleanup();
		return -1;
	}
	else
	{
		cout << buf << endl;
	}
}

//8.�ر�socket��closesocket
/*
int closesocket(
SOCKET s //Ҫ�رյ�socket
);
*/
//9.������绷����WSACleanup ���κβ�����ֱ�ӵ��ü���
