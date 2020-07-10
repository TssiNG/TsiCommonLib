#include "tsiStr.h"

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
  int    iPower       = 0;  //幂
  double dMntsa       = 0;  //尾数
  double dCoefficient = 1;  //系数

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

std::string common::str::byte2str(BYTE val)
{
  std::string ret      = "";
  size_t      high_bit = val / 16;
  size_t      low_bit  = val % 16;

  ret += bit_hex_to_str(high_bit);
  ret += bit_hex_to_str(low_bit);

  return ret;
}

std::string common::str::word2str(WORD val)
{
  std::string ret = "";

  BYTE high_8_bit = 0xFF & (val >> 8);
  BYTE low_8_bit  = 0xFF & val;

  ret += bit_hex_to_str(high_8_bit / 16);
  ret += bit_hex_to_str(high_8_bit % 16);
  ret += bit_hex_to_str(low_8_bit / 16);
  ret += bit_hex_to_str(low_8_bit % 16);

  return ret;
}

std::string common::str::dw2str(DWORD val)
{
  return "";
}

std::string common::str::bit_hex_to_str(size_t bit)
{
  std::string ret;

  switch (bit)
  {
    case 0:
      ret = "0";
      break;
    case 1:
      ret = "1";
      break;
    case 2:
      ret = "2";
      break;
    case 3:
      ret = "3";
      break;
    case 4:
      ret = "4";
      break;
    case 5:
      ret = "5";
      break;
    case 6:
      ret = "6";
      break;
    case 7:
      ret = "7";
      break;
    case 8:
      ret = "8";
      break;
    case 9:
      ret = "9";
      break;
    case 10:
      ret = "A";
      break;
    case 11:
      ret = "B";
      break;
    case 12:
      ret = "C";
      break;
    case 13:
      ret = "D";
      break;
    case 14:
      ret = "E";
      break;
    case 15:
      ret = "F";
      break;
    default:
      ret = "";
  }

  return ret;
}