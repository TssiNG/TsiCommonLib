#include "tsiWindows.h"

#ifdef _WIN32

bool common::winutil::ScreenShot(const char* szSavePath, const ShotRect *ShotInfo)
{
  //显示器屏幕
  HDC hCurrScreen = GetDC(NULL);

  //创建一个兼容的DC,在内存中表示当前位图的上下文
  HDC hMemDC = CreateCompatibleDC(hCurrScreen);

  //宽高
  int iShotWidth,iShotHeight;
  
  //截图开始坐标
  int iShotStartX,iShotStartY;

  //不指定区域则截取全屏幕
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

  //当前屏幕位图
  HBITMAP hBmp = CreateCompatibleBitmap(hCurrScreen, iShotWidth, iShotHeight);

  //用当前位图句柄表示内存中屏幕位图上下文
  SelectObject(hMemDC,hBmp);

  //将当前屏幕图像复制到内存中
  BOOL ret = BitBlt(hMemDC, 0, 0, iShotWidth, iShotHeight, hCurrScreen, iShotStartX, iShotStartY, SRCCOPY);

  //BMP图像信息头
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
   * Windows按4字节分配内存
   * 首先计算每行所需要的bit数,并按4字节对齐
   * 在对对齐后的数据乘4,从DWORD转为BYTE
   * 每行实际所占BYTE乘图像列数得到数据源大小
   * * * * * * * * * * * * * * * * * * * */
  DWORD dwSrcSize = ((iShotWidth * hBmpInfo.biBitCount + 31) / 32) * 4 * iShotHeight;
  
  //截图总大小
  DWORD dwPicSize = HEAD_SIZE + dwSrcSize;

  //BMP图像文件头
  BITMAPFILEHEADER hBmpFile;
                   hBmpFile.bfSize      = dwPicSize;
                   hBmpFile.bfType      = TYPE_BMP;
                   hBmpFile.bfOffBits   = HEAD_SIZE;
                   hBmpFile.bfReserved1 = MUST_ZERO;
                   hBmpFile.bfReserved2 = MUST_ZERO;

  //BMP图像数据源
  char *bmpSrc = new char[dwSrcSize];
  ZeroMemory(bmpSrc, dwSrcSize);

  //检索指定的兼容位图中的所有位元数据
  //并复制到指定格式的设备无关位图的缓存中
  GetDIBits(hMemDC, hBmp, 0, (UINT)iShotHeight, bmpSrc, (BITMAPINFO*)&hBmpInfo, DIB_RGB_COLORS);

  //汇总所有数据信息
  char *szBmp = new char[dwPicSize];
  ZeroMemory(szBmp, dwPicSize);
  memcpy(szBmp, (void*)&hBmpFile, FILE_HEAD);
  memcpy(szBmp + FILE_HEAD, (void*)&hBmpInfo, INFO_HEAD);
  memcpy(szBmp + HEAD_SIZE, bmpSrc, dwSrcSize);

  //保存BMP图像
  FILE *hFile = fopen(szSavePath, "wb+");
  if (nullptr != hFile)
  {
    size_t count = fwrite(szBmp, 1, dwPicSize, hFile);
    fclose(hFile);
  }

  //释放资源
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

  //获取窗口矩形结构
  RECT wndRect;
  GetWindowRect(hWnd, &wndRect);

  //窗口大小信息
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

  //等待窗口出来再截图
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