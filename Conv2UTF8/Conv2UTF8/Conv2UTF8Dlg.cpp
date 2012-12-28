
// Conv2UTF8Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Conv2UTF8.h"
#include "Conv2UTF8Dlg.h"
#include "afxdialogex.h"
#include <kernel/fileio.h>
#include <kernel/kernel.h>
#include <kernel/Logger.h>
using namespace new3d::kernel;

HANDLE g_hModule = GetModuleHandle(NULL);

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CConv2UTF8Dlg �Ի���




CConv2UTF8Dlg::CConv2UTF8Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConv2UTF8Dlg::IDD, pParent)
	, _sDir(_T(""))
	, _nCodepage(0)
	, _sExt(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CConv2UTF8Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PATH, _sDir);
	DDX_Text(pDX, IDC_EDIT_CODEPAGE, _nCodepage);
	DDX_Text(pDX, IDC_EDIT3_FILEEXT, _sExt);
}

BEGIN_MESSAGE_MAP(CConv2UTF8Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, &CConv2UTF8Dlg::OnBnClickedButtonBrowse)
	ON_BN_CLICKED(IDC_BUTTON_START, &CConv2UTF8Dlg::OnBnClickedButtonStart)
END_MESSAGE_MAP()


// CConv2UTF8Dlg ��Ϣ�������

BOOL CConv2UTF8Dlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	_sExt = "lua;xml;c;cpp;h;hpp;cxx;";
	_nCodepage = 936;
	UpdateData(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CConv2UTF8Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CConv2UTF8Dlg::OnPaint()
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
HCURSOR CConv2UTF8Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CConv2UTF8Dlg::OnBnClickedButtonBrowse()
{
	char sDis[MAX_PATH];
	BROWSEINFO bi;
	bi.hwndOwner = GetSafeHwnd();
	bi.pidlRoot = NULL;
	bi.pszDisplayName = sDis;
	bi.lpszTitle = "Select directory where convert from";
	bi.ulFlags = BIF_USENEWUI | BIF_RETURNONLYFSDIRS | BIF_RETURNONLYFSDIRS;
	bi.lpfn = 0;
	bi.lParam = 0;
	bi.iImage = 0;
	LPITEMIDLIST pList =  SHBrowseForFolder(&bi);
	if(NULL == pList)
		return;

	char sPath2[MAX_PATH];
	SHGetPathFromIDList(pList, sPath2);
	_sDir = sPath2;
	UpdateData(FALSE);
}

void CConv2UTF8Dlg::parseExt()
{
	_setExt.clear();

	if(!_sExt.IsEmpty())
	{
		const char *from = _sExt;
		const char *sep = from;
		while(*sep)
		{
			if(*sep == ';')
			{
				if(sep > from)
				{
					std::string t;
					t.assign(from, sep-from);
					strlwr(&t[0]);
					_setExt.insert(t);

					from = sep+1;
				}
			}
			++sep;
		}

		if(sep > from)
		{
			std::string t;
			t.assign(from, sep-from);
			strlwr(&t[0]);
			_setExt.insert(t);
		}
	}
}

void CConv2UTF8Dlg::doConvert(const char *sFile)
{
	FILE *file = fopen(sFile, "rb");
	if(file == NULL)
	{
		LOGGER::Error("read %s failed\r\n", sFile);
		return;
	}

	fseek(file, 0, SEEK_END);
	unsigned size = ftell(file);
	char *src = new char[size+1];

	fseek(file, 0, SEEK_SET);
	fread(src, size, 1, file);
	src[size] = 0;
	fclose(file);

	if(size > 3 && ((*(unsigned*)src) & 0xFFFFFF) == 0xBFBBEF)	//utf-8
	{	
		return;		
	}

	//convert to wchar
	wchar_t *srcw = new wchar_t[size+1];
	int sizew = MultiByteToWideChar(_nCodepage, 0, src, size, srcw, size);
	//conver to utf8
	char *dst = new char[sizew*4+1];
	int size2 = WideCharToMultiByte(CP_UTF8, 0, srcw, sizew, dst, sizew*4, NULL, NULL);

	//write back
	file = fopen(sFile, "wb");
	if(file == NULL)
	{
		SetFileAttributes(sFile, FILE_ATTRIBUTE_NORMAL);
		file = fopen(sFile, "wb");
	}

	if(file == NULL)
		LOGGER::Error("write %s failed\r\n", sFile);
	else
	{
		const unsigned h = 0xBFBBEF;
		fwrite(&h, 3, 1, file);
		fwrite(dst, size2, 1, file);
		fclose(file);
	}

	SAFE_DELETE_ARRAY(src);
	SAFE_DELETE_ARRAY(srcw);
	SAFE_DELETE_ARRAY(dst);
}

void CConv2UTF8Dlg::doDir(const char *sDir)
{
	L3_FIND_HANDLE hfind;
	L3_DIRECTORY_TYPE attr;
	const char *fn = l3Kernel_SysFindFirst(sDir, &hfind, &attr);
	while(fn)
	{
		if(attr.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if(strcmp(fn,".") && strcmp(fn,".."))
			{
				std::string subdir = sDir;
				subdir += "\\";
				subdir += fn;

				l3Kernel_SysPushCWD();
				doDir(subdir.c_str());
				l3Kernel_SysPopCWD();
			}
		}
		else
		{
			std::string ext;
			l3Kernel_extractExt(fn, ext);
			strlwr(&ext[0]);
			if(_setExt.find(ext) != _setExt.end())
			{
				std::string path = sDir;
				path += "\\";
				path += fn;
				doConvert(path.c_str());
			}
		}

		fn = l3Kernel_SysFindNext(hfind, &attr);
	}

	l3Kernel_SysCloseFind(hfind);
}

void CConv2UTF8Dlg::OnBnClickedButtonStart()
{
	UpdateData(TRUE);
	if(_sDir.IsEmpty())
		return;

	parseExt();

	doDir(_sDir);
}
