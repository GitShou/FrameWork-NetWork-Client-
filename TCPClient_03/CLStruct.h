#ifndef ___CLSTRUCT_H___
#define	___CLSTRUCT_H___

/***** �X���b�h�p�\���� *****/
typedef struct{
	HANDLE	TH;
	UINT	ID;
}Thread_Handle;
typedef struct{
	void* p_Server;
	int target;
}Thread_Data;

typedef struct{
	Thread_Handle	hd;
	Thread_Data		thData;
}Thread_Info;
/***************************/

#endif