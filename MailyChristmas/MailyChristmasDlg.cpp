﻿
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
	, m_radio_index(0)
	, m_body(_T(""))
	, m_password(_T(""))
	, m_subject(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMailyChristmasDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FROM, m_from);
	DDX_Text(pDX, IDC_EDIT_USER, m_user);
	DDX_Text(pDX, IDC_EDIT_TO, m_to);
	DDX_Radio(pDX, IDC_RADIO1, (int&)m_radio_index);
	DDX_Text(pDX, IDC_EDIT_SUBJECT, m_subject);
	DDX_Text(pDX, IDC_EDIT_BODY, m_body);
	DDX_Control(pDX, IDC_STATIC_SANTA, m_img_santa);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_password);
	DDX_Text(pDX, IDC_EDIT_SUBJECT, m_subject);
}

BEGIN_MESSAGE_MAP(CMailyChristmasDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT_FROM, &CMailyChristmasDlg::OnChangeEditFrom)
	ON_EN_CHANGE(IDC_EDIT_SERVER, &CMailyChristmasDlg::OnChangeEditServer)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CMailyChristmasDlg::OnClickedButtonAdd)
	ON_BN_CLICKED(IDOK, &CMailyChristmasDlg::OnBnClickedOk)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO1, IDC_RADIO4, &CMailyChristmasDlg::RadioCtrl)
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
		// TODO: Add extra initialization here
	m_body += _T("<h3>To. </h3>\r\n\r\n");
	m_body += _T("여기에 내용을 입력해주세요.\r\n\r\n");
	m_body += _T("<h3>From. </h3>\r\n\r\n");

	UpdateData(FALSE);

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
	else if (domain.CompareNoCase(_T("naver.com")) == 0)
	{
		m_server = _T("smtp.naver.com");
		m_user = addr.Mid(0, pos);
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

void CMailyChristmasDlg::RadioCtrl(UINT id)
{
	switch (id)
	{
	case IDC_RADIO1:
		m_selected_img = "santa_pad.bmp";
		break;
	case IDC_RADIO2:
		m_selected_img = "rudolf_pad.bmp";
		break;
	case IDC_RADIO3:
		m_selected_img = "snowman_pad.bmp";
		break;
	case IDC_RADIO4:
		m_selected_img = "cookeie_pad.bmp";
		break;
	}
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




	IMailPtr oSmtp = NULL;
	oSmtp.CreateInstance(__uuidof(EASendMailObjLib::Mail));


	try
	{
		//The license code for EASendMail ActiveX Object,
		//for evaluation usage, please use "TryIt" as the license code.
		oSmtp->LicenseCode = _T("TryIt");
	}
	catch (_com_error& ep)
	{
		MessageBox((const TCHAR*)ep.Description(), _T("Error"), MB_OK);
		return;
	}

	oSmtp->Charset = _T("utf-8");

	oSmtp->ServerAddr = (LPCTSTR)m_server;
	oSmtp->ServerPort = 25;

	oSmtp->Protocol = 0; // SMTP

	const int ConnectNormal = 0;
	const int ConnectSSLAuto = 1;
	const int ConnectSTARTTLS = 2;
	const int ConnectDirectSSL = 3;
	const int ConnectTryTLS = 4;

	oSmtp->ConnectType = ConnectTryTLS;

	// 대부분의 최신 SMTP 서버는 이제 SSL/TLS 연결을 요구합니다.
	// ConnectTryTLS는 서버가 SSL/TLS 연결을 지원하는지 여부를 의미하며, 지원하는 경우 SSL/TLS가 자동으로 사용됩니다.
	if (m_server.GetLength() > 0)
	{
		
		oSmtp->UserName = (LPCTSTR)m_user;
		oSmtp->Password = (LPCTSTR)m_password;

		// 서버 포트에 기반하여 SSL/TLS를 사용합니다.
		oSmtp->ConnectType = ConnectSSLAuto;
	}

	CString name = _T("");
	CString addr = _T("");

	_parseEmailAddr(m_from, name, addr);

	oSmtp->From = (LPCTSTR)name;
	oSmtp->FromAddr = (LPCTSTR)addr;

	oSmtp->SignerCert->Unload();

	oSmtp->AddRecipientEx((LPCTSTR)m_to, 0); // 0, Normal recipient, 1, cc, 2, bcc

	CString rcpts = m_to;


	oSmtp->RecipientsCerts->Clear();




	oSmtp->Subject = (LPCTSTR)m_subject;
	

	// 현재 선택된 라디오 버튼의 ID를 얻음
	int selectedRadioID = GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO4);

	// 선택된 라디오 버튼에 따라 이미지 소스 설정
	CString imageSource;
	switch (selectedRadioID)
	{
	case IDC_RADIO1:
		imageSource = "https://i.ibb.co/KDLL1h5/santa-pad.jpg";
		break;
	case IDC_RADIO2:
		imageSource = "https://i.ibb.co/KrWdY4k/rudolf-pad.jpg";
		break;
	case IDC_RADIO3:
		imageSource = "https://i.ibb.co/n8ytJZt/snowman-pad.jpg";
		break;
	case IDC_RADIO4:
		imageSource = "https://i.ibb.co/K61qCSt/cookie-pad.jpg";
		break;
	default:
		break;
	}


	CString currentText;
	GetDlgItemText(IDC_EDIT_BODY, currentText);

	CString htmlCode;
	htmlCode += _T("<body style='background-image: url(");
	htmlCode += imageSource;
	htmlCode += _T("); background-size: 500px; width:500px; height:500px;  background-repeat: no-repeat; display: flex; justify-content: center; align-items: center;'>");
	htmlCode += _T("<div style='color: black; font-size: 15px; text-align: center; font-family: Arial, sans-serif; padding: 100px; box-sizing: border-box;'>");
	htmlCode += currentText;
	htmlCode += _T("</div></body>");



	m_body = htmlCode;
	CString body = m_body;
	
	oSmtp->BodyText = (LPCTSTR)body;
	oSmtp->BodyFormat = 1; //' Using HTML FORMAT to send mail

	pWnd = GetDlgItem(IDOK);
	pWnd->EnableWindow(FALSE);
	pWnd = GetDlgItem(IDCANCEL);
	pWnd->EnableWindow(FALSE);


	if (oSmtp->SendMail() == 0)
	{
		MessageBox(_T("메시지가 성공적으로 전달되었습니다!"), _T("OK"), MB_OK);
	}
	else
	{
		CString error = _T("이메일 전송에 실패했습니다!");
		error.Append(oSmtp->GetLastErrDescription());
		MessageBox(error, _T("Error"), MB_OK | MB_ICONERROR);

		CString server = m_server.MakeLower();
		if (server.Find(_T("gmail.com")) != -1)
		{
			MessageBox(_T("Gmail doesn't support user/password login, please create app password, see comments in the source codes"));
		}
		else if (server.Find(_T("office365.com")) != -1)
		{
			MessageBox(_T("It is possible that Office 365 disabled password login in your tenant, see comments in the source codes"));

		}
	}

	pWnd = GetDlgItem(IDOK);
	pWnd->EnableWindow(TRUE);
	pWnd = GetDlgItem(IDCANCEL);
	pWnd->EnableWindow(TRUE);
}
