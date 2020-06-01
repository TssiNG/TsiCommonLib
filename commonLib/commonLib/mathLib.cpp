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