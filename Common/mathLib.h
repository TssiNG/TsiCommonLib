#ifndef _TSI_MATH_LIB_
#define _TSI_MATH_LIB_

#include <vector>

using _Array  = std::vector<size_t>;
using _Matrix = std::vector<std::vector<size_t>>;

namespace common
{
namespace math
{

size_t rec_fibonacci(int idx);

size_t dp_fibonacci(int idx);

long long dicotomy_arr_peak(_Array peak_arr);

long long dicotomy_mat_peak(_Matrix peak_mat);

}
}


#endif