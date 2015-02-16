#ifndef ___CLSTRUCT_H___
#define	___CLSTRUCT_H___

/***** スレッド用構造体 *****/
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