#include "C_CLManager.h"

bool C_CLManager::FirstConnection(){

	const int SIZE_IPINPUT = 15;	// IP�A�h���X���͎��̕K�v�o�b�t�@�T�C�Y

	int sts;
	int ch;
	bool flg = true;

	char		svIP[SIZE_IPINPUT];
	sockaddr_in svAddr;


	LPHOSTENT	lphe;
	IN_ADDR		ip;

	// �T�[�o�[�������
	printf("�T�[�o�[�̐ݒ���J�n\n");
	printf("�T�[�o�[��IP�A�h���X����͂��Ă��������B");
	scanf_s("%s", svIP, SIZE_IPINPUT);

	// ���͂��ꂽ����ݒ肷��
	svAddr.sin_family = AF_INET;
	svAddr.sin_port = htons(SVRPORTNO);
	svAddr.sin_addr.s_addr = inet_addr(svIP);

	// �T�[�o�[�֐ڑ��v��
	printf("�T�[�o�[�֐ڑ��J�n...\n");

	if (this->Connection(&this->m_myTCPSock, &svAddr)){
		return true;
	}else{
		if (this->Connection(&this->m_myUDPSock, &svAddr))	return true;
	}

	printf("�T�[�o�[�Ƃ̐ڑ��m��\n");
	printf("TCP�y��UDP�\�P�b�g�̒ʐM������Œ肵�܂���\n");

	this->CheckingPingTime();

	//this->MakeRecvThread();
	return false;
}

bool C_CLManager::CheckingPingTime(){
	MsgData		work;
	sockaddr_in	fromAddr;
	int			addrLen = sizeof(sockaddr);

	printf("�T�[�o�[�Ƃ̒ʐM�m�F���s���܂��B\n");

	// ������UDP�\�P�b�g�ɃT�[�o�[����f�[�^�������Ă���̂�ҋ@
	recvfrom(this->m_myUDPSock, work.data, sizeof(MsgData), 0, (struct sockaddr *)&fromAddr, &addrLen);
	Connection(&m_myUDPSock, &fromAddr);  // ��M�������̏�������UDP�\�P�b�g�̒ʐM������T�[�o�[�ƌŒ�

	// ��M�����f�[�^�ɃT�[�o�[����̃����_���l���܂܂�Ă���̂ŁA�K��̌v�Z���@�ŕϊ����s���ԐM����i�v�Z���̓}�N�����g���Ē�`���Ă���j
	work.Msg.Body0.rndNo = MAKE_ATTESTATION_NO; // �K��̌v�Z���@�Œl��ύX
	send(this->m_myUDPSock, work.data, sizeof(MsgData), 0);	// �ύX�����f�[�^�𑗐M

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
