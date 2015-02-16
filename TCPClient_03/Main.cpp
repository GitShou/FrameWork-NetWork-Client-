#include "C_CLManager.h"

//------------------------------------
// �}�N��
//------------------------------------
#define		NAME		"TCP_Server"
#define		TITLE		"TCP_Server"
#define		RECT_WIDTH	100
#define		RECT_HEIGHT	50

const char* SERVERIP = "127.0.0.1";

#define		USERNAME	"���X �Ȍ�"

//------------------------------------
// ���C�u����
//------------------------------------
#pragma	comment(lib, "ws2_32.lib")

//------------------------------------
// �v���g�^�C�v
//------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd,			// �E�C���h�E���b�Z�[�W�֐� 
	UINT message,
	WPARAM wParam,
	LPARAM lParam);

//------------------------------------
// �O���[�o���ϐ�
//------------------------------------
bool mainModule;
C_CLManager clManager(256);
//------------------------------------
// WinMain�֐�
//------------------------------------
int APIENTRY WinMain(HINSTANCE 	hInstance, 		// �A�v���P�[�V�����C���X�^���X�l
	HINSTANCE 	hPrevInstance,	// �Ӗ��Ȃ�
	LPSTR 		lpszArgs, 		// �N�����̈���������
	int 		nWinMode)		// �E�C���h�E�\�����[�h
{
	HWND			hwnd;						// �E�C���h�E�n���h��
	WNDCLASSEX		wcex;						// �E�C���h�E�N���X�\����

	// �E�C���h�E�N���X���̃Z�b�g
	wcex.hInstance = hInstance;			// �C���X�^���X�l�̃Z�b�g
	wcex.lpszClassName = NAME;					// �N���X��
	wcex.lpfnWndProc = (WNDPROC)WndProc;		// �E�C���h�E���b�Z�[�W�֐�
	wcex.style = 0;					// �E�C���h�E�X�^�C��
	wcex.cbSize = sizeof(WNDCLASSEX);	// �\���̂̃T�C�Y
	wcex.hIcon = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);	// ���[�W�A�C�R��
	wcex.hIconSm = LoadIcon((HINSTANCE)NULL, IDI_WINLOGO);		// �X���[���A�C�R��
	wcex.hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);		// �J�[�\���X�^�C��
	wcex.lpszMenuName = 0; 					// ���j���[�Ȃ�
	wcex.cbClsExtra = 0;					// �G�L�X�g���Ȃ�
	wcex.cbWndExtra = 0;
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);		// �w�i�F��

	if (!RegisterClassEx(&wcex)) return FALSE;	// �E�C���h�E�N���X�̓o�^

	hwnd = CreateWindow(NAME, 				// �E�C���h�E�N���X�̖��O
		TITLE, 							// �^�C�g��
		WS_CAPTION | WS_SYSMENU,		// �E�C���h�E�X�^�C��
		100, 100,						// X���W,Y���W
		640, 480,						// �E�C���h�E�T�C�Y
		HWND_DESKTOP, 					// �e�E�C���h�E�Ȃ�
		(HMENU)NULL, 					// ���j���[�Ȃ�
		hInstance, 						// �C���X�^���X�n���h��
		(LPVOID)NULL);					// �ǉ������Ȃ�

	if (!hwnd) return FALSE;


	while (1){ Sleep(100); }


	// �E�C���h�E��\������
	ShowWindow(hwnd, nWinMode);
	UpdateWindow(hwnd);

	return 0;
}
//------------------------------------
// �E�C���h�E�v���V�[�W��
//------------------------------------
LRESULT WINAPI WndProc(HWND hwnd, 				// �E�C���h�E�n���h���l
	UINT message,			// ���b�Z�[�W���ʎq
	WPARAM wParam,			// �t�я��P
	LPARAM lParam)			// �t�я��Q
{
	switch (message){
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			break;

		}
		break;

	case WM_DESTROY:
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}
