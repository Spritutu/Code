
// EHPCSettingToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EHPCSettingTool.h"
#include "EHPCSettingToolDlg.h"
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include "Utility.h"
#include "ConfigTabFactory.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CBCGPDialog
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CBCGPDialog(IDD_ABOUTBOX)
{
}

BOOL CAboutDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	EnableVisualManagerStyle(TRUE, TRUE);

	return TRUE;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CBCGPDialog)
END_MESSAGE_MAP()


// CEHPCSettingToolDlg �Ի���



CEHPCSettingToolDlg::CEHPCSettingToolDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(IDD_EHPCSETTINGTOOL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//֧��Layout
	//EnableLayout(TRUE);
}

void CEHPCSettingToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CEHPCSettingToolDlg, CBCGPDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_SAVE, &CEHPCSettingToolDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_QUIT, &CEHPCSettingToolDlg::OnBnClickedBtnQuit)
END_MESSAGE_MAP()


// CEHPCSettingToolDlg ��Ϣ�������

BOOL CEHPCSettingToolDlg::OnInitDialog()
{
	using namespace std;
	CBCGPDialog::OnInitDialog();

	EnableVisualManagerStyle(TRUE,TRUE);

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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//��������ļ�
	vector<string> ConfigFileArray;
	DetectConfigFile(ConfigFileArray);

	if (!ConfigFileArray.empty())
	{
		InitDisplay();
		for (auto& Element : ConfigFileArray)
		{
			auto strTabName = m_TabMap.GetTabNameByConfigName(Element);
			if (!strTabName.empty())
			{
				auto pTabWnd = CreateConfigTabWnd(Element);
				if (nullptr != pTabWnd)
				{
					m_TabPtrArray.push_back(pTabWnd);
					pTabWnd->SetConfigFileName(Element);
					pTabWnd->CreateSelf(&m_TabWnd);
					m_TabWnd.AddTab(pTabWnd, CString(strTabName.c_str()));
				}
			}
		}
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CEHPCSettingToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CBCGPDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CEHPCSettingToolDlg::OnPaint()
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
		CBCGPDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CEHPCSettingToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CEHPCSettingToolDlg::InitDisplay(void)
{

	if (NULL == m_TabWnd.GetSafeHwnd())
	{
		CWnd* pWnd = GetDlgItem(IDC_STATIC_TAB_POS);
		if (nullptr != pWnd && NULL != pWnd->GetSafeHwnd())
		{
			pWnd->ShowWindow(SW_HIDE);
			CRect rc;
			pWnd->GetWindowRect(&rc);
			ScreenToClient(&rc);
			//����TabWnd
			m_TabWnd.Create(CBCGPTabWnd::STYLE_3D_ROUNDED, rc, this, CBaseTabWnd::s_nTabBaseID++, CBCGPTabWnd::LOCATION_TOP);
		
			m_TabWnd.EnableAutoColor();
		}
	
#if 0
		CBCGPStaticLayout* pLayout = (CBCGPStaticLayout*)GetLayout();
		if (pLayout != nullptr)
		{
			pLayout->AddAnchor(m_TabWnd.GetSafeHwnd(), CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeHorz);
		}
#endif
	}

	if (m_TabWnd.GetSafeHwnd())
	{
		m_TabWnd.RecalcLayout();
	}
}



void CEHPCSettingToolDlg::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDialog::OnSize(nType, cx, cy);

}

//���������ļ��Ƿ����
void CEHPCSettingToolDlg::DetectConfigFile(std::vector<std::string>& ConfigFileArray)
{
	using namespace std;
	using namespace boost::filesystem;
	ConfigFileArray.clear();
	//��ȡ��ǰĿ¼
	string strDir = Utility::GetExeDirecory();
	if (strDir.empty())
	{
		return;
	}

	directory_iterator End;
	//������ǰĿ¼
	for (directory_iterator Iter(strDir); Iter != End; ++Iter)
	{

		path TempPath = *Iter;
		string strExtensionName = TempPath.extension().string();
		if (boost::iends_with(strExtensionName, "json"))
		{
			//��ȡ�����ļ�����
			ConfigFileArray.push_back(TempPath.filename().string());
		}
	}

}


void CEHPCSettingToolDlg::OnBnClickedBtnSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	for (auto Iter = m_TabPtrArray.begin(); Iter != m_TabPtrArray.end(); ++Iter)
	{
		Iter->SaveConfig();
	}
}


void CEHPCSettingToolDlg::OnBnClickedBtnQuit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	PostMessage(WM_CLOSE, 0, 0);
}


BOOL CEHPCSettingToolDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (WM_KEYDOWN == pMsg->message)
	{
		if (VK_RETURN == pMsg->wParam || VK_ESCAPE == pMsg->wParam)
		{
			return TRUE;
		}
	}

	return CBCGPDialog::PreTranslateMessage(pMsg);
}
