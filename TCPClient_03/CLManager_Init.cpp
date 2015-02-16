#include "C_CLManager.h"

void C_CLManager::InitClient(void){
	WSADATA		m_wd;								// �v�r�`�r�s�`�q�s�t�o�p
	WORD		requiredversion = MAKEWORD(2, 2);	// ���̃v���O�������v������o�[�W����;

	this->clOperatingNormally = clFalse;

	// ���\���p�R���\�[���E�C���h�E�\��
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
	printf("�\�P�b�g�������J�n\n");

	// Windows �̏ꍇ
	sts = WSAStartup(requiredversion, m_wd);
	if (this->m_commCheck.CheckCommError(sts))
	{
		printf("WINSOCK���������s\n");
		_getch();
		//�R���\�[���폜
		FreeConsole();
		return true;
	}
	return false;
}
bool C_CLManager::CheckingVersion(WSADATA* m_wd, WORD requiredversion){
	printf("�o�[�W�����`�F�b�N\n");
	// �o�[�W�����`�F�b�N
	if (m_wd->wVersion != requiredversion)
	{
		printf("�o�[�W�����G���[");
		_getch();
		//�R���\�[���폜
		FreeConsole();
		return true;	// �����ŃR���X�g���N�^�������I��
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

	// TCP�ʐM�p�̃\�P�b�g�𐶐�����
	if (this->MakeSocket(&this->m_myTCPSock, SOCKETTYPE::TCP)){
		printf("TCP�\�P�b�g�������s");
	}
	// UDP�ʐM�p�̃\�P�b�g�𐶐�����
	if (this->MakeSocket(&this->m_myUDPSock, SOCKETTYPE::UDP)){
		printf("UDP�\�P�b�g�������s");
	}

	// �}���`�L���X�g�p�̏��ݒ�
	mreq.imr_multiaddr.S_un.S_addr = inet_addr(MULTICAST_ADDR);
	mreq.imr_interface.S_un.S_addr = htonl(INADDR_ANY);

	// ���j�L���X�g�p�̏��ݒ�
	memset(&myAddr, 0, sizeof(sockaddr_in));
	myAddr.sin_port = htons(SVRPORTNO);
	myAddr.sin_family = AF_INET;
	myAddr.sin_addr.s_addr = htonl(INADDR_ANY);


	// �}���`�L���X�g���\�P�b�g�ɐݒ肷��
	sts = setsockopt(this->m_myUDPSock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(ip_mreq));
	if (this->m_commCheck.CheckCommError(sts)){
		printf("�}���`�L���X�g�ݒ莸�s(UDP)\n");
		_getch();
		FreeConsole();	//�R���\�[���폜
		return true;
	}

	printf("�}���`�L���X�g��ݒ肵�܂���%c", MULTICAST_ADDR);

	return false;
}


C_CLManager::~C_CLManager(void){

	// �\�P�b�g�I��
	closesocket(this->m_myTCPSock);
	// �v�h�m�r�n�b�j�̌㏈��
	WSACleanup();

}



bool C_CLManager::MakeSocket(SOCKET* sock, SOCKETTYPE type){

	switch (type){
	case SOCKETTYPE::TCP:
		// UDP�ʐM�p�̃\�P�b�g�𐶐�����
		*sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (this->m_commCheck.CheckCommError(*sock)){
			printf("UDP�\�P�b�g�������s\n");
			_getch();
			//�R���\�[���폜
			FreeConsole();
			return true;
		}
		break;
	case SOCKETTYPE::UDP:
		// UDP�ʐM�p�̃\�P�b�g�𐶐�����
		*sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (this->m_commCheck.CheckCommError(*sock)){
			printf("UDP�\�P�b�g�������s\n");
			_getch();
			//�R���\�[���폜
			FreeConsole();
			return true;
		}
		break;
	}
	return false;
}
	