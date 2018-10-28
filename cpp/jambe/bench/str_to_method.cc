#include "../src/method.hh"

#include <benchmark/benchmark.h>
#include <string>
#include <cstring>
#include <unordered_map>

using namespace jambe;

static std::array<std::string, JAMBE_METHOD_NB> methods_str =
{
  "GET",
  "POST",
  "PUT",
  "DELETE",
  "HEAD",
  "PATCH",
};

static std::array<const char*, JAMBE_METHOD_NB> methods_cstr =
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

static void to_method_switch_cstr(benchmark::State& state)
{
  for (auto _ : state)
  {
    const std::string& str = methods_str[state.range(0)];
    Method m;
    if (std::strcmp(str.data(), "GET") == 0)
      m = Method::GET;
    else if (std::strcmp(str.data(), "POST") == 0)
      m = Method::POST;
    else if (std::strcmp(str.data(), "PUT") == 0)
      m = Method::PUT;
    else if (std::strcmp(str.data(), "DELETE") == 0)
      m = Method::DELETE;
    else if (std::strcmp(str.data(), "HEAD") == 0)
      m = Method::HEAD;
    else if (std::strcmp(str.data(), "PATCH") == 0)
      m = Method::PATCH;
  }
}
BENCHMARK(to_method_switch_cstr)->Arg(0)->Arg(1)->Arg(2)->Arg(3)->Arg(4)->Arg(5);

static void to_method_switch_str(benchmark::State& state)
{
  for (auto _ : state)
  {
    const std::string& str = methods_str[state.range(0)];
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
BENCHMARK(to_method_switch_str)->Arg(0)->Arg(1)->Arg(2)->Arg(3)->Arg(4)->Arg(5);

static void to_method_loop_cstr(benchmark::State& state)
{
  for (auto _ : state)
  {
    const std::string& str = methods_str[state.range(0)];
    Method m;
    for (std::size_t i = 0; i < methods_cstr.size(); ++i)
    {
      if (std::strcmp(str.data(), methods_cstr[i]) == 0)
      {
        m = static_cast<Method>(i);
        break;
      }
    }
  }
}
BENCHMARK(to_method_loop_cstr)->Arg(0)->Arg(1)->Arg(2)->Arg(3)->Arg(4)->Arg(5);

static void to_method_loop_str(benchmark::State& state)
{
  for (auto _ : state)
  {
    const std::string& str = methods_str[state.range(0)];
    Method m;
    for (std::size_t i = 0; i < methods_str.size(); ++i)
    {
      if (str.data() == methods_str[i])
      {
        m = static_cast<Method>(i);
        break;
      }
    }
  }
}
BENCHMARK(to_method_loop_str)->Arg(0)->Arg(1)->Arg(2)->Arg(3)->Arg(4)->Arg(5);

static void to_method_map(benchmark::State& state)
{
  for (auto _ : state)
  {
    const std::string& str = methods_str[state.range(0)];
    Method m = methods_map[str];
  }
}
BENCHMARK(to_method_map)->Arg(0)->Arg(1)->Arg(2)->Arg(3)->Arg(4)->Arg(5);
