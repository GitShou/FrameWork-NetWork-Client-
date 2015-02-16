#ifndef ___FRAMEWORKMESSAGE_H___
#define ___FRAMEWORKMESSAGE_H___

// ���b�Z�[�W�w�b�_�[
struct	_MSGHEADER{
	short	type;	// ���b�Z�[�W�^�C�v 0:����@1:�ʏ�@2:�I��
};

// ���b�Z�[�W�{�f�B�i���b�Z�[�W�^�C�v�O�j
struct	_MSGBODY0{
	int rndNo;
};

// ���b�Z�[�W�{�f�B�i���b�Z�[�W�^�C�v�P�j
struct	_MSGBODY1{
	unsigned int sequenceNo;
};


// ���b�Z�[�W�̍\��
struct	_MESSAGE{
	struct	_MSGHEADER	Header;
	union{
		struct	_MSGBODY0	Body0;		// ����
		struct	_MSGBODY1	Body1;		// �ʏ�

	};
};

// ����M���b�Z�[�W�\����
struct	MsgData{
	union{
		struct	_MESSAGE  Msg;
		char	data[sizeof(_MESSAGE)];
	};
};

#endif