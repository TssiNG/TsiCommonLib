#include <stdarg.h>

#include "tsiStr.h"
#include "tsiTime.h"
#include "tsiFile.h"
#include "tsiThread.h"

namespace common
{
namespace log
{

#define LOG_FATAL 0
#define LOG_ERROR 1
#define LOG_WARN  2
#define LOG_INFO  3
#define LOG_DEBUG 4
#define LOG_TRACE 5

typedef struct
{
  size_t      msg_level;
  time_t      msg_time;
  std::string msg_main;
  std::vector<std::string> msg_param;
}stLog_record;

class CRecorder
{
public:
  CRecorder();
  ~CRecorder();

  bool generate_record(size_t level, time_t time, std::string msg);
  stLog_record get_record();
  void remove_record();

private:
  std::mutex m_mtx_queue;
  std::queue<stLog_record> m_record_queue;
};

class CFilter
{
public:
  CFilter();
  ~CFilter();

  bool check_record(size_t log_level);

private:
  size_t m_log_level;
};

class CFormater
{
public:
  CFormater();
  ~CFormater();

  std::string generate_level_str(size_t level);
  std::string generate_time_str(time_t time);
  std::string format_msg(stLog_record record);

private:
  std::string m_log_msg;
};

class CPrinter
{
public:
  CPrinter();
  ~CPrinter();

private:
  std::mutex    m_mtx_log;
  std::ofstream m_os_log;
};

class CTsiLog
{
public:
  CTsiLog();
  ~CTsiLog();

  void log_msg(std::string msg,...);

private:
  CRecorder m_recorder;
  CFilter   m_filter;
  CFormater m_formater;
  CPrinter  m_printer;
};

}
}