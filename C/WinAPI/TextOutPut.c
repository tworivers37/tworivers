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
	HDC hDC;
	//출력에 관한 함수의 첫 번째 인자는 무조건 DC값이다.
	PAINTSTRUCT ps;
	TCHAR *str;
	RECT rt={100,100,100,100};
	switch(iMessage){
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_LBUTTONDOWN:	// 왼쪽 마우스 버튼 클릭 시
								// 텍스트 출력.
								// DC를 얻는 방법1
								// GetDC 함수 사용.
								// 사용 후 ReleaseDC로 해제.
			hDC=GetDC(hWnd);
			//TextOut(hDC,100,100,TEXT("test TEXT"),10);
			str=TEXT("test TEXT");
			TextOut(hDC,100,100,str,lstrlen(str));
			ReleaseDC(hWnd,hDC);
			return 0;
		case WM_PAINT:	//윈도우가 가려졌다가 다시 나타날때 다시 그려줘야함.
						//가려졌을 때 WM_PAINT 메시지 발생.
						//DC를 얻는 방법2
						//BeginPaint 함수 사용.
						//BeginPaint 함수는 WM_PAINT 메시지 처리 루틴 내에서만 사용가능.
						//다른 곳에선 사용 불가.
			hDC=BeginPaint(hWnd,&ps);
			//TextOut(hDC,100,100,TEXT("Paint"),5);
			str=TEXT("Paint");
			TextOut(hDC,100,100,str,lstrlen(str));

			/*str=TEXT("DrawText"
			"1234567890"
			"adsfbdasdfasfdsf");
			
			DrawText(hDC,str,-1,&rt,DT_CENTER|DT_WORDBREAK);*/
			//길이가 -1 이면 문자열 끝까지 출력.

			EndPaint(hWnd,&ps);
			return 0;
	}
	return DefWindowProc(hWnd,iMessage,wParam,lParam);
}
