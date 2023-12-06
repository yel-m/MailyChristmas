
// MailyChristmasDlg.h: 헤더 파일
//

#pragma once


// CMailyChristmasDlg 대화 상자
class CMailyChristmasDlg : public CDialogEx
{
// 생성입니다.
public:
	CMailyChristmasDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAILYCHRISTMAS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
private:
	static void	_parseEmailAddr(LPCTSTR lpszSrc, CString& name, CString& address);
	static void _splitAddr(LPCTSTR lpszSrc, CStringArray& values);
	void _changeSettingforWellKnownServer();
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnChangeEditFrom();
	CString m_from;
	CString m_server;
	CString m_user;
	afx_msg void OnChangeEditServer();
	afx_msg void OnClickedButtonAdd();
	afx_msg void OnBnClickedOk();
	CString m_to;
};
