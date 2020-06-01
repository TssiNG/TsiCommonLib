#ifndef _UNIX_UTIL_
#define _UNIX_UTIL_

#ifdef __unix__
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#include <iostream>
#include <string>

namespace common
{
namespace unix
{

typedef struct
{
  std::string _bash;
  std::string _sh;
}ShellSignal;

void signal_to_str(const int _bash_sg, ShellSignal &_signal, );

void get_cmd_result(const std::string &cmd, std::string result);

void send_proc_signal(const std::string &proc_name, int sys_signal);

}
}

#endif

#endif