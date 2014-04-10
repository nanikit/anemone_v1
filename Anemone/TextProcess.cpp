#include "StdAfx.h"
#include "TextProcess.h"


CTextProcess::CTextProcess()
{
	StartWatchClip();
}


void CTextProcess::StartWatchClip()
{
	hWnds.Clip = SetClipboardViewer(hWnds.Main);
}

void CTextProcess::EndWatchClip()
{
	ChangeClipboardChain(hWnds.Clip, NULL);
}

bool CTextProcess::OnDrawClipboard()
{
	char *szBuff, *szBuff2;
	wchar_t *lpszBuff;
	int nBufLen;

	std::wstring szClipText;
	std::wstring szNameOrg, szNameTrans;
	std::wstring szContextOrg, szContextTrans;

	OpenClipboard(hWnds.Clip);
	HANDLE hClipData = GetClipboardData(CF_UNICODETEXT);
	
	// Ŭ������ ������ ���� (�Ǵ� ���� �ʴ� �԰�)
	if (hClipData == NULL)
	{
		MessageBox(0, 0, 0, 0);
		return false;
	}

	szClipText = (wchar_t*)GlobalLock(hClipData);
	GlobalUnlock(hClipData);

	szContextOrg = szClipText;
	nBufLen = WideCharToMultiByte(932, 0, szContextOrg.c_str(), -1, NULL, NULL, NULL, NULL);
	szBuff = (char *)malloc((nBufLen+2)*2);

	// �޸� �Ҵ� ����
	if (szBuff == NULL)
	{
		MessageBox(0, 0, 0, 0);
		return false;
	}

	WideCharToMultiByte(932, 0, szContextOrg.c_str(), -1, szBuff, nBufLen, NULL, NULL);

	szBuff2 = (char *)Cl.TransEngine->J2K_TranslateMMNT(0, szBuff);
	free(szBuff);

	nBufLen = MultiByteToWideChar(949, 0, szBuff2, -1, NULL, NULL);
	lpszBuff = (wchar_t *)malloc((nBufLen+2)*2);

	// �޸� �Ҵ� ����
	if (lpszBuff == NULL)
	{
		MessageBox(0, 0, 0, 0);
		return false;
	}

	MultiByteToWideChar(949, 0, szBuff2, -1, lpszBuff, nBufLen);

	szContextTrans = lpszBuff;
	free(lpszBuff);
	Cl.TransEngine->J2K_FreeMem(szBuff2);

	*(Cl.TextRenderer->szContextOrg) = szContextOrg;
	*(Cl.TextRenderer->szContextTrans) = szContextTrans;
	//SendMessage(hWnds.Main, WM_PAINT, 0, 0);
	
	Cl.TextRenderer->Paint();

	CloseClipboard();

	ChangeClipboardChain(hWnds.Main, NULL);
	hWnds.Clip = SetClipboardViewer(hWnds.Main);
	return true;
}

CTextProcess::~CTextProcess()
{
	// Ŭ������ ���� ����
	EndWatchClip();
}