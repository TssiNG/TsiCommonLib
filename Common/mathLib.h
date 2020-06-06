#ifndef _TSI_MATH_LIB_
#define _TSI_MATH_LIB_

#include <vector>

using _Array  = std::vector<size_t>;
using _Matrix = std::vector<std::vector<size_t>>;

#define _LAST(x) x - 1
#define _NEXT(x) x + 1

namespace common
{
namespace math
{

size_t rec_fibonacci(int idx);

size_t dp_fibonacci(int idx);

long long dicotomy_arr_peak(const _Array arr, size_t _mid_idx = -1);

void insert_sort(const _Array &arr);

void merge_sort(const _Array &arr);

void heap_sort(const _Array &arr);

}
}


#endif