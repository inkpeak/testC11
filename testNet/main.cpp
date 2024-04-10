#include"testClient.cpp"
#include"testServer.cpp"
#include<windows.h>
//������
void testServer() {
	//1.���绷����ʼ��
	int ret = test01(); 
	char buf[0xFF];

	//2.�����������׽��� socket
	SOCKET sock = test02();

	//3.�󶨱���IP�Ͷ˿ڣ�bind
	sockaddr_in addr = test03(sock,"127.0.0.1",9999);

	//4.�����ͻ��ˣ�listen
	ret = test04(sock); 
	int i = 0;
	while (true && i!=1)
	{ 
		//5.�ȴ��ͻ������ӣ�accept
		SOCKET sockCli = test05(sock);

		//6.������Ϣ��send
		test06(sock, sockCli);

		//7.������Ϣ��recv 
		ret = test07(sockCli, buf);
		cout<< ++i <<endl;
	}
	cout << "close" << endl;
	//8.�ر�socket��closesocket
	//closesocket(sock);
	//closesocket(sockCli);

	//9.������绷����WSACleanup
	//WSACleanup();
	system("pause");
}

//�ͻ���
void testClient() {
	//1.��ʼ�����绷����WSAStartup 
	int ret = test01();
	char buf[0xFF];//255


	//cout << strlen(buf) << endl;//544
	//cout << sizeof(buf) << endl;//255
	//2.�����׽��֣�socket
	SOCKET sock = test02();
	sockaddr_in addr = test03(sock,"127.0.0.1", 9998);

	//3.���ӷ�������connect
	sockaddr_in Saddr;//��������Ϣ
	Saddr.sin_family = AF_INET; //��ַΪIPv4Э��
	Saddr.sin_port = htons(9999); //�˿�Ϊ9999
	inet_pton(AF_INET, "127.0.0.1", &Saddr.sin_addr.s_addr);
	ret = testConn(sock,Saddr);

	//5.�������ݣ�recv
	 ret=testRecv(sock, buf);
	//4.�������ݣ�send
	ret = testSend(sock, buf,ret);

	//6.�������绷����WSACleanup
	//WSACleanup();

}

int main() {
	testClient();
	//testServer();
}