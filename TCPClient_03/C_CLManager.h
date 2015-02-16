#ifndef ___C_CLManeger_H___
#define ___C_CLManeger_H___

// �N���C�A���g��GUID
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

	clOperatingNormally clOperatingNormally; // �}�l�[�W���[�̐���ғ����Ӗ�����

	char buf[256];

	C_CommCheck	m_commCheck;

	Thread_Info m_recvThread;
	bool		runRecvThread;

private: // Function
	void InitClient(void);
	bool InitWinsock(WSADATA* m_wd, WORD requiredversion);
	bool CheckingVersion(WSADATA* m_wd, WORD requiredversion);
	bool InitMysock(void);
	bool FirstConnection();									// �T�[�o�[�ɑ΂���TCP�ɂ��ŏ��̃R�l�N�V�������s��
	bool Connection(SOCKET* sock, sockaddr_in* addr);		// �w�肵���\�P�b�g��connect()���s���܂�
	bool CheckingPingTime();

	void StartRecv();										// �A�N�Z�v�g�v�X���b�h�𗧂��グ��֐�
	static UINT WINAPI  RecvThread(void* data);				// �A�N�Z�v�g�����Ă���X���b�h
	bool MakeSocket(SOCKET* sock, SOCKETTYPE type);			// �w�肵���^�C�v�̃\�P�b�g�𐶐�����


public:
	C_CLManager(int dataMaxSize) : m_maxDataSize(dataMaxSize){ InitClient(); };
	~C_CLManager();

	bool	SendGameData(char* data, int dataSize);
	bool	GetNewData(char* buff, int buffSize);

};

#endif