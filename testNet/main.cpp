#include"testClient.cpp"
#include"testServer.cpp"
#include<windows.h>
//服务器
void testServer() {
	//1.网络环境初始化
	int ret = test01(); 
	char buf[0xFF];

	//2.创建服务器套接字 socket
	SOCKET sock = test02();

	//3.绑定本机IP和端口：bind
	sockaddr_in addr = test03(sock,"127.0.0.1",9999);

	//4.监听客户端：listen
	ret = test04(sock); 
	int i = 0;
	while (true && i!=1)
	{ 
		//5.等待客户端连接：accept
		SOCKET sockCli = test05(sock);

		//6.发送消息：send
		test06(sock, sockCli);

		//7.接收消息：recv 
		ret = test07(sockCli, buf);
		cout<< ++i <<endl;
	}
	cout << "close" << endl;
	//8.关闭socket：closesocket
	//closesocket(sock);
	//closesocket(sockCli);

	//9.清除网络环境：WSACleanup
	//WSACleanup();
	system("pause");
}

//客户端
void testClient() {
	//1.初始化网络环境：WSAStartup 
	int ret = test01();
	char buf[0xFF];//255


	//cout << strlen(buf) << endl;//544
	//cout << sizeof(buf) << endl;//255
	//2.创建套接字：socket
	SOCKET sock = test02();
	sockaddr_in addr = test03(sock,"127.0.0.1", 9998);

	//3.连接服务器：connect
	sockaddr_in Saddr;//服务器信息
	Saddr.sin_family = AF_INET; //地址为IPv4协议
	Saddr.sin_port = htons(9999); //端口为9999
	inet_pton(AF_INET, "127.0.0.1", &Saddr.sin_addr.s_addr);
	ret = testConn(sock,Saddr);

	//5.接收数据：recv
	 ret=testRecv(sock, buf);
	//4.发送数据：send
	ret = testSend(sock, buf,ret);

	//6.清理网络环境：WSACleanup
	//WSACleanup();

}

int main() {
	testClient();
	//testServer();
}