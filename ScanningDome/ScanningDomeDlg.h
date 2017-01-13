
// ScanningDomeDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CScanningDomeDlg �Ի���
class CScanningDomeDlg : public CDialogEx
{
// ����
public:
	CScanningDomeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCANNINGDOME_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit edit_feature_shift_;
	CEdit edit_feature_len_;
	CEdit edit_file_path_;
	CEdit edit_feature_;
	bool GetFile(wchar_t* file_path);
	bool OnCopyText(CString source);
	afx_msg void OnBnClickedButtonOpenFile();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedButtonCopyFilePath();
	afx_msg void OnBnClickedButtonCopyFeature();
	afx_msg void OnBnClickedButtonCopyFileImage();
	CEdit m_edit_iamge_md5_;
	CEdit edit_file_size_start_;
	afx_msg void OnBnClickedButtonCopyFileSize();
};
