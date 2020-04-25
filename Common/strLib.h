#ifndef _TSI_STRING_
#define _TSI_STRING_

#include <string>

namespace common
namespace str
{
void strReplace(std::string &src, const char *from, const char *to);

double sci2db(const std::string &strSci);
}
}

#endif