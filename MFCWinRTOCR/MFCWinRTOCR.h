
// MFCWinRTOCR.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CMFCWinRTOCRApp:
// このクラスの実装については、MFCWinRTOCR.cpp を参照してください
//

class CMFCWinRTOCRApp : public CWinApp
{
public:
	CMFCWinRTOCRApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CMFCWinRTOCRApp theApp;
