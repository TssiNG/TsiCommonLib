#include "tsiMath.h"

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

//折半插入排序 : 时间复杂度为n^2
void common::math::insert_sort(_Array &arr)
{
  for (size_t idx = 0; idx < arr.size(); ++idx)
  {
    size_t curr_val    = arr[idx];      //当前索引值
    size_t curr_pos    = idx;           //当前索引初始位置
    size_t compare_pos = curr_pos / 2;  //比较索引初始位置
    bool   needInsert  = false;         //是否需要插入当前值

    while (true)
    {
      //同一位置不比较
      if (curr_pos == compare_pos) break;

      if (curr_val < arr[compare_pos])
      {
        //将当前位移动至比较位, 下一个比较位为当前位折半
        curr_pos    = compare_pos;
        compare_pos = curr_pos / 2;
        needInsert  = true;
      }
      else
      {
        //当前比较位为当前位的前一位则退出
        if (compare_pos == (curr_pos - 1)) break;

        //下一个比较位为当前位到当前比较位之间折半
        compare_pos = (compare_pos + curr_pos) / 2;
      }
    }

    if (needInsert)
    {
      //将当前值插入到当前索引位
      arr.erase(arr.begin() + idx);
      arr.insert(arr.begin() + curr_pos, curr_val);
    }
  }
}

//归并排序 : 时间复杂度为nlogn
void common::math::merge_sort(_Array &arr)
{
  
}

//堆排序 : 时间复杂度为nlogn
void common::math::heap_sort(_Array& arr)
{

}