
// MFCWinRTOCRDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "MFCWinRTOCR.h"
#include "MFCWinRTOCRDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
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


// CMFCWinRTOCRDlg ダイアログ



CMFCWinRTOCRDlg::CMFCWinRTOCRDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCWINRTOCR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCWinRTOCRDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCWinRTOCRDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCWinRTOCRDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMFCWinRTOCRDlg メッセージ ハンドラー

BOOL CMFCWinRTOCRDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
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

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CMFCWinRTOCRDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CMFCWinRTOCRDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CMFCWinRTOCRDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCWinRTOCRDlg::OnBnClickedButton1()
{
	Button1Async();
}

winrt::Windows::Foundation::IAsyncAction CMFCWinRTOCRDlg::Button1Async()
{
	//ファイルピッカーでファイルを選んで
	auto picker = winrt::Windows::Storage::Pickers::FileOpenPicker();
	picker.as<IInitializeWithWindow>()->Initialize(this->m_hWnd);
	picker.FileTypeFilter().Append(L".jpg");
	picker.FileTypeFilter().Append(L".png");
	auto picfile = co_await picker.PickSingleFileAsync();

	//ファイルを開いて
	auto picstream = co_await picfile.OpenAsync(winrt::Windows::Storage::FileAccessMode::Read);
	auto picdecoder = co_await winrt::Windows::Graphics::Imaging::BitmapDecoder::CreateAsync(picstream);
	auto showpic = co_await picdecoder.GetSoftwareBitmapAsync(winrt::Windows::Graphics::Imaging::BitmapPixelFormat::Bgra8, winrt::Windows::Graphics::Imaging::BitmapAlphaMode::Premultiplied);

	//OCR機能を使用する。
	winrt::Windows::Media::Ocr::OcrEngine ocr = nullptr;
	ocr = winrt::Windows::Media::Ocr::OcrEngine::TryCreateFromUserProfileLanguages();
	auto result = co_await ocr.RecognizeAsync(showpic);

	//結果の表示
	winrt::hstring restext = result.Text();
	auto msgdlg = winrt::Windows::UI::Popups::MessageDialog(L"Result");
	msgdlg.as<IInitializeWithWindow>()->Initialize(this->m_hWnd);
	msgdlg.Content(restext);
	auto dlgres = co_await msgdlg.ShowAsync();
}
