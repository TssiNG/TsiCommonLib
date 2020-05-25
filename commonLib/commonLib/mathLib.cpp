#include "pch.h"
#include "mathLib.h"

size_t common::math::fibonacci(size_t idx)
{
  if (0 >= idx)
  {
    return 0;
  }
  else if (2 >= idx)
  {
    return idx;
  }

  return (fibonacci(idx - 1) + fibonacci(idx - 2));
}