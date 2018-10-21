#include "gtest/gtest.h"
#include "route.hh"

using namespace jambe;

TEST(malformed_route, empty)
{
  try
  {
    std::string route = "";
    Route r(route);
    FAIL();
  }
  catch (const MalformedRouteException& expected) {}
  catch (const std::exception& expected)
  {
    FAIL();
  }
}

TEST(malformed_route, slash_slash)
{
  std::string route = "//";
  Route r(route);

  try
  {
    r.next_part();
    FAIL();
  }
  catch (const MalformedRouteException& expected) {}
  catch (const std::exception& expected)
  {
    FAIL();
  }
}

TEST(malformed_route, colon)
{
  try
  {
    std::string route = ":";
    Route r(route);
    FAIL();
  }
  catch (const MalformedRouteException& expected) {}
  catch (const std::exception& expected)
  {
    FAIL();
  }
}

TEST(malformed_route, slash_colon)
{
  std::string route = "/:";
  Route r(route);
  EXPECT_FALSE(r.is_end());

  try
  {
    r.next_part();
    FAIL();
  }
  catch (const MalformedRouteException& expected) {}
  catch (const std::exception& expected)
  {
    FAIL();
  }
}

TEST(malformed_route, empty_param_name1)
{
  std::string route = "/abc/:";
  Route r(route);

  EXPECT_EQ(r.next_part(), "abc");

  try
  {
    r.next_part();
    FAIL();
  }
  catch (const MalformedRouteException& expected) {}
  catch (const std::exception& expected)
  {
    FAIL();
  }
}

TEST(malformed_route, empty_param_name2)
{
  std::string route = "/abc/:/toto";
  Route r(route);

  EXPECT_EQ(r.next_part(), "abc");

  try
  {
    r.next_part();
    FAIL();
  }
  catch (const MalformedRouteException& expected) {}
  catch (const std::exception& expected)
  {
    FAIL();
  }
}

TEST(malformed_route, colon_inside_part)
{
  std::string route = "/abc/to:to";
  Route r(route);

  EXPECT_FALSE(r.is_end());
  EXPECT_EQ(r.next_part(), "abc");

  try
  {
    r.next_part();
    FAIL();
  }
  catch (const MalformedRouteException& expected) {}
  catch (const std::exception& expected)
  {
    FAIL();
  }
}

TEST(route, slash)
{
  std::string route = "/";
  Route r(route);
  EXPECT_TRUE(r.is_end());
}

TEST(route, slash_abc)
{
  std::string route = "/abc";
  Route r(route);
  EXPECT_FALSE(r.is_end());
  EXPECT_EQ(r.next_part(), "abc");
  EXPECT_TRUE(r.is_end());
}

TEST(route, slash_abc_slash)
{
  std::string route = "/abc/";
  Route r(route);
  EXPECT_FALSE(r.is_end());
  EXPECT_EQ(r.next_part(), "abc");
  EXPECT_TRUE(r.is_end());
}

TEST(route, slash_abc_def)
{
  std::string route = "/abc/def";
  Route r(route);
  EXPECT_FALSE(r.is_end());
  EXPECT_EQ(r.next_part(), "abc");
  EXPECT_FALSE(r.is_end());
  EXPECT_EQ(r.next_part(), "def");
  EXPECT_TRUE(r.is_end());
}

TEST(route, slash_abc_id_def)
{
  std::string route = "/abc/:id/def";
  Route r(route);
  EXPECT_FALSE(r.is_end());
  EXPECT_EQ(r.next_part(), "abc");
  EXPECT_FALSE(r.is_end());
  EXPECT_EQ(r.next_part(), ":id");
  EXPECT_FALSE(r.is_end());
  EXPECT_EQ(r.next_part(), "def");
  EXPECT_TRUE(r.is_end());
}
