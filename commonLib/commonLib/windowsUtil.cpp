#include "pch.h"
#include "windowsUtil.h"
#include <stdio.h>

#ifdef _WIN32

#include <tchar.h>

bool common::winutil::ScreenShot(const char* szSavePath)
{
  //显示器屏幕
  //HDC hCurrScreen = GetDC(NULL);
  HDC hCurrScreen = CreateDC(_T("display"),NULL,NULL,NULL);

  //创建一个兼容的DC,在内存中表示当前位图的上下文
  HDC hCmpDC = CreateCompatibleDC(hCurrScreen);

  //宽高
  int iScreenWidth  = GetDeviceCaps(hCurrScreen, HORZRES);
  int iScreenHeight = GetDeviceCaps(hCurrScreen, VERTRES);

  //当前屏幕位图
  HBITMAP hBmp = CreateCompatibleBitmap(hCurrScreen, iScreenWidth, iScreenHeight);

  //用当前位图句柄表示内存中屏幕位图上下文
  SelectObject(hCmpDC,hBmp);

  //将当前屏幕图像复制到内存中
  BOOL ret = BitBlt(hCmpDC, 0, 0, iScreenWidth, iScreenHeight, hCurrScreen, 0, 0, SRCCOPY);

  //BMP图像信息头
  BITMAPINFOHEADER hBmpInfo;
                   hBmpInfo.biSize          = INFO_HEAD;
                   hBmpInfo.biWidth         = iScreenWidth;
                   hBmpInfo.biHeight        = iScreenHeight;
                   hBmpInfo.biPlanes        = TAG_DEV_PLAS;
                   hBmpInfo.biClrUsed       = NO_COLOR_TAB;
                   hBmpInfo.biBitCount      = BITS_PER_PIX;
                   hBmpInfo.biSizeImage     = UNCMP_RGB;
                   hBmpInfo.biCompression   = BI_RGB;
                   hBmpInfo.biClrImportant  = ALL_COLOR;
                   hBmpInfo.biXPelsPerMeter = H_RESOL_0;
                   hBmpInfo.biYPelsPerMeter = V_RESOL_0;

  //数据源大小
  DWORD dwSrcSize = ((iScreenWidth * hBmpInfo.biBitCount + 31) / 32) * 4 * iScreenHeight;
  
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
  GetDIBits(hCmpDC, hBmp, 0, (UINT)iScreenHeight, bmpSrc, (BITMAPINFO*)&hBmpInfo, DIB_RGB_COLORS);

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
  ReleaseDC(NULL, hCmpDC);
  ReleaseDC(NULL,hCurrScreen);
  delete[] szBmp;
  delete[] bmpSrc;
  szBmp  = nullptr;
  bmpSrc = nullptr;
  return true;
}

#endif