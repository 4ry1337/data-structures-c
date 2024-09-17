#include "map.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void test_create_destroy_hashmap() {
  map *mp = create_map();

  assert(mp != NULL);
  assert(mp->map_size == 0);
  assert(mp->num_of_buckets == 4);
  assert(mp->buckets != NULL);

  destroy_map(mp);

  printf("test_create_destroy_hashmap:\tPassed\n");
}

void test_define_get_value() {
  map *mp = create_map();

  define(mp, "Rakhat", 21);

  assert(mp->map_size == 1);
  assert(get_value(mp, "Rakhat") == 21);
  assert(get_value(mp, "Mirat") == INT_MIN);

  define(mp, "Rakhat", 22);
  define(mp, "Mirat", 24);

  assert(mp->map_size == 2);
  assert(get_value(mp, "Rakhat") == 22);
  assert(get_value(mp, "Mirat") == 24);

  define(mp, "abc", 1);
  define(mp, "def", 1);
  define(mp, "rng", 1);
  define(mp, "c++", 1);
  define(mp, "asd", 1);
  define(mp, "qwe", 1);
  define(mp, "rty", 1);
  define(mp, "fgh", 1);
  define(mp, "uio", 1);
  define(mp, "p][", 1);
  define(mp, "jkl", 1);
  define(mp, ";'", 1);
  define(mp, "zxc", 1);
  define(mp, "vbn", 1);
  define(mp, "m.,", 1);

  assert(mp->num_of_buckets == 8);
  assert(mp->map_size == 17);

  destroy_map(mp);
  printf("test_define:\tPassed\n");
}

void test_contains_key() {
  map *mp = create_map();

  define(mp, "Rakhat", 22);

  assert(contains_key(mp, "Rakhat"));
  assert(!contains_key(mp, "Mirat"));

  destroy_map(mp);
  printf("test_contains_key:\tPassed\n");
}

void test_clear_map() {
  map *mp = create_map();

  define(mp, "Rakhat", 21);
  define(mp, "Mirat", 24);

  clear_map(mp);

  assert(mp != NULL);
  assert(mp->map_size == 0);
  assert(mp->num_of_buckets == 4);
  assert(mp->buckets != NULL);

  destroy_map(mp);

  printf("test_clear_map:\tPassed\n");
}

void test_map_size() {
  map *mp = create_map();

  define(mp, "Rakhat", 22);
  define(mp, "Mirat", 24);
  define(mp, "abc", 1);
  define(mp, "def", 1);
  define(mp, "rng", 1);
  define(mp, "c++", 1);
  define(mp, "asd", 1);
  define(mp, "qwe", 1);
  define(mp, "rty", 1);
  define(mp, "fgh", 1);
  define(mp, "uio", 1);
  define(mp, "p][", 1);
  define(mp, "jkl", 1);
  define(mp, ";'", 1);
  define(mp, "zxc", 1);
  define(mp, "vbn", 1);
  define(mp, "m.,", 1);

  assert(map_size(mp) == 17);

  destroy_map(mp);
  printf("test_map_size:\tPassed\n");
}
void test_print_map() {
  map *mp = create_map();

  define(mp, "Rakhat", 21);
  define(mp, "Mirat", 24);

  print_map(mp);

  destroy_map(mp);
  printf("test_print_map:\tPassed\n");
}

int main(int argc, char *argv[]) {
  test_create_destroy_hashmap();
  test_define_get_value();
  test_contains_key();
  test_clear_map();
  test_print_map();
  test_map_size();
  return EXIT_SUCCESS;
}
