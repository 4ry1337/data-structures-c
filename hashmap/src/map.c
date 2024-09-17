#include "map.h"
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_BUCKETS 4
#define MAX_LOAD_FACTOR 3.0

int hash(char *key) {
  int n = strlen(key), p = 31, power = 1, h = 0;
  for (int i = n - 1; i >= 0; i--) {
    h += key[i] * power;
    power *= p;
  }
  return h;
}

node *create_node(char *key, int val) {
  node *n = (node *)malloc(sizeof(node));
  if (n == NULL) {
    printf("Unable to allocate memory");
    exit(EXIT_FAILURE);
  }
  n->key = strdup(key);
  n->value = val;
  n->link = NULL;
  return n;
}

// Creates a new empty map on the heap
map *create_map() {
  map *mp = (map *)malloc(sizeof(map));

  mp->map_size = 0;
  mp->num_of_buckets = INITIAL_BUCKETS;
  mp->buckets = (node **)calloc(INITIAL_BUCKETS, sizeof(node *));

  if (mp->buckets == NULL) {
    free(mp);
    printf("Unable to allocate memory");
    exit(1);
  }

  return mp;
}

void destroy_bucket(node *curr) {
  if (curr == NULL) {
    return;
  }
  destroy_bucket(curr->link);
  free(curr->key);
  free(curr);
}

// Destroys the map, and frees up its memory
void destroy_map(map *mp) {
  for (size_t i = 0; i < mp->num_of_buckets; i++) {
    destroy_bucket(mp->buckets[i]);
  }
  free(mp->buckets);
  free(mp);
}

void rehash_map(map *mp) {
  size_t new_num_of_buckets = mp->num_of_buckets * 2;
  node **new_buckets = (node **)calloc(new_num_of_buckets, sizeof(node *));

  if (mp->buckets == NULL) {
    free(mp);
    printf("Unable to allocate memory");
    exit(1);
  }

  for (size_t i = 0; i < mp->num_of_buckets; i++) {
    node *curr = mp->buckets[i];
    while (curr != NULL) {
      node *next = curr->link;
      int new_index = hash(curr->key) % new_num_of_buckets;

      // For efficiency reversed order
      curr->link = new_buckets[new_index];
      new_buckets[new_index] = curr;

      curr = next;
    }
  }

  free(mp->buckets);
  mp->buckets = new_buckets;
  mp->num_of_buckets = new_num_of_buckets;
}

// Adds the key-value pair (key, val) to the map
void define(map *mp, char *key, int val) {
  int h = hash(key);
  node **curr = &mp->buckets[h % mp->num_of_buckets];
  while (*curr != NULL) {
    if (strcmp((*curr)->key, key) == 0) {
      (*curr)->value = val;
      return;
    }
    curr = &(*curr)->link;
  }
  *curr = create_node(key, val);
  if (*curr == NULL) {
    printf("Unable to allocate memory");
    return;
  }
  mp->map_size++;
  if (((double)mp->map_size / mp->num_of_buckets) > MAX_LOAD_FACTOR) {
    /*printf("rehashing...\n");*/
    rehash_map(mp);
  }
  return;
}

// Checks if the given key is in the map
_Bool contains_key(map *mp, char *key) {
  int h = hash(key);
  node *curr = mp->buckets[h % mp->num_of_buckets];
  while (curr != NULL) {
    if (strcmp(curr->key, key) == 0) {
      return true;
    }
    curr = curr->link;
  }
  return false;
}

// Returns the value associated with the given key;
// If the key is not there, output an error message to the
// console window, and return INT_MIN
int get_value(map *mp, char *key) {
  int h = hash(key);
  node *curr = mp->buckets[h % mp->num_of_buckets];
  while (curr != NULL) {
    if (strcmp(curr->key, key) == 0) {
      return curr->value;
    }
    curr = curr->link;
  }
  return INT_MIN;
}

// Returns the number of key-value pairs in the map
size_t map_size(map *mp) { return mp->map_size; }

// Removes all of the key-value pairs from the map
void clear_map(map *mp) {
  for (size_t i = 0; i < mp->num_of_buckets; i++) {
    destroy_bucket(mp->buckets[i]);
    mp->buckets[i] = NULL;
  }
  mp->map_size = 0;
}

void print_bucket(node *node) {
  if (node == NULL) {
    return;
  }
  printf("<%s, %d>; ", node->key, node->value);
  print_bucket(node->link);
}

// Outputs the key-value pairs in the map to the console window
void print_map(map *mp) {
  printf("{ ");
  for (size_t i = 0; i < mp->num_of_buckets; i++) {
    print_bucket(mp->buckets[i]);
  }
  printf("}\n");
}

// Outputs the load factor of the underlying hash table
double load_factor(map *mp) {
  return (double)mp->map_size / mp->num_of_buckets;
}

// Outputs the standard deviation of the sizes of the buckets
// in the underlying hash table
double bucket_size_stdev(map *mp) {
  double mean = load_factor(mp);
  double var = 0.0;

  for (size_t i = 0; i < mp->num_of_buckets; i++) {
    node *curr = mp->buckets[i];
    size_t bucket_size = 0;
    while (curr != NULL) {
      bucket_size++;
      curr = curr->link;
    }
    var += ((bucket_size - mean) * (bucket_size - mean));
  }
  return sqrt(var / mp->num_of_buckets);
}
