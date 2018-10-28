#include "../src/method.hh"

#include <benchmark/benchmark.h>
#include <string>
#include <unordered_map>

using namespace jambe;

static std::vector<std::string> methods =
{
  "GET",
  "POST",
  "PUT",
  "DELETE",
  "HEAD",
  "PATCH",
};

static std::unordered_map<std::string, Method> methods_map =
{
  { "GET", Method::GET },
  { "POST", Method::POST },
  { "PUT", Method::PUT },
  { "DELETE", Method::DELETE },
  { "HEAD", Method::HEAD },
  { "PATCH", Method::PATCH },
};

static void to_method_switch(benchmark::State& state)
{
  for (auto _ : state)
  {
    const std::string& str = methods[state.range(0)];
    Method m;
    if (str == "GET")
      m = Method::GET;
    else if (str == "POST")
      m = Method::POST;
    else if (str == "PUT")
      m = Method::PUT;
    else if (str == "DELETE")
      m = Method::DELETE;
    else if (str == "HEAD")
      m = Method::HEAD;
    else if (str == "PATCH")
      m = Method::PATCH;
  }
}
BENCHMARK(to_method_switch)->Arg(0)->Arg(1)->Arg(2)->Arg(3)->Arg(4)->Arg(5);

static void to_method_map(benchmark::State& state)
{
  for (auto _ : state)
  {
    const std::string& str = methods[state.range(0)];
    Method m = methods_map[str];
  }
}
BENCHMARK(to_method_map)->Arg(0)->Arg(1)->Arg(2)->Arg(3)->Arg(4)->Arg(5);
