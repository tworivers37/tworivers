#include<Windows.h>	

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClassName=TEXT("Hello");

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdParam,int nCmdShow){
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;

	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=WndProc;
	WndClass.lpszClassName=lpszClassName;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW|CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClassName,lpszClassName,
					  WS_OVERLAPPEDWINDOW,
					  CW_USEDEFAULT,
					  CW_USEDEFAULT,
					  CW_USEDEFAULT,
					  CW_USEDEFAULT,
					  NULL,
					  (HMENU)NULL,
					  hInstance,
					  NULL);
	ShowWindow(hWnd,nCmdShow);
	while(GetMessage(&Message,NULL,0,0)){
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	TCHAR *str;
	switch(iMessage){
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_LBUTTONDOWN:
			MessageBox(hWnd,TEXT("Message Box Test"),TEXT("Message Box"),MB_ABORTRETRYIGNORE);
			//MB_OK : OK 버튼
			//MB_OKCANCEL : OK,Cancel
			//MB_RETRYCANCEL : Retry,Cancel
			//MB_YESNO : Yes,No
			//MB_YESNOCANCEL : Yes,No,Cancel
			//MB_ABORTRETRYIGNORE : Abort,Retry,Ignore
			return 0;
		case WM_RBUTTONDOWN:
			if(MessageBox(hWnd,TEXT("YES OR NO"),TEXT("?"),MB_YESNO)==IDYES){
				//IDABORT : abort
				//IDCANCEL : cancel
				//IDIGNORE : ignore
				//IDNO : no
				//IDOK : ok
				//IDRETRY : retry
				//IDYES : yes
				hdc=GetDC(hWnd);
				str=TEXT("YES good");
				TextOut(hdc,100,100,str,lstrlen(str));
				ReleaseDC(hWnd,hdc);
			}
			else{
				hdc=GetDC(hWnd);
				str=TEXT("No bad");
				TextOut(hdc,100,100,str,lstrlen(str));
				ReleaseDC(hWnd,hdc);
			}
			return 0;
	}
	return DefWindowProc(hWnd,iMessage,wParam,lParam);
}
