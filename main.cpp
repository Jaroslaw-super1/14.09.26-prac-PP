#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <cstdlib>
#include <future>
#include <functional>
#include <algorithm>

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





  data_t values(size, 1);
  size_t v_size = values.size();

  const std::size_t chunk = v_size / threads;
  const std::size_t rem = v_size % threads;


  std::vector< size_t > times;



  for (size_t r = 0; r < 5; r++)
  {
    Clicker cl;
    
    init = cl.millisec();

    std::vector< std::future< value_t > > futures;
    futures.reserve(threads);


    size_t begin = 0;

    for (size_t i = 0; i < threads; ++i)
    {
      const size_t end = begin + chunk + (i < rem ? 1 : 0);

      futures.emplace_back(std::async(std::launch::async, sum_range, std::cref(values), begin, end));

      begin = end;
    }

    for (auto & f : futures)
    {
      sum += f.get();
    }

    times.push_back(cl.millisec());
    total = cl.millisec();

    std::cout << total - init << ' ' << sum << '\n';

    sum = 0;
  }

  std::cout << '\n';

  std::sort(times.begin(), times.end());

  size_t summ = 0;

  for (size_t i = 0; i < 5; i++)
  {
    summ += times[i];
    std::cout << times[i] << '\n';
  }

  std::cout << '\n' << summ << '\n';
  std::cout << '\n' << times[2] << '\n';
}