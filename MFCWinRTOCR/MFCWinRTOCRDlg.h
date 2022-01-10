
// MFCWinRTOCRDlg.h : ヘッダー ファイル
//

#pragma once


// CMFCWinRTOCRDlg ダイアログ
class CMFCWinRTOCRDlg : public CDialogEx
{
// コンストラクション
public:
	CMFCWinRTOCRDlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCWINRTOCR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	winrt::Windows::Foundation::IAsyncAction Button1Async();
};
