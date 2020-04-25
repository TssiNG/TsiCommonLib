#ifndef _TSI_WIN_UTIL_
#define _TSI_WIN_UTIL_

#ifdef _WIN32
#include <Windows.h>

namespace common
{
namespace winutil
{

bool screen_shot(const char *save_path);

}
}


#endif

#endif