#include "C_CLManager.h"

void C_CLManager::InitClient(void){
	WSADATA		m_wd;								// ＷＳＡＳＴＡＲＴＵＰ用
	WORD		requiredversion = MAKEWORD(2, 2);	// このプログラムが要求するバージョン;

	this->clOperatingNormally = clFalse;

	// 情報表示用コンソールウインドウ表示
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONIN$", "r", stdin);

	if (this->InitWinsock(&m_wd, requiredversion)){
		exit(1);
	}
	if (this->CheckingVersion(&m_wd, requiredversion)){
		exit(1);
	}
	if (this->InitMysock()){
		exit(1);
	}
	if (this->FirstConnection()){
		exit(1);
	}

	this->clOperatingNormally = clTrue;
}

bool C_CLManager::InitWinsock(WSADATA* m_wd, WORD requiredversion){
	int sts;
	printf("ソケット初期化開始\n");

	// Windows の場合
	sts = WSAStartup(requiredversion, m_wd);
	if (this->m_commCheck.CheckCommError(sts))
	{
		printf("WINSOCK初期化失敗\n");
		_getch();
		//コンソール削除
		FreeConsole();
		return true;
	}
	return false;
}
bool C_CLManager::CheckingVersion(WSADATA* m_wd, WORD requiredversion){
	printf("バージョンチェック\n");
	// バージョンチェック
	if (m_wd->wVersion != requiredversion)
	{
		printf("バージョンエラー");
		_getch();
		//コンソール削除
		FreeConsole();
		return true;	// ここでコンストラクタを強制終了
	}
	return false;
}

bool C_CLManager::InitMysock(){
	int			sts;

	bool		flg = true;

	sockaddr_in myAddr;
	int			myAddrLen = sizeof(sockaddr);
	int			myPortNo;
	ip_mreq		mreq;

	// TCP通信用のソケットを生成する
	if (this->MakeSocket(&this->m_myTCPSock, SOCKETTYPE::TCP)){
		printf("TCPソケット生成失敗");
	}
	// UDP通信用のソケットを生成する
	if (this->MakeSocket(&this->m_myUDPSock, SOCKETTYPE::UDP)){
		printf("UDPソケット生成失敗");
	}

	// マルチキャスト用の情報設定
	mreq.imr_multiaddr.S_un.S_addr = inet_addr(MULTICAST_ADDR);
	mreq.imr_interface.S_un.S_addr = htonl(INADDR_ANY);

	// ユニキャスト用の情報設定
	memset(&myAddr, 0, sizeof(sockaddr_in));
	myAddr.sin_port = htons(SVRPORTNO);
	myAddr.sin_family = AF_INET;
	myAddr.sin_addr.s_addr = htonl(INADDR_ANY);


	// マルチキャストをソケットに設定する
	sts = setsockopt(this->m_myUDPSock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(ip_mreq));
	if (this->m_commCheck.CheckCommError(sts)){
		printf("マルチキャスト設定失敗(UDP)\n");
		_getch();
		FreeConsole();	//コンソール削除
		return true;
	}

	printf("マルチキャストを設定しました%c", MULTICAST_ADDR);

	return false;
}


C_CLManager::~C_CLManager(void){

	// ソケット終了
	closesocket(this->m_myTCPSock);
	// ＷＩＮＳＯＣＫの後処理
	WSACleanup();

}



bool C_CLManager::MakeSocket(SOCKET* sock, SOCKETTYPE type){

	switch (type){
	case SOCKETTYPE::TCP:
		// UDP通信用のソケットを生成する
		*sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (this->m_commCheck.CheckCommError(*sock)){
			printf("UDPソケット生成失敗\n");
			_getch();
			//コンソール削除
			FreeConsole();
			return true;
		}
		break;
	case SOCKETTYPE::UDP:
		// UDP通信用のソケットを生成する
		*sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (this->m_commCheck.CheckCommError(*sock)){
			printf("UDPソケット生成失敗\n");
			_getch();
			//コンソール削除
			FreeConsole();
			return true;
		}
		break;
	}
	return false;
}
	