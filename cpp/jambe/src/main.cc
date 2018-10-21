#include "router.hh"

#include <iostream>

int main()
{
  jambe::Router<int> r;
  int n[] = { 0, 1, 2, 3, 4, 5, 6 };
  r.add_route("/users", jambe::Method::GET, n[0]);
  r.add_route("/users", jambe::Method::POST, n[1]);
  r.add_route("/users/:id", jambe::Method::GET, n[2]);
  r.add_route("/users/:id", jambe::Method::PUT, n[3]);
  r.add_route("/users/:id", jambe::Method::DELETE, n[4]);
  r.add_route("/users/:id/posts", jambe::Method::GET, n[5]);
  r.add_route("/posts", jambe::Method::GET, n[6]);
}
