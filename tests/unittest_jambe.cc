#include "gtest/gtest.h"
#include "jambe.hh"

using namespace jambe;

static
int n[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

template <typename T>
static
void check_lookup_success(const Lookup<T>& l, const T& exp_data, std::size_t exp_param_size)
{
  EXPECT_EQ(l.error, LookupError::NONE);
  EXPECT_EQ(l.data, exp_data);
  EXPECT_EQ(l.params.size(), exp_param_size);
}

template <typename T>
static
void check_lookup_params(const Lookup<T>& l, const std::vector<Param>& exp_params)
{
  EXPECT_EQ(l.params.size(), exp_params.size());

  for (size_t i = 0; i < l.params.size(); ++i)
  {
    EXPECT_EQ(l.params[i].name, exp_params[i].name);
    EXPECT_EQ(l.params[i].value, exp_params[i].value);
  }
}

template <typename T>
static
void check_lookup_fail(const Lookup<T>& l, LookupError exp_err)
{
  EXPECT_EQ(l.error, exp_err);
}

TEST(basic, get_root)
{
  Router<int> r;
  r.add_route("/", Method::GET, n[0]);
  auto l = r.lookup("/", Method::GET);
  check_lookup_success(l, n[0], 0);
}

TEST(basic, get_users)
{
  Router<int> r;
  r.add_route("/users", Method::GET, n[0]);
  auto l = r.lookup("/users", Method::GET);
  check_lookup_success(l, n[0], 0);
}

TEST(basic, post_users)
{
  Router<int> r;
  r.add_route("/users", Method::POST, n[0]);
  auto l = r.lookup("/users", Method::POST);
  check_lookup_success(l, n[0], 0);
}

TEST(basic, delete_users)
{
  Router<int> r;
  r.add_route("/users", Method::DELETE, n[0]);
  auto l = r.lookup("/users", Method::DELETE);
  check_lookup_success(l, n[0], 0);
}

TEST(basic, head_users)
{
  Router<int> r;
  r.add_route("/users", Method::HEAD, n[0]);
  auto l = r.lookup("/users", Method::HEAD);
  check_lookup_success(l, n[0], 0);
}

TEST(basic, patch_users)
{
  Router<int> r;
  r.add_route("/users", Method::PATCH, n[0]);
  auto l = r.lookup("/users", Method::PATCH);
  check_lookup_success(l, n[0], 0);
}

TEST(basic, put_users)
{
  Router<int> r;
  r.add_route("/users", Method::PUT, n[0]);
  auto l = r.lookup("/users", Method::PUT);
  check_lookup_success(l, n[0], 0);
}

TEST(basic, get_users_multiple_methods)
{
  Router<int> r;
  r.add_route("/users", Method::GET, n[0]);
  r.add_route("/users", Method::POST, n[1]);
  auto l = r.lookup("/users", Method::POST);
  check_lookup_success(l, n[1], 0);
}

TEST(lookup_error, get_root_wrong_method)
{
  Router<int> r;
  r.add_route("/users", Method::GET, n[0]);
  auto l = r.lookup("/users", Method::POST);
  check_lookup_fail(l, LookupError::METHOD_NOT_ALLOWED);
}

TEST(lookup_error, get_users_wrong_method)
{
  Router<int> r;
  r.add_route("/users", Method::GET, n[0]);
  auto l = r.lookup("/users", Method::POST);
  check_lookup_fail(l, LookupError::METHOD_NOT_ALLOWED);
}

TEST(lookup_error, get_not_found1)
{
  Router<int> r;
  r.add_route("/users", Method::GET, n[0]);
  auto l = r.lookup("/users/toto", Method::GET);
  check_lookup_fail(l, LookupError::NOT_FOUND);
}

TEST(lookup_error, get_not_found2)
{
  Router<int> r;
  r.add_route("/users", Method::GET, n[0]);
  auto l = r.lookup("/usars", Method::GET);
  check_lookup_fail(l, LookupError::NOT_FOUND);
}

TEST(lookup_error, get_not_found_empty)
{
  Router<int> r;
  auto l = r.lookup("/users", Method::GET);
  check_lookup_fail(l, LookupError::NOT_FOUND);
}

TEST(param, get_users_id)
{
  Router<int> r;
  r.add_route("/users/:id", Method::GET, n[0]);
  auto l = r.lookup("/users/32", Method::GET);
  check_lookup_success(l, n[0], 1);
  check_lookup_params(l, { { "id", "32"} });
}

TEST(param, get_users_id_posts)
{
  Router<int> r;
  r.add_route("/users/:id/posts", Method::GET, n[0]);
  auto l = r.lookup("/users/32/posts", Method::GET);
  check_lookup_success(l, n[0], 1);
  check_lookup_params(l, { { "id", "32"} });
}

TEST(param, backtracking1)
{
  Router<int> r;
  r.add_route("/users/:id/posts/yo", Method::GET, n[0]);
  r.add_route("/users/me/posts", Method::GET, n[1]);
  auto l = r.lookup("/users/me/posts/yo", Method::GET);
  check_lookup_success(l, n[0], 1);
  check_lookup_params(l, { { "id", "me"} });
}

TEST(param, backtracking2)
{
  Router<int> r;
  r.add_route("/:id/lol", Method::GET, n[0]);
  r.add_route("/lol/:id", Method::GET, n[1]);
  auto l = r.lookup("/lol/lol", Method::GET);
  check_lookup_success(l, n[1], 1);
  check_lookup_params(l, { { "id", "lol"} });
}

TEST(param, backtracking3)
{
  Router<int> r;
  r.add_route("/:bb/bras/jambe", Method::GET, n[0]);
  r.add_route("/lol/:aaa/toto", Method::GET, n[1]);
  auto l = r.lookup("/lol/bras/jambe", Method::GET);
  check_lookup_success(l, n[0], 1);
  check_lookup_params(l, { { "bb", "lol"} });
}

TEST(user_exception, already_registered)
{
  Router<int> r;
  r.add_route("/abc", Method::GET, n[0]);
  try
  {
    r.add_route("/abc", Method::GET, n[1]);
    FAIL();
  }
  catch (const AlreadyRegisteredException& expected) {}
}

TEST(user_exception, already_registered_param)
{
  Router<int> r;
  r.add_route("/users/:id", Method::POST, n[0]);
  try
  {
    r.add_route("/users/:id", Method::POST, n[1]);
    FAIL();
  }
  catch (const AlreadyRegisteredException& expected) {}
}

TEST(user_exception, wildcard_conflict1)
{
  Router<int> r;
  r.add_route("/users/:id", Method::GET, n[0]);
  try
  {
    r.add_route("/users/:user_id/posts", Method::GET, n[1]);
    FAIL();
  }
  catch (const WildcardConflictException& expected) {}
}

TEST(user_exception, wildcard_conflict2)
{
  Router<int> r;
  r.add_route("/users/:id", Method::GET, n[0]);
  try
  {
    r.add_route("/users/me/posts/:id", Method::GET, n[1]);
    FAIL();
  }
  catch (const WildcardConflictException& expected) {}
}
