#include "ParentProcessDlg.h"

ParentProcessDlg* ParentProcessDlg::ptr = NULL;

ParentProcessDlg::ParentProcessDlg(void)
{
	ptr = this;
}

ParentProcessDlg::~ParentProcessDlg(void)
{
	
}

void ParentProcessDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}



void ParentProcessDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(IDC_BUTTON1 == id)
	{
		CreateMutex(0, FALSE, TEXT("{EFCAC70D-D06F-4A38-AF91-602D30AA82B5}"));
		
		STARTUPINFO st = {sizeof(st)};
		PROCESS_INFORMATION pr;

		TCHAR filename[20];
		wsprintf(filename, TEXT("%s"), TEXT("CodingThread.exe"));
		
		if (!CreateProcess(NULL, filename, NULL, NULL, 0, 0, NULL, NULL, &st, &pr))
		{
			MessageBox(0,0,0,0);
			return;
		}
		CloseHandle(pr.hThread);
		CloseHandle(pr.hProcess);

		ZeroMemory(&st,sizeof(st));
		st.cb = sizeof(st);
		
		wsprintf(filename, TEXT("%s"), TEXT("DecodingThread.exe"));
		
		if (!CreateProcess(NULL, filename, NULL, NULL, 0, 0, NULL, NULL, &st, &pr))
		{
			MessageBox(0, 0, 0, 0);
			return;
		}
		CloseHandle(pr.hThread);
		CloseHandle(pr.hProcess);	
	}
}

BOOL CALLBACK ParentProcessDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}