#include "C_CLManager.h"

bool C_CLManager::FirstConnection(){

	const int SIZE_IPINPUT = 15;	// IPアドレス入力時の必要バッファサイズ

	int sts;
	int ch;
	bool flg = true;

	char		svIP[SIZE_IPINPUT];
	sockaddr_in svAddr;


	LPHOSTENT	lphe;
	IN_ADDR		ip;

	// サーバー情報を入力
	printf("サーバーの設定を開始\n");
	printf("サーバーのIPアドレスを入力してください。");
	scanf_s("%s", svIP, SIZE_IPINPUT);

	// 入力された情報を設定する
	svAddr.sin_family = AF_INET;
	svAddr.sin_port = htons(SVRPORTNO);
	svAddr.sin_addr.s_addr = inet_addr(svIP);

	// サーバーへ接続要求
	printf("サーバーへ接続開始...\n");

	if (this->Connection(&this->m_myTCPSock, &svAddr)){
		return true;
	}else{
		if (this->Connection(&this->m_myUDPSock, &svAddr))	return true;
	}

	printf("サーバーとの接続確立\n");
	printf("TCP及びUDPソケットの通信相手を固定しました\n");

	this->CheckingPingTime();

	//this->MakeRecvThread();
	return false;
}

bool C_CLManager::CheckingPingTime(){
	MsgData		work;
	sockaddr_in	fromAddr;
	int			addrLen = sizeof(sockaddr);

	printf("サーバーとの通信確認を行います。\n");

	// 自分のUDPソケットにサーバーからデータが送られてくるのを待機
	recvfrom(this->m_myUDPSock, work.data, sizeof(MsgData), 0, (struct sockaddr *)&fromAddr, &addrLen);
	Connection(&m_myUDPSock, &fromAddr);  // 受信した時の情報を元にUDPソケットの通信相手をサーバーと固定

	// 受信したデータにサーバーからのランダム値が含まれているので、規定の計算方法で変換を行い返信する（計算式はマクロを使って定義している）
	work.Msg.Body0.rndNo = MAKE_ATTESTATION_NO; // 規定の計算方法で値を変更
	send(this->m_myUDPSock, work.data, sizeof(MsgData), 0);	// 変更したデータを送信

	return false;
}

bool C_CLManager::Connection(SOCKET* sock, sockaddr_in* addr){
	int sts;
	int	addrLen = sizeof(sockaddr);

	sts = connect(*sock, (struct sockaddr *) addr, addrLen);
	if (this->m_commCheck.CheckCommError(sts)){
		return true;
	}
	return false;
}

bool	C_CLManager::SendGameData(char* data, int dataSize){
	return false;

}

bool	C_CLManager::GetNewData(char* buff, int buffSize){
	return false;
}
