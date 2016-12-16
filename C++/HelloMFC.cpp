#include<afxwin.h>

class CHelloApp:public CWinApp{
	public:
		virtual BOOL InitInstance();
};

CHelloApp theApp;

BOOL CHelloApp::InitInstance(){
	m_pMainWnd=new CMainFrame;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	return true;
}


class CMainFrame:public CFrameWnd{
public:
	CMainFrame();
protected:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags,CPoint point);
	DECLARE_MESSAGE_MAP()
};


CMainFrame::CMainFrame(){
	Create(NULL,"Hello MFC");
}

void CMainFrame::OnPaint(){
	char *msg="Hello MFC~";
	CPaintDC dc(this);
	dc.TextOut(100,100,msg,lstrlen(msg));
}

void CMainFrame::OnLButtonDown(UINT nFlags,CPoint point){
	MessageBox("Mouse");
}

BEGIN_MESSAGE_MAP(CMainFrame,CFrameWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()
