
// MailyChristmasDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MailyChristmas.h"
#include "MailyChristmasDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMailyChristmasDlg 대화 상자



CMailyChristmasDlg::CMailyChristmasDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAILYCHRISTMAS_DIALOG, pParent)
	, m_from(_T(""))
	, m_server(_T(""))
	, m_user(_T(""))
	, m_to(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMailyChristmasDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FROM, m_from);
	DDX_Text(pDX, IDC_EDIT_USER, m_user);
	DDX_Text(pDX, IDC_EDIT_TO, m_to);
}

BEGIN_MESSAGE_MAP(CMailyChristmasDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT_FROM, &CMailyChristmasDlg::OnChangeEditFrom)
	ON_EN_CHANGE(IDC_EDIT_SERVER, &CMailyChristmasDlg::OnChangeEditServer)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CMailyChristmasDlg::OnClickedButtonAdd)
	ON_BN_CLICKED(IDOK, &CMailyChristmasDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMailyChristmasDlg 메시지 처리기

BOOL CMailyChristmasDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMailyChristmasDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMailyChristmasDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMailyChristmasDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMailyChristmasDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMailyChristmasDlg::OnChangeEditFrom()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CString name, addr, domain;
	_parseEmailAddr(m_from, name, addr);

	int pos = addr.Find(_T('@'));
	if (pos != -1)
		domain = addr.Mid(pos + 1);

	if (domain.CompareNoCase(_T("hotmail.com")) == 0)
	{
		m_server = _T("smtp.office365.com");
		m_user = addr;
	}
	else if (domain.CompareNoCase(_T("gmail.com")) == 0)
	{
		m_server = _T("smtp.gmail.com");
		m_user = addr;
	}
	else if (domain.CompareNoCase(_T("yahoo.com")) == 0)
	{
		m_server = _T("smtp.mail.yahoo.com");
		m_user = addr;
	}
	else if (domain.CompareNoCase(_T("aol.com")) == 0)
	{
		m_server = _T("smtp.aol.com");
		m_user = addr;
	}
	else
	{
		m_user = addr;
	}

	UpdateData(FALSE);
	_changeSettingforWellKnownServer();
}

void CMailyChristmasDlg::_parseEmailAddr(LPCTSTR lpszSrc, CString& name, CString& addr)
{
	name = _T("");
	addr = _T("");

	if (lpszSrc == NULL)
		return;

	LPCTSTR pszBuf = _tcschr(lpszSrc, _T('<'));
	if (pszBuf == NULL)
	{
		addr = lpszSrc;
	}
	else
	{
		name.Append(lpszSrc, pszBuf - lpszSrc);
		addr.Append(pszBuf);
	}

	name = name.Trim(_T(" \"<>"));
	addr = addr.Trim(_T(" \"<>"));
}

void CMailyChristmasDlg::_changeSettingforWellKnownServer()
{
	UpdateData(TRUE);

	if (m_server.CompareNoCase(_T("smtp.gmail.com")) == 0 ||
		m_server.CompareNoCase(_T("smtp.office365.com")) == 0 ||
		m_server.CompareNoCase(_T("smtp.mail.yahoo.com")) == 0 ||
		m_server.CompareNoCase(_T("smtp.office365.com")) == 0 ||
		m_server.CompareNoCase(_T("smtp.aol.com")) == 0)
	{	
		CWnd* pWnd = GetDlgItem(IDC_EDIT_USER);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_PASSWORD);
		pWnd->EnableWindow(TRUE);
	}

	UpdateData(FALSE);
}

void CMailyChristmasDlg::OnChangeEditServer()
{
	_changeSettingforWellKnownServer();
}


void CMailyChristmasDlg::OnClickedButtonAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMailyChristmasDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!UpdateData(TRUE))
		return;

	m_from = m_from.Trim();
	m_to = m_to.Trim();

	CWnd* pWnd = NULL;
	if (m_from.GetLength() == 0)
	{
		MessageBox(_T("발신인 이메일 주소를 입력해주세요!"), _T("Error"), MB_OK | MB_ICONERROR);
		pWnd = GetDlgItem(IDC_EDIT_FROM);
		pWnd->SetFocus();
		return;
	}

	if (m_to.GetLength() == 0)
	{
		MessageBox(_T("수신인 이메일 주소를 입력해주세요!"), _T("Error"), MB_OK | MB_ICONERROR);
		pWnd = GetDlgItem(IDC_EDIT_TO);
		pWnd->SetFocus();
		return;
	}

	// TODO : 텍스트와 합성된 이미지 파일 생성
	CFileDialog* pFileDlg = new CFileDialog(TRUE);
	pFileDlg->m_ofn.Flags |= OFN_ALLOWMULTISELECT;



	// TODO : 이메일 전송 코드

	CString name = _T("");
	CString addr = _T("");

	_parseEmailAddr(m_from, name, addr); // 이름과 주소 따로 가져와서 각각 저장


	// 이메일 전송에 성공했을 때
	// if (oSmtp->SendMail() == 0)
	// {
		CString s;
		s.Append(addr);
		s.Append(_T("로 메시지가 성공적으로 전달되었습니다!"));
		MessageBox(s, _T("OK"), MB_OK);
	// }
	// else
	// {
		// CString s = _T("Failed to delivery to: ");
		// s.Append(addr);
		// s.Append(_T(": "));
		// s.Append(oSmtp->GetLastErrDescription());
		// MessageBox(s, _T("Error"), MB_OK | MB_ICONERROR);
	// }



	pWnd = GetDlgItem(IDOK);
	pWnd->EnableWindow(TRUE);
	pWnd = GetDlgItem(IDCANCEL);
	pWnd->EnableWindow(TRUE);



	CDialogEx::OnOK();
}
