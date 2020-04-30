#ifndef _TSI_TIME_
#define _TSI_TIME_

#include <chrono>

#ifdef _WIN32
#include <time.h>
#include <WinSock2.h>
#pragma comment (lib,"ws2_32.lib")
#else
#include <sys/time.h>
#endif

namespace common
{
namespace time
{

//stamp format : "y-m-d h:m:s.ms"
char* get_time_stamp();


}
}

/*
+------------------------------------------------------------------------------------+
|                         multi platform <time.h> interface                          |
+--------+-------------------------------+-------------------------------------------+
| retVal |          definition           |                   usage                   |
+--------+-------------------------------+-------------------------------------------+
| tm*    | gmtime(time_t time)           | translate time_t to GMT time              |
+--------+-------------------------------+-------------------------------------------+
| tm*    | localtime(time_t time)        | translate time_t to local time            |
+--------+-------------------------------+-------------------------------------------+
| char*  | ctime(time_t time)            | translate time_t to char* (time_t format) |
+--------+-------------------------------+-------------------------------------------+
| char*  | asctime(tm* time)             | translate tm to char*     (tm format)     |
+--------+-------------------------------+-------------------------------------------+
| time_t | mktime(tm* time)              | translate tm to time_t    (tm format)     |
+--------+-------------------------------+-------------------------------------------+
| time_t | time(time_t* time)            | return local time                         |
+--------+-------------------------------+-------------------------------------------+
| double | difftime(time_t t1,time_t t2) | return the diff sec between t1 and t2     |
+------------------------------------------------------------------------------------+


+-----------------------------------------------------------------------------+
|                         definition of struct tm                             |
+---------------+-------------------------------------------------------------+
|    members    |                          meaning                            |
+---------------+-------------------------------------------------------------+
|  int tm_sec   |  seconds after the minute - [0, 60] including leap second   |
+---------------+-------------------------------------------------------------+
|  int tm_min   |  minutes after the hour - [0, 59]                           |
+---------------+-------------------------------------------------------------+
|  int tm_hour  |  hours since midnight - [0, 23]                             |
+---------------+-------------------------------------------------------------+
|  int tm_mday  |  day of the month - [1, 31]                                 |
+---------------+-------------------------------------------------------------+
|  int tm_mon   |  months since January - [0, 11]                             |
+---------------+-------------------------------------------------------------+
|  int tm_year  |  years since 1900                                           |
+---------------+-------------------------------------------------------------+
|  int tm_wday  |  days since Sunday - [0, 6]                                 |
+---------------+-------------------------------------------------------------+
|  int tm_yday  |  days since January 1 - [0, 365]                            |
+---------------+-------------------------------------------------------------+
|  int tm_isdst |  daylight savings time flag                                 |
+---------------+-------------------------------------------------------------+


+--------------------------------------+
|       related struct or type         |
+-----------+--------------------------+
|   type    |       description        |
+-----------+--------------------------+
|  time_t   |  seconds since 1970s     |
+-----------+--------------------------+
|  timeval  |  ms since 1970s          |
+-----------+--------------------------+
|    tm     |  time stamp since 1900s  |
+-----------+--------------------------+

*/

#endif