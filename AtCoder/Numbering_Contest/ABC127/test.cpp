#include <iostream>
#include <string>
#include <set>

int main()
{
  // (1)
  {
    std::multiset<std::string> s = { "A", "B", "B", "C", "D" };

    // B以上D以下の範囲を取得
    decltype(s)::iterator it = s.lower_bound("C");
    decltype(s)::iterator last = --s.begin();

    while (it != last) {
      std::cout << *it << std::endl;
      --it;
    }
    std::cout << std::endl;
  }


}