#ifndef PAIR_HPP_
#define PAIR_HPP_

template <typename T1, typename T2>
class Pair
{
public:
  T1 first;
  T2 second;
  Pair(const T1 &first, const T2 &second) : first(first), second(second) {}
};

#endif