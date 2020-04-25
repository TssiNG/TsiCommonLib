#include "pch.h"
#include "windowsUtil.h"

#ifdef _WIN32

bool common::winutil::screen_shot(const char* save_path)
{
  HBITMAP hBitmap;

  HDC hScreenDC = CreateDC(L"display",NULL,NULL,NULL);

  return true;
}

/*
HBITMAP ScreenCapture(LPSTR filename,WORD BitCount,LPRECT lpRect)
{
    HBITMAP hBitmap;
    //显示器屏幕DC
    HDC hScreenDC=CreateDC("display",NULL,NULL,NULL);
    HDC hmenDC=CreateCompatibleDC(hScreenDC);
    //显示器屏幕的宽和高
    int ScreenWidth=GetDeviceCaps(hScreenDC,HORZRES);
    int ScreenHeight=GetDeviceCaps(hScreenDC,VERTRES);

    HBITMAP hOldBM;
    //保存位图数据
    PVOID lpvpxldata;
    //截取获取的长度及起点
    INT ixStart;
    INT iyStart;
    INT iX;
    INT iY;
    //位图数据大小
    DWORD dwBitmapArraySize;

    DWORD nBitsOffset;
    DWORD lImageSize;
    DWORD lFileSize;

    BITMAPINFO bmInfo;

    BITMAPFILEHEADER bmFileHeader;
    HANDLE hbmfile;
    DWORD dwWritten;

    if(lpRect==NULL)
    {
        ixStart=iyStart=0;
        iX=ScreenWidth;
        iY=ScreenHeight;
    }
    else
    {
        ixStart=lpRect->left;
        iyStart=lpRect->top;
        iX=lpRect->right - lpRect->left;
        iY=lpRect->bottom - lpRect->top;
    }
    hBitmap=CreateCompatibleBitmap(hScreenDC,iX,iY);
    hOldBM=(HBITMAP)SelectObject(hmenDC,hBitmap);
    BitBlt(hmenDC,0,0,iX,iY,hScreenDC,ixStart,iyStart,SRCCOPY);
    hBitmap=(HBITMAP)SelectObject(hmenDC,hOldBM);
    if(filename==NULL)
    {
        DeleteDC(hScreenDC);
        DeleteDC(hmenDC);
        return hBitmap;
    }

    dwBitmapArraySize = ((((iX*32)+31)&~31)>>3)*iY;
    lpvpxldata=HeapAlloc(GetProcessHeap(),HEAP_NO_SERIALIZE,dwBitmapArraySize);
    ZeroMemory(lpvpxldata,dwBitmapArraySize);

    ZeroMemory(&bmInfo,sizeof(BITMAPINFO));
    bmInfo.bmiHeader.biSize=sizeof(PBITMAPINFOHEADER);
    bmInfo.bmiHeader.biWidth=iX;
    bmInfo.bmiHeader.biHeight=iY;
    bmInfo.bmiHeader.biPlanes=1;
    bmInfo.bmiHeader.biBitCount=BitCount;
    bmInfo.bmiHeader.biClrImportant=BI_RGB;

    ZeroMemory(&bmFileHeader,sizeof(BITMAPFILEHEADER));
    nBitsOffset=sizeof(BITMAPFILEHEADER)+bmInfo.bmiHeader.biSize;
    lImageSize=((((bmInfo.bmiHeader.biWidth*bmInfo.bmiHeader.biBitCount)+31)& ~31)>>3)*bmInfo.bmiHeader.biHeight;
    lFileSize=nBitsOffset+lImageSize;
    bmFileHeader.bfOffBits=nBitsOffset;

    GetDIBits(hmenDC,hBitmap,0,bmInfo.bmiHeader.biHeight,lpvpxldata,&bmInfo,DIB_RGB_COLORS);
    hbmfile=CreateFile(filename,GENERIC_WRITE,FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

    if(hbmfile==INVALID_HANDLE_VALUE)
    {
        MessageBox(NULL,"create file error","error",MB_OK);
    }
    WriteFile(hbmfile,&bmFileHeader,sizeof(BITMAPCOREHEADER),&dwWritten,NULL);
    WriteFile(hbmfile,&bmInfo,sizeof(BITMAPINFO),&dwWritten,NULL);
    WriteFile(hbmfile,lpvpxldata,lImageSize,&dwWritten,NULL);
    CloseHandle(hbmfile);


    HeapFree(GetProcessHeap(),HEAP_NO_SERIALIZE,lpvpxldata);
    ReleaseDC(0,hScreenDC);
    DeleteDC(hmenDC);
    return hBitmap;
}
*/

#endif