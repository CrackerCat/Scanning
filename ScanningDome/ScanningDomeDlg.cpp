
// ScanningDomeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ScanningDome.h"
#include "ScanningDomeDlg.h"
#include "afxdialogex.h"
#include <string>
#include "Search.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CScanningDomeDlg �Ի���



CScanningDomeDlg::CScanningDomeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SCANNINGDOME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScanningDomeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FEATURE_SHIFT, edit_feature_shift_);
	DDX_Control(pDX, IDC_EDIT_FEATURE_LEN, edit_feature_len_);
	DDX_Control(pDX, IDC_EDIT_FILE_PATH, edit_file_path_);
	DDX_Control(pDX, IDC_EDIT_FEATURE, edit_feature_);
	DDX_Control(pDX, IDC_EDIT_FILE_IMAGE, m_edit_iamge_md5_);
	DDX_Control(pDX, IDC_EDIT_FILE_SIZE_START, edit_file_size_start_);
}

BEGIN_MESSAGE_MAP(CScanningDomeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN_FILE, &CScanningDomeDlg::OnBnClickedButtonOpenFile)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON_COPY_FILE_PATH, &CScanningDomeDlg::OnBnClickedButtonCopyFilePath)
	ON_BN_CLICKED(IDC_BUTTON_COPY_FEATURE, &CScanningDomeDlg::OnBnClickedButtonCopyFeature)
	ON_BN_CLICKED(IDC_BUTTON_COPY_FILE_IMAGE, &CScanningDomeDlg::OnBnClickedButtonCopyFileImage)
	ON_BN_CLICKED(IDC_BUTTON_COPY_FILE_SIZE, &CScanningDomeDlg::OnBnClickedButtonCopyFileSize)
END_MESSAGE_MAP()


// CScanningDomeDlg ��Ϣ�������

BOOL CScanningDomeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	edit_feature_shift_.SetWindowTextW(L"100");
	edit_feature_len_.SetWindowTextW(L"100");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CScanningDomeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CScanningDomeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CScanningDomeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CScanningDomeDlg::GetFile(wchar_t* file_path)
{
	unsigned int kCodeGetSize = 100;
	unsigned int kCodeGetShift = 100;
	CString cs_edit_featrue_shift;
	CString cs_edit_featrue_len;
	CString a_to_w;

	edit_feature_shift_.GetWindowTextW(cs_edit_featrue_shift);
	edit_feature_len_.GetWindowTextW(cs_edit_featrue_len);
	kCodeGetShift = _wtoi(cs_edit_featrue_shift.GetBuffer());
	kCodeGetSize = _wtoi(cs_edit_featrue_len.GetBuffer());

	char iamge_md5[512] = { 0 };
	char *data = new char[kCodeGetSize];
	wchar_t buff[512] = { 0 };
	wchar_t *data_str = new wchar_t[kCodeGetSize * 2 + 1 ];
	auto st_size = get_file_data(file_path, nullptr) / 1024;
	//��ȡ������
	auto if_success = get_code_feature(file_path, kCodeGetShift, data, kCodeGetSize);
	if (!if_success) {
		return false;
	}
	get_image_feature(file_path, iamge_md5);
	change_chars(data, kCodeGetSize, data_str);
	edit_file_path_.SetWindowTextW(file_path);
	edit_feature_.SetWindowTextW(data_str);
	a_to_w = iamge_md5;
	m_edit_iamge_md5_.SetWindowTextW(a_to_w);

	_itow(st_size, buff, 10);
	CString a_to_w2 = buff;
	a_to_w2 += L" * 1024";
	edit_file_size_start_.SetWindowTextW(a_to_w2);
	delete data;
	delete data_str;
	return true;
}

void CScanningDomeDlg::OnBnClickedButtonOpenFile()
{
	edit_file_path_.SetWindowTextW(L"");
	edit_feature_.SetWindowTextW(L"");

	BOOL isOpen = TRUE;     //�Ƿ��(����Ϊ����)  
	CString defaultDir = L"E:\\";   //Ĭ�ϴ򿪵��ļ�·��  
	CString fileName = L"";         //Ĭ�ϴ򿪵��ļ���  
	CString filter = L"�ļ� (*.exe; *.dll)|*.exe;*.dll||";   //�ļ����ǵ�����  
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_READONLY, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = L"E:\\FileTest\\test.doc";
	INT_PTR result = openFileDlg.DoModal();
	if (result != IDOK) {
		return;
	}

	if (!GetFile(openFileDlg.GetPathName().GetBuffer())){
		AfxMessageBox(L"�ļ���ȡʧ��");
		return;
	}
}


void CScanningDomeDlg::OnDropFiles(HDROP hDropInfo)
{
	int DropCount = DragQueryFile(hDropInfo, -1, NULL, 0);//ȡ�ñ��϶��ļ�����Ŀ  
	for (int i = 0; i< DropCount; i++){
		WCHAR wcStr[MAX_PATH];
		DragQueryFile(hDropInfo, i, wcStr, MAX_PATH);//�����ҷ�ĵ�i���ļ����ļ���  
		if (!StrCmpW(wcStr, L"")) {
			continue;
		}
		if (!GetFile(wcStr)) {
			AfxMessageBox(L"�ļ���ȡʧ��");
		}
		break;
	}
	DragFinish(hDropInfo);  //�ϷŽ�����,�ͷ��ڴ�

	CDialogEx::OnDropFiles(hDropInfo);
}

bool CScanningDomeDlg::OnCopyText(CString source)
{
	//�ı����ݱ�����source������
	if (OpenClipboard())
	{
		//��ֹ��ASCII���Ը��Ƶ����а�Ϊ����
		int buff_size = source.GetLength();
		CStringW strWide = CStringW(source);
		int nLen = strWide.GetLength();
		//�����а��ÿ�
		::EmptyClipboard();
		HANDLE clipbuffer = ::GlobalAlloc(GMEM_DDESHARE, (nLen + 1) * 2);
		if (!clipbuffer)
		{
			::CloseClipboard();
			return false;
		}
		char* buffer = (char*)::GlobalLock(clipbuffer);
		memset(buffer, 0, (nLen + 1) * 2);
		memcpy_s(buffer, nLen * 2, strWide.GetBuffer(0), nLen * 2);
		strWide.ReleaseBuffer();
		::GlobalUnlock(clipbuffer);
		::SetClipboardData(CF_UNICODETEXT, clipbuffer);
		::CloseClipboard();
	}
	return true;
}

void CScanningDomeDlg::OnBnClickedButtonCopyFilePath()
{
	CString text;
	edit_file_path_.GetWindowTextW(text);
	OnCopyText(text);
}


void CScanningDomeDlg::OnBnClickedButtonCopyFeature()
{
	CString text;
	edit_feature_.GetWindowTextW(text);
	OnCopyText(text);
}


void CScanningDomeDlg::OnBnClickedButtonCopyFileImage()
{
	CString text;
	m_edit_iamge_md5_.GetWindowTextW(text);
	OnCopyText(text);
}


void CScanningDomeDlg::OnBnClickedButtonCopyFileSize()
{
	CString text;
	edit_file_size_start_.GetWindowTextW(text);
	OnCopyText(text);
}
