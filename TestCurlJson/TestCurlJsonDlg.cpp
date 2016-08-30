
// TestCurlJsonDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestCurlJson.h"
#include "TestCurlJsonDlg.h"
#include "afxdialogex.h"

//#include<iostream>

//curl���
#include "curl/curl.h"
#include <string>

#pragma comment(lib, "libcurld_imp.lib") 

//json
#include "json\json.h" 
#pragma comment(lib,"json_vc71_libmtd.lib")





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


// CTestCurlJsonDlg �Ի���




CTestCurlJsonDlg::CTestCurlJsonDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestCurlJsonDlg::IDD, pParent)
	, m_show(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestCurlJsonDlg::DoDataExchange(CDataExchange* pDX)
{
	// ����MFCĬ�ϵ����ݽ��� 
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_show);
}

BEGIN_MESSAGE_MAP(CTestCurlJsonDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTestCurlJsonDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTestCurlJsonDlg ��Ϣ�������

BOOL CTestCurlJsonDlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestCurlJsonDlg::OnPaint()
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
HCURSOR CTestCurlJsonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//curl�ص�����
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


//ת����ʽ
wchar_t* ConvertUtf8ToUnicode(const char* utf8)
{
	if(!utf8)
	{
		wchar_t* buf = (wchar_t*)malloc(2);
		memset(buf,0,2);
		return buf;
	}
	int nLen = ::MultiByteToWideChar(CP_UTF8,MB_ERR_INVALID_CHARS,(LPCSTR)utf8,-1,NULL,0);
	//������Ҫ��unicode����  
	WCHAR * wszUNICODE = new WCHAR[nLen+1];  
	memset(wszUNICODE, 0, nLen * 2 + 2);  
	nLen = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)utf8, -1, wszUNICODE, nLen);    //��utf8ת��unicode
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

std::string U2Utf(const std::wstring& wstrUnicode)//Unicodeתutf8    
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
	//��ʵ�ִ��ݺ͵��ò���
    CURL *curl;
    CURLcode code;  
    curl = curl_easy_init();

	 if (curl)
     {
			curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.0.116:8080/TianMen/PushExitMessageAction!test.action");   // ָ��url
			std::string licenstr = "licensePlate=��A123456&driverName=����"; 
			//const char* licenChar = licenstr.c_str();
			std::wstring licenwstr = string2wstring(licenstr);
			licenstr = U2Utf(licenwstr);
			//std::string canshu = licenstr;
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, licenstr.c_str());	   //���ݲ��� ����������const char*	
			//curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "licensePlate=abcd123");	   //���ݲ���
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, http_data_writer);   //�ص�����
			//����д���� �ص����������� 
			std::string strData;  
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&strData);  
			// ִ������  
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

					Json::Reader reader;//json����  
                    Json::Value value;//��ʾһ��json��ʽ�Ķ���
					
					if(reader.parse(p_str,value))//������json�ŵ�json����  
						{  
							std::string total=value["total"].asString(); 
							std::string out;
							result.append(value["licensePlate"].asString()+"\n");
							result.append(value["driverName"].asString()+"\n");
							//std::cout<<total<<std::endl;  
							const Json::Value arrayObj=value["rows"];//������  
							
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
