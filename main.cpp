#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <cstdlib>
#include <future>

class Clicker
{
public:
  Clicker():
  start_(std::chrono::high_resolution_clock::now())
  {}

  double millisec() const
  {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;
    auto t = high_resolution_clock::now();
    return duration_cast< milliseconds >(t - start_).count();
  }
private:
  std::chrono::time_point< std::chrono::high_resolution_clock > start_;
};

using data_t = std::vector< unsigned long long >;
using value_t = data_t::value_type;


value_t sum_range(const data_t & data, size_t begin, size_t end)
{
  value_t s = 0;
  for (size_t j = begin; j < end; ++j)
  {
    s += data[j];
  }
  return s;
}


int main(int argc, char ** argv)
{
  constexpr size_t size{1'000'000'000};

  const size_t threads = std::stoul(argv[1]);

  double init{0}, total{0};
  value_t sum{0};

  {
    Clicker cl;
    data_t values(size, 1);
    size_t v_size = values.size();

    init = cl.millisec();

    const std::size_t chunk = v_size / threads;
    const std::size_t rem   = v_size % threads;

    std::vector< std::future< value_t > > futures;
    futures.reserve(threads);







    for (size_t i = 0; i < values.size(); ++i)
    {
      sum += values[i];
    }
    total = cl.millisec();
  }

  std::cout << total - init << '\n';
}