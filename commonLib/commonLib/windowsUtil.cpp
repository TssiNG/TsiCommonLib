#include "pch.h"
#include "windowsUtil.h"
#include <stdio.h>

#ifdef _WIN32

#include <tchar.h>

bool common::winutil::ScreenShot(const char* szSavePath)
{
  //��ʾ����Ļ
  //HDC hCurrScreen = GetDC(NULL);
  HDC hCurrScreen = CreateDC(_T("display"),NULL,NULL,NULL);

  //����һ�����ݵ�DC,���ڴ��б�ʾ��ǰλͼ��������
  HDC hCmpDC = CreateCompatibleDC(hCurrScreen);

  //���
  int iScreenWidth  = GetDeviceCaps(hCurrScreen, HORZRES);
  int iScreenHeight = GetDeviceCaps(hCurrScreen, VERTRES);

  //��ǰ��Ļλͼ
  HBITMAP hBmp = CreateCompatibleBitmap(hCurrScreen, iScreenWidth, iScreenHeight);

  //�õ�ǰλͼ�����ʾ�ڴ�����Ļλͼ������
  SelectObject(hCmpDC,hBmp);

  //����ǰ��Ļͼ���Ƶ��ڴ���
  BOOL ret = BitBlt(hCmpDC, 0, 0, iScreenWidth, iScreenHeight, hCurrScreen, 0, 0, SRCCOPY);

  //BMPͼ����Ϣͷ
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

  //����Դ��С
  DWORD dwSrcSize = ((iScreenWidth * hBmpInfo.biBitCount + 31) / 32) * 4 * iScreenHeight;
  
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
  GetDIBits(hCmpDC, hBmp, 0, (UINT)iScreenHeight, bmpSrc, (BITMAPINFO*)&hBmpInfo, DIB_RGB_COLORS);

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
  ReleaseDC(NULL, hCmpDC);
  ReleaseDC(NULL,hCurrScreen);
  delete[] szBmp;
  delete[] bmpSrc;
  szBmp  = nullptr;
  bmpSrc = nullptr;
  return true;
}

#endif