
// Conv2UTF8Dlg.h : 头文件
//

#pragma once
#include <set>
#include <string>


// CConv2UTF8Dlg 对话框
class CConv2UTF8Dlg : public CDialogEx
{
// 构造
public:
	CConv2UTF8Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CONV2UTF8_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	std::set<std::string> _setExt;
	void parseExt();
	void doDir(const char *sDir);
	void doConvert(const char *sFile);

	HICON m_hIcon;

	// 生成的消息映射函数
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
