
// TestCurlJsonDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestCurlJson.h"
#include "TestCurlJsonDlg.h"
#include "afxdialogex.h"

//#include<iostream>

//curl添加
#include "curl/curl.h"
#include <string>

#pragma comment(lib, "libcurld_imp.lib") 

//json
#include "json\json.h" 
#pragma comment(lib,"json_vc71_libmtd.lib")





#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CTestCurlJsonDlg 对话框




CTestCurlJsonDlg::CTestCurlJsonDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestCurlJsonDlg::IDD, pParent)
	, m_show(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestCurlJsonDlg::DoDataExchange(CDataExchange* pDX)
{
	// 处理MFC默认的数据交换 
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_show);
}

BEGIN_MESSAGE_MAP(CTestCurlJsonDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTestCurlJsonDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTestCurlJsonDlg 消息处理程序

BOOL CTestCurlJsonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTestCurlJsonDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestCurlJsonDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTestCurlJsonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//curl回调方法
size_t http_data_writer(void* data, size_t size, size_t nmemb, void* content)  
{  
    long totalSize = size*nmemb;  
    std::string* symbolBuffer = (std::string*)content;  
    if(symbolBuffer)  
    {  
        symbolBuffer->append((char *)data, ((char*)data)+totalSize);  
    }  
    return totalSize;  
}


//转换格式
wchar_t* ConvertUtf8ToUnicode(const char* utf8)
{
	if(!utf8)
	{
		wchar_t* buf = (wchar_t*)malloc(2);
		memset(buf,0,2);
		return buf;
	}
	int nLen = ::MultiByteToWideChar(CP_UTF8,MB_ERR_INVALID_CHARS,(LPCSTR)utf8,-1,NULL,0);
	//返回需要的unicode长度  
	WCHAR * wszUNICODE = new WCHAR[nLen+1];  
	memset(wszUNICODE, 0, nLen * 2 + 2);  
	nLen = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)utf8, -1, wszUNICODE, nLen);    //把utf8转成unicode
	return wszUNICODE;
}

/*char* ConvertUnicodeToUtf8(const wchar_t* unicode)  
{  
	//if(unicode == NULL){return unicode("\0");}
    int len;  
    len = WideCharToMultiByte(CP_UTF8, 0,unicode, -1, NULL, 0, NULL, NULL);  
    char *szUtf8 = (char*)malloc(len + 1);  
    memset(szUtf8, 0, len + 1);  
    WideCharToMultiByte(CP_UTF8, 0,unicode, -1, szUtf8, len, NULL,NULL);  
    return szUtf8;  
}*/

std::string wstring2string(const std::wstring & wstr)
{
   std::string str("");
   int nLen = WideCharToMultiByte(CP_ACP,0,(LPCWSTR)wstr.c_str(),(int)wstr.length(),NULL,0,NULL,NULL);
   if(nLen <= 0) {return str;}
   str.resize(nLen,'\0');
   WideCharToMultiByte(CP_ACP,0,(LPCWSTR)wstr.c_str(),(int)wstr.length(),(LPSTR)str.c_str(),nLen,NULL,NULL);
   return str ;
}

std::wstring string2wstring(const std::string & str)
{
   std::wstring wstr(L"");
   int nLen = MultiByteToWideChar(CP_ACP,0,(LPCSTR)str.c_str(),(int)str.length(),0,0);
   if(nLen <= 0){return wstr;}
   wstr.resize(nLen,L'\0');
   MultiByteToWideChar(CP_ACP,0,(LPCSTR)str.c_str(),(int)str.length(),(LPWSTR)wstr.c_str(),nLen);
   return wstr;
}

std::string U2Utf(const std::wstring& wstrUnicode)//Unicode转utf8    
{    
    std::string strRet;
    if( wstrUnicode.empty() )  
        return strRet; 
    int nLen = WideCharToMultiByte(CP_UTF8, 0, wstrUnicode.c_str(), -1, NULL, 0, NULL, NULL);    
    char* pBuffer=new char[nLen+1];  
    pBuffer[nLen] = '\0';  
    nLen = WideCharToMultiByte(CP_UTF8, 0, wstrUnicode.c_str(), -1, pBuffer, nLen, NULL, NULL);   
    strRet.append(pBuffer);  
    delete[] pBuffer;  
    return strRet;    
}  


void CTestCurlJsonDlg::OnBnClickedButton1()
{
	//已实现传递和调用参数
    CURL *curl;
    CURLcode code;  
    curl = curl_easy_init();

	 if (curl)
     {
			curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.0.116:8080/TianMen/PushExitMessageAction!test.action");   // 指定url
			std::string licenstr = "licensePlate=鄂A123456&driverName=张三"; 
			//const char* licenChar = licenstr.c_str();
			std::wstring licenwstr = string2wstring(licenstr);
			licenstr = U2Utf(licenwstr);
			//std::string canshu = licenstr;
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, licenstr.c_str());	   //传递参数 参数必须是const char*	
			//curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "licensePlate=abcd123");	   //传递参数
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, http_data_writer);   //回调函数
			//设置写数据 回调函数必须有 
			std::string strData;  
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&strData);  
			// 执行请求  
			code = curl_easy_perform(curl); 
			if(code == CURLcode::CURLE_OK)  
			{  
					UpdateData(TRUE);				    
					std::string result;
				    long responseCode = 0;  
					curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);  
					if (responseCode < 200 || responseCode >= 300 || strData.empty()) { curl_easy_cleanup(curl);return ; }  
					const char *p=strData.data();
					WCHAR *p_new = ConvertUtf8ToUnicode(p);
					std::string p_str = wstring2string(p_new);

					Json::Reader reader;//json解析  
                    Json::Value value;//表示一个json格式的对象
					
					if(reader.parse(p_str,value))//解析出json放到json中区  
						{  
							std::string total=value["total"].asString(); 
							std::string out;
							result.append(value["licensePlate"].asString()+"\n");
							result.append(value["driverName"].asString()+"\n");
							//std::cout<<total<<std::endl;  
							const Json::Value arrayObj=value["rows"];//迭代器  
							
							for (int i=0; i < arrayObj.size();i++)    
							{  
								out=arrayObj[i]["shiftNumber"].asString(); 
								   	  
	                             //m_show = out;  
								//m_show = out.c_str();
								result.append(out);

							}  
						} 
					    m_show = result.c_str();
					   UpdateData(FALSE); 

					 getchar();  
						
			}
	  }
	  curl_easy_cleanup(curl);
}
