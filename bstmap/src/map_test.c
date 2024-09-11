#include "map.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_create_destroy_bstmap() {
  map *mp = create_map();

  assert(mp != NULL);

  assert(mp->map_size == 0);
  assert(mp->root == NULL);

  destroy_map(mp);

  printf("test_create_destroy_bstmap: Passed\n");
}

void test_map_size() {
  map *mp = create_map();
  assert(map_size(mp) == 0);

  define(mp, "Rakhat", 21);
  assert(map_size(mp) == 1);

  define(mp, "Yskak", 12);
  assert(map_size(mp) == 2);

  define(mp, "Yskak", 20);
  assert(map_size(mp) == 2);

  define(mp, "Mirat", 23);
  assert(map_size(mp) == 3);

  destroy_map(mp);
  printf("test_map_size: Passed\n");
}

void test_print_bstmap() {
  map *mp = create_map();

  define(mp, "Rakhat", 21);
  define(mp, "Yskak", 12);
  define(mp, "Mirat", 23);

  printf("test_print_bstmap:\nExpected:\n[ "
         "\nRakhat\t21\nYskak\t12\nMirat\t23\n]\nActual:\n");
  print_map(mp);

  destroy_map(mp);
}

void test_define_get_value() {
  map *mp = create_map();

  define(mp, "Rakhat", 21);
  define(mp, "Yskak", 12);
  define(mp, "Mirat", 23);

  assert(get_value(mp, "Rakhat") == 21);
  assert(get_value(mp, "Yskak") == 12);
  assert(get_value(mp, "Mirat") == 23);

  destroy_map(mp);
  printf("test_define_get_value: Passed\n");
}

void test_clear_map() {
  map *mp = create_map();

  define(mp, "Rakhat", 21);
  define(mp, "Yskak", 12);
  define(mp, "Mirat", 23);

  clear_map(mp);

  assert(mp->map_size == 0);
  assert(mp->root == NULL);

  destroy_map(mp);

  printf("test_clear_map: Passed\n");
}

void test_contain_key() {
  map *mp = create_map();
  define(mp, "rakhat", 21);
  assert(contains_key(mp, "rakhat") && !contains_key(mp, "yskak"));
  destroy_map(mp);
  printf("Test contains key: Passed\n");
}

int main(int argc, char *argv[]) {
  test_create_destroy_bstmap();
  test_define_get_value();
  test_clear_map();
  test_contain_key();
  test_map_size();
  test_print_bstmap();
  return EXIT_SUCCESS;
}
