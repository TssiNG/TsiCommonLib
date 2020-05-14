#ifndef _TSI_STRING_
#define _TSI_STRING_

#include <string>

#ifdef WIN32
#include <Windows.h>
#else
typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned long  DWORD;
#endif

namespace common
{
namespace str
{
void strReplace(std::string &src, const char *from, const char *to);

double sci2db(const std::string &strSci);

std::string byte2str(BYTE val);

std::string word2str(WORD val);

std::string dw2str(DWORD val);

std::string bit_hex_to_str(size_t bit);
}
}

#endif