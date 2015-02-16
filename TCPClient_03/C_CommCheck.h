#ifndef ___C_Comm_Check_H___
#define ___C_Comm_Check_H___

#include <WinSock2.h>
#include <stdio.h>
#include <process.h>

struct errdata_t{
	int	errNo;
	char* errMsg;
};

class C_CommCheck
{
private:

	void errcom(int errcode);

	struct errdata_t errData[95];


public:

	C_CommCheck();
		
	bool CheckCommError(int sts);		// SOCKET_ERROR�`�F�b�N
	bool CheckCommError(SOCKET sock);	// INVALID_SOCKET�`�F�b�N
	bool CheckCommError( int sts, int target );	// �^�C���A�E�g�`�F�b�N
	void MakeTimeOutThread(int target);
	UINT WINAPI C_CommCheck::CheckingActive( void* data );
};

#endif