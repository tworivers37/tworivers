#include<Windows.h>
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM); // 사용자와 시스템이 보내오는 메시지를 처리함.중요.
HINSTANCE g_hInst; //WinMain 함수의 hInstance 값을 전역변수에 저장.수시로 사용하기때문.
LPCTSTR lpszClass=TEXT("Hello");  // 윈도우 클래스를 정의하는데 사용.

//hInstance : 프로그램 인스턴스 핸들
//hPrevInstance : 바로 앞에 실행된 프로그램의 인스턴스 핸들. 없는 경우 NULL.16비트 호환을 위한 인수.찌꺼기
//lpszCmdParam : 명령행으로 입력된 프로그램 인수. argv 에 해당.대게 실행 직후 열 파일의 경로 전달.
//nCmdShow : 프로그램이 실행될 형태.최소화,보통 모양등이 전달.
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdParam,int nCmdShow){

	HWND hWnd;
	MSG Message; //메시지에 대한 정보.
	//hwnd : 메시지를 받을 윈도우 핸들
	//message : 어떤 종류의 메시지인가를 나타냄.
	//wParam : 전달된 메시지에 대한 부가적인 정보.
	//lParam : 전달된 메시지에 대한 부가적인 정보.
	//time : 메시지가 발생한 시간.
	//pt : 메시지가 발생했을 때의 마우스 위치.
	WNDCLASS WndClass;
	g_hInst=hInstance;

	WndClass.cbClsExtra=0; //예약 영역.사용하지 않을 때 0으로 지정.
	WndClass.cbWndExtra=0; //예약 영역.사용하지 않을 때 0으로 지정.
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);//윈도우 배경 색상 지정.윈도우의 배경 색상을 채색할 브러시를 지정.
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW); //마우스 커서 지정.
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION); //아이콘 지정.
	WndClass.hInstance=hInstance; //윈도우 클래스 등록.
	WndClass.lpfnWndProc=WndProc;// 윈도우 메시지 처리 함수를 지정.
	WndClass.lpszClassName=lpszClass;// 윈도우 클래스의 이름을 문자열로 지정.
	WndClass.lpszMenuName=NULL; //메뉴 지정.메뉴는 프로그램 코드에서 실행 중 만드는게 아니라 리소스 에디터에 의해 별도로 만들어져 링크시 합쳐짐.
	WndClass.style=CS_HREDRAW|CS_VREDRAW; // 윈도우 스타일 지정.CS_HREDRAW,CS_VREDRAW 옵션으로 윈도우의 크기가 변할 경우 윈도우를 다시 그림.
	RegisterClass(&WndClass); //윈도우 클래스 등록.

	//윈도우 생성.
	//윈도우 핸들 리턴.
	//메모리상에 윈도우에 대한 정보를 만듦.화면 출력x.
	//lpszClassName : 생성하고자 하는 윈도우의 클래스를 지정하는 문자열.
	//lpszWindowName : 윈도우의 타이틀 바에 나타날 문자열.
	//dwStyle : 윈도우의 형태 지정.
	//X,Y,nWidth,nHeight : 윈도우의 크기와 위치를 지정하며 픽셀 단위로 사용.CW_USEDEFAULT 를 사용하면 운영체제가 화면 크기에 맞게 크기와 위치 지정.
	//hWndParent : 부모 윈도우가 있을 경우 부모 윈도우의 핸들을 지정.없을경우 NULL.NULL이면 데스크탑이 부모가 되어 바탕화면 어디든 이동가능.
	//hmenu : 윈도우에서 사용할 메뉴의 핸들을 지정.윈도우 클래스에서 지정한 메뉴는 그 윈도우 클래스 기반으로하는 모든 윈도우에서 공통적으로 사용되는
	//반면 이 인자로 지정된 메뉴는 현재 CreateWindow로 만들어지는 윈도우에만 사용.NULL로 지정하면 윈도우 클래스에서 지정한 것으로 사용.
	//hinst : 윈도우를 만드는 주체.프로그램의 핸들을 지정.
	//lpvParam : CREATESTRUCT라는 구조체의 주소. 여러 개의 윈도우를 만들 때 각 윈도우에 고유의 파라미터를 전달하는 목적.
	hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow); //메모리에 만들어진 윈도우를 화면에 출력.nCmdShow는 윈도우를 화면에 출력하는 방법 지정.
	
	//메시지 루프.메시지를 처리하는 부분.
	//무한 반복.
	//윈도우의 멀티태스킹을 지원하는 역할.
	while(GetMessage(&Message,NULL,0,0)){ //메시지 큐에서 메시지를 읽음.읽은 메시지는 MSG 구조체에 저장.WM_QUIT 경우 False 리턴하여 루프 종료.
		TranslateMessage(&Message); //키보드 입력 메시지를 가공하여 프로그램에서 쉽게 쓸 수 있도록 함.
		DispatchMessage(&Message); //메시지를 윈도우 메시지 처리 함수(WndProc)으로 전달.
	}
	return (int)Message.wParam; //WM_QUIT 로 부터 전달된 탈출코드
}
//운영체제에 의해 호출.
//hWnd : 핸들
//iMessage : 어떤 종류의 메시지.어떤 변화가 발생했는가.
//wParam,lParam : iMessgae의 부가적인 정보.
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam){
	switch(iMessage){
		case WM_DESTROY:
			PostQuitMessage(0);//WM_QUIT 메시지를 보냄.GetMessage 함수 리턴 값이 False 되어 반복문을 탈출 하여 WinMain 종료.
			return 0; //무사 처리 되었으면 0을 리턴.
	}
	return (DefWindowProc(hWnd,iMessage,wParam,lParam));//WndProc 에서 처리하지 않은 나머지 메시지에 대한 처리를 함.
														//ex) 시스템 메뉴를 더블클릭하면 프로그램이 종료 되는데, 이는 별도로 처리하지 않고 DefWindowProc 함수에서 처리.
														//그래서 윈도우의 이동이나 크기 변경 등의 처리는 DefWindowProc 으로 넘기기만 하면됨.
}