#include "pch.h"
#include "windowsUtil.h"

#ifdef _WIN32

bool common::winutil::ScreenShot(const char* szSavePath, const ShotRect *ShotInfo)
{
  //��ʾ����Ļ
  HDC hCurrScreen = GetDC(NULL);

  //����һ�����ݵ�DC,���ڴ��б�ʾ��ǰλͼ��������
  HDC hMemDC = CreateCompatibleDC(hCurrScreen);

  //���
  int iShotWidth,iShotHeight;
  
  //��ͼ��ʼ����
  int iShotStartX,iShotStartY;

  //��ָ���������ȡȫ��Ļ
  if (nullptr == ShotInfo)
  {
    iShotWidth  = GetDeviceCaps(hCurrScreen, HORZRES);
    iShotHeight = GetDeviceCaps(hCurrScreen, VERTRES);
    iShotStartX = 0;
    iShotStartY = 0;
  }
  else
  {
    iShotWidth  = ShotInfo->rect_width;
    iShotHeight = ShotInfo->rect_height;
    iShotStartX = ShotInfo->x_start;
    iShotStartY = ShotInfo->y_start;
  }

  //��ǰ��Ļλͼ
  HBITMAP hBmp = CreateCompatibleBitmap(hCurrScreen, iShotWidth, iShotHeight);

  //�õ�ǰλͼ�����ʾ�ڴ�����Ļλͼ������
  SelectObject(hMemDC,hBmp);

  //����ǰ��Ļͼ���Ƶ��ڴ���
  BOOL ret = BitBlt(hMemDC, 0, 0, iShotWidth, iShotHeight, hCurrScreen, iShotStartX, iShotStartY, SRCCOPY);

  //BMPͼ����Ϣͷ
  BITMAPINFOHEADER hBmpInfo;
                   hBmpInfo.biSize          = INFO_HEAD;
                   hBmpInfo.biWidth         = iShotWidth;
                   hBmpInfo.biHeight        = iShotHeight;
                   hBmpInfo.biPlanes        = TAG_DEV_PLAS;
                   hBmpInfo.biClrUsed       = NO_COLOR_TAB;
                   hBmpInfo.biBitCount      = BITS_PER_PIX;
                   hBmpInfo.biSizeImage     = UNCMP_RGB;
                   hBmpInfo.biCompression   = BI_RGB;
                   hBmpInfo.biClrImportant  = ALL_COLOR;
                   hBmpInfo.biXPelsPerMeter = H_RESOL_0;
                   hBmpInfo.biYPelsPerMeter = V_RESOL_0;

  /* * * * * * * * * * * * * * * * * * * *
   * Windows��4�ֽڷ����ڴ�
   * ���ȼ���ÿ������Ҫ��bit��,����4�ֽڶ���
   * �ڶԶ��������ݳ�4,��DWORDתΪBYTE
   * ÿ��ʵ����ռBYTE��ͼ�������õ�����Դ��С
   * * * * * * * * * * * * * * * * * * * */
  DWORD dwSrcSize = ((iShotWidth * hBmpInfo.biBitCount + 31) / 32) * 4 * iShotHeight;
  
  //��ͼ�ܴ�С
  DWORD dwPicSize = HEAD_SIZE + dwSrcSize;

  //BMPͼ���ļ�ͷ
  BITMAPFILEHEADER hBmpFile;
                   hBmpFile.bfSize      = dwPicSize;
                   hBmpFile.bfType      = TYPE_BMP;
                   hBmpFile.bfOffBits   = HEAD_SIZE;
                   hBmpFile.bfReserved1 = MUST_ZERO;
                   hBmpFile.bfReserved2 = MUST_ZERO;

  //BMPͼ������Դ
  char *bmpSrc = new char[dwSrcSize];
  ZeroMemory(bmpSrc, dwSrcSize);

  //����ָ���ļ���λͼ�е�����λԪ����
  //�����Ƶ�ָ����ʽ���豸�޹�λͼ�Ļ�����
  GetDIBits(hMemDC, hBmp, 0, (UINT)iShotHeight, bmpSrc, (BITMAPINFO*)&hBmpInfo, DIB_RGB_COLORS);

  //��������������Ϣ
  char *szBmp = new char[dwPicSize];
  ZeroMemory(szBmp, dwPicSize);
  memcpy(szBmp, (void*)&hBmpFile, FILE_HEAD);
  memcpy(szBmp + FILE_HEAD, (void*)&hBmpInfo, INFO_HEAD);
  memcpy(szBmp + HEAD_SIZE, bmpSrc, dwSrcSize);

  //����BMPͼ��
  FILE *hFile = fopen(szSavePath, "wb+");
  if (nullptr != hFile)
  {
    size_t count = fwrite(szBmp, 1, dwPicSize, hFile);
    fclose(hFile);
  }

  //�ͷ���Դ
  DeleteObject(hBmp);
  DeleteObject(hMemDC);
  ReleaseDC(NULL, hCurrScreen);
  delete[] szBmp;
  delete[] bmpSrc;
  szBmp  = nullptr;
  bmpSrc = nullptr;
  return true;
}

bool common::winutil::WndGetShotRect(HWND hWnd, ShotRect &ShotInfo)
{
  if (NULL == hWnd)
  {
    return false;
  }

  //��ȡ���ھ��νṹ
  RECT wndRect;
  GetWindowRect(hWnd, &wndRect);

  //���ڴ�С��Ϣ
  ShotInfo.x_start = wndRect.left;
  ShotInfo.y_start = wndRect.top;
  ShotInfo.x_end = wndRect.right;
  ShotInfo.y_end = wndRect.bottom;
  ShotInfo.rect_width = wndRect.right - wndRect.left;
  ShotInfo.rect_height = wndRect.bottom - wndRect.top;

  return true;
}

bool common::winutil::SetWndTop(HWND hWnd, bool isTop)
{
  bool retVal = false;

  if (isTop)
  {
    retVal = SetWindowPos(hWnd,
                          HWND_TOPMOST,
                          0, 0, 0, 0,
                          SWP_ASYNCWINDOWPOS | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
  }
  else
  {
    retVal = SetWindowPos(hWnd,
                          HWND_NOTOPMOST,
                          0, 0, 0, 0,
                          SWP_ASYNCWINDOWPOS | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
  }

  return retVal;
}

HWND common::winutil::GetWndByClsAndName(const TCHAR* szWndCls, const TCHAR* szWndName)
{
  return FindWindow(szWndCls, szWndName);
}

void common::winutil::WndGetShotcut(HWND hWnd, const char *szSavePath)
{
  common::winutil::SetWndTop(hWnd, true);

  //�ȴ����ڳ����ٽ�ͼ
  Sleep(200);

  common::winutil::ShotRect ShotPos;
  common::winutil::WndGetShotRect(hWnd, ShotPos);

  common::winutil::ScreenShot(szSavePath, &ShotPos);

  common::winutil::SetWndTop(hWnd, false);
}

void common::winutil::SendWndMouseClickL(HWND hWnd, Pos clickPos)
{
  LPARAM pos = MAKELONG(clickPos.x,clickPos.y);

  SendMessage(hWnd, WM_LBUTTONDOWN, NULL, pos);
  Sleep(50);
  SendMessage(hWnd, WM_LBUTTONUP, NULL, pos);
}

/*
  #include <TlHelp32.h>

  HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

  PROCESSENTRY32 lppe;
  lppe.dwSize = sizeof(PROCESSENTRY32);

  Process32First(hSnapshot, &lppe);

  DWORD dwPid;

  while (true)
  {
    std::wstring processName = (wchar_t*)lppe.szExeFile;

    if (processName == L"TIM.exe")
    {
      dwPid = lppe.th32ProcessID;
      break;
    }

    if (!Process32Next(hSnapshot, &lppe))
    {
      break;
    }
  }
*/

#endif