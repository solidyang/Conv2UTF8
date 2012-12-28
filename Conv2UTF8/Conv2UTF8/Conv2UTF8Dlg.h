
// Conv2UTF8Dlg.h : ͷ�ļ�
//

#pragma once
#include <set>
#include <string>


// CConv2UTF8Dlg �Ի���
class CConv2UTF8Dlg : public CDialogEx
{
// ����
public:
	CConv2UTF8Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CONV2UTF8_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	std::set<std::string> _setExt;
	void parseExt();
	void doDir(const char *sDir);
	void doConvert(const char *sFile);

	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonBrowse();
	CString _sDir;
	int _nCodepage;
	CString _sExt;
	afx_msg void OnBnClickedButtonStart();
};
