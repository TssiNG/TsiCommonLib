#include "pch.h"
#include "mathLib.h"

size_t common::math::rec_fibonacci(int idx)
{
  if (0 >= idx) return 0;
  if (2 >= idx) return idx;

  return (rec_fibonacci(idx - 1) + rec_fibonacci(idx - 2));
}

size_t common::math::dp_fibonacci(int idx)
{
  if (0 >= idx) return 0;
  if (2 >= idx) return idx;

  std::vector<size_t> fibonacci;
  fibonacci.push_back(1);
  fibonacci.push_back(2);

  size_t pre_last_num, last_num, curr_num;

  pre_last_num = fibonacci[0];
  last_num     = fibonacci[1];

  for (size_t i = 2; i < idx; ++i)
  {
    curr_num     = pre_last_num + last_num;
    pre_last_num = last_num;
    last_num     = curr_num;

    fibonacci.push_back(curr_num);
  }

  return fibonacci[idx - 1];
}

//二分法查找峰值 : 时间复杂度为logn
long long common::math::dicotomy_arr_peak(const _Array arr, size_t _curr)
{
  size_t _end_idx = arr.size() - 1;
  
  if (arr.empty())     return 0;
  if (arr.size() == 1) return arr[0];
  if (arr.size() == 2) return arr[0] >= arr[1] ? arr[0] : arr[1];

  //初始索引为-1
  if (_curr == -1)
  {
    _curr  = _end_idx / 2;
  }
  
  //首尾直接返回
  if (0 == _curr || _end_idx == _curr) return arr[_curr];

  _Array dicotomy_arr = arr;

  //当前索引值小于前一个索引值, 移除当前索引值之后的所有元素
  if (arr[_curr] < arr[_LAST(_curr)])
  {
    dicotomy_arr.erase(dicotomy_arr.begin() + _curr, dicotomy_arr.end());

    _curr = (dicotomy_arr.size() - 1) / 2;

    return dicotomy_arr_peak(dicotomy_arr, _curr);
  }
  
  //当前索引值小于后一个索引值, 移除当前索引值之前的所有元素
  if (arr[_curr] < arr[_NEXT(_curr)])
  {
    dicotomy_arr.erase(dicotomy_arr.begin(), dicotomy_arr.begin() + _curr);

    _curr = (dicotomy_arr.size() - 1) / 2;

    return dicotomy_arr_peak(dicotomy_arr, _curr);
  }

  return arr[_curr];
}

void common::math::insert_sort(const _Array &arr)
{
  //插入排序 : 时间复杂度为nlogn
}

void common::math::merge_sort(const _Array &arr)
{
  //归并排序 : 时间复杂度为nlogn
}