#include <iostream>
#include <chrono>
#include <string>
#include <vector>

class Clicker
{
public:
  Clicker():
  start_(std::chrono::high_resolution_clock::now())
  {}

  double millisec() const {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;
    auto t = high_resolution_clock::now();
    return duration_cast< milliseconds >(t - start_).count();
  }
private:
  std::chrono::time_point< std::chrono::steady_clock > start_;
};

using data_t = std::vector< unsigned long long >;
using value_t = data_t::value_type;

int main(int argc, char ** argv)
{
  constexpr size_t size{1'000'000'000};
  double init{0}, total{0};
  value_t sum{0};
  {
    mtt::Clicker cl;
    data_t values(size, 1);
    init = cl.millisec();
    for (size_t i = 0; i < values.size(); ++i)
    {
      sum += values[i];
    }
    total = cl.millisec();
  }
}