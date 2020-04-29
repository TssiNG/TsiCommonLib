#ifndef _TSI_WIN_UTIL_
#define _TSI_WIN_UTIL_

#ifdef _WIN32
#include <Windows.h>

#pragma warning(disable:4996)

namespace common
{
namespace winutil
{

#define TAG_DEV_PLAS  1
#define BITS_PER_PIX  32
#define NO_COLOR_TAB  0
#define UNCMP_RGB     0
#define H_RESOL_0     0
#define V_RESOL_0     0
#define ALL_COLOR     0

#define MUST_ZERO     0
#define TYPE_BMP      0x4D42

#define FILE_HEAD     sizeof(BITMAPFILEHEADER)
#define INFO_HEAD     sizeof(BITMAPINFOHEADER)
#define HEAD_SIZE     sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER)

struct ShotRect
{
  ShotRect()
  {
    x_start     = 0;
    y_start     = 0;
    x_end       = 0;
    y_end       = 0;
    rect_width  = 0;
    rect_height = 0;
  }

  int x_start;
  int y_start;
  int x_end;
  int y_end;
  int rect_width;
  int rect_height;
};

bool ScreenShot(const char *szSavePath, const ShotRect *ShotInfo = nullptr);

bool WindowGetShotInfo(HWND hWnd, common::winutil::ShotRect& ShotInfo);

bool SetWindowTop(HWND hWnd, bool isTop);

}
}


#endif

#endif