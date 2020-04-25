#include "pch.h"
#include "strLib.h"

void common::str::strReplace(std::string &src, const char *from, const char *to)
{
  size_t sizeFrom = strlen(from);
  size_t sizeTo   = strlen(to);
  size_t curPos   = src.find(from, 0);

  while (std::string::npos != curPos)
  {
    src.replace(curPos, sizeFrom, to, sizeTo);
    curPos = src.find(from, curPos + sizeTo);
  }
}

double common::str::sci2db(const std::string &strSci)
{
  int    iPower       = 0;  //ÃÝ
  double dMntsa       = 0;  //Î²Êý
  double dCoefficient = 1;  //ÏµÊý

  std::string strPower, strMntsa;

  if (std::string::npos == strSci.find("E"))
  {
    return atof(strSci.c_str());
  }

  strMntsa = strSci.substr(0, strSci.find("E"));
  strPower = strSci.substr(strSci.find("E") + 1);

  dMntsa = atof(strMntsa.c_str());
  iPower = atoi(strPower.c_str());

  while (iPower != 0)
  {
    if (iPower > 0)
    {
      dCoefficient *= 10;
      iPower--;
    }
    else
    {
      dCoefficient *= 0.1;
      iPower++;
    }
  }

  return dMntsa * dCoefficient;
}