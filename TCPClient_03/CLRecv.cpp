#include "C_CLManager.h"

void C_CLManager::StartRecv(){
	this->runRecvThread = true;

	// アクセプト用のスレッドを起動
	this->m_recvThread.hd.TH = (HANDLE)_beginthreadex(NULL, 0, RecvThread, this, 0, &this->m_recvThread.hd.ID);

}

UINT WINAPI  C_CLManager::RecvThread(void* data){
	C_CLManager*	clManager = (C_CLManager*)data;

	while (clManager->runRecvThread){
		printf("クライアント受付中...\n\n");
		//clManager->m_commCheck.CheckCommError( recv(clManager->m_myUDPSock, ) );
	}
return 0;
}