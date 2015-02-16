#ifndef ___C_CLManeger_H___
#define ___C_CLManeger_H___

// クライアントのGUID
//static const GUID FrameWorkGUID_Client =
//{ 0xc39e4436, 0xff6e, 0x4209, { 0x94, 0x94, 0x64, 0x52, 0x90, 0x5d, 0x7a, 0x2 } };

#include "CL_IncludeHeader.h"

class C_CLManager
{
private: // Const
	const int m_maxDataSize;

private: // Variable

	SOCKET	m_myUDPSock;
	SOCKET	m_myTCPSock;

	clOperatingNormally clOperatingNormally; // マネージャーの正常稼働を意味する

	char buf[256];

	C_CommCheck	m_commCheck;

	Thread_Info m_recvThread;
	bool		runRecvThread;

private: // Function
	void InitClient(void);
	bool InitWinsock(WSADATA* m_wd, WORD requiredversion);
	bool CheckingVersion(WSADATA* m_wd, WORD requiredversion);
	bool InitMysock(void);
	bool FirstConnection();									// サーバーに対してTCPによる最初のコネクションを行う
	bool Connection(SOCKET* sock, sockaddr_in* addr);		// 指定したソケットにconnect()を行います
	bool CheckingPingTime();

	void StartRecv();										// アクセプト要スレッドを立ち上げる関数
	static UINT WINAPI  RecvThread(void* data);				// アクセプトをしているスレッド
	bool MakeSocket(SOCKET* sock, SOCKETTYPE type);			// 指定したタイプのソケットを生成する


public:
	C_CLManager(int dataMaxSize) : m_maxDataSize(dataMaxSize){ InitClient(); };
	~C_CLManager();

	bool	SendGameData(char* data, int dataSize);
	bool	GetNewData(char* buff, int buffSize);

};

#endif