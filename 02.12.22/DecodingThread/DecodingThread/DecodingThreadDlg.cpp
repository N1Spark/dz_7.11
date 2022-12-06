#include "DecodingThreadDlg.h"

DecodingThreadDlg* DecodingThreadDlg::ptr = NULL;

DecodingThreadDlg::DecodingThreadDlg(void)
{
	ptr = this;
}

DecodingThreadDlg::~DecodingThreadDlg(void)
{
	
}

void DecodingThreadDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

DWORD WINAPI Decoding_Thread(LPVOID lp)
{
	DecodingThreadDlg *ptr = (DecodingThreadDlg *)lp;
	char buf[4096];

	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, false, TEXT("{EFCAC70D-D06F-4A38-AF91-602D30AA82B5}"));
	
	DWORD dwAnswer = WaitForSingleObject(hMutex, INFINITE);
	if(dwAnswer == WAIT_OBJECT_0)
	{
		std::ifstream in(TEXT("array.txt"));
		if (!in.is_open())
		{
			MessageBox(0, TEXT("Error"), TEXT("Error"), MB_OK);
			return 1;
		}
		int B[100];
		int sum = 0;
		for (int i = 0; i < 100; i++)
		{
			in >> B[i];
			sum += B[i];
		}
		in.close();
		MessageBox(0, TEXT("Поток прочитал информацию из файла"), TEXT(""), MB_OK);
		TCHAR str[30];
		wsprintf(str, TEXT("Сумма чисел равна %d"), sum);
		MessageBox(0, str, TEXT(""), MB_OK);
		ReleaseMutex(hMutex);
	}
	return 0;
}

BOOL DecodingThreadDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	hDialog = hwnd;
	CreateThread(NULL, 0, Decoding_Thread, this, 0, NULL); 
	return TRUE;
}

BOOL CALLBACK DecodingThreadDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
	}
	return FALSE;
}