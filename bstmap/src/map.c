#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _tree_node {
  char *key;
  int value;
  struct _tree_node *left;
  struct _tree_node *right;
} tree_node;

tree_node *insert_tree(tree_node *tn, char *key, int val) {
  if (tn == NULL) {
    tn = (tree_node *)malloc(sizeof(tree_node));
    if (tn == NULL) {
      printf("Unable to allocate memory");
      exit(1);
    }
    tn->key = strdup(key);

    if (tn->key == NULL) {
      free(tn);
      return NULL;
    }

    tn->left = tn->right = NULL;
    tn->value = val;

    return tn;
  }

  int cmp = strcmp(key, tn->key);
  if (cmp > 0) {
    tn->right = insert_tree(tn->right, key, val);
  } else if (cmp < 0) {
    tn->left = insert_tree(tn->left, key, val);
  } else {
    tn->value = val;
  }
  return tn;
}

tree_node *find_node(tree_node *tn, char *key) {
  if (tn == NULL) {
    return NULL;
  } else {
    int cmp = strcmp(key, tn->key);
    if (cmp > 0) {
      return find_node(tn->right, key);
    } else if (cmp < 0) {
      return find_node(tn->left, key);
    } else {
      return tn;
    }
  }
}

void destroy_tree(tree_node *tn) {
  if (tn) {
    destroy_tree(tn->left);
    destroy_tree(tn->right);
    free(tn->key);
    free(tn);
  }
}

void print_tree(tree_node *tn) {
  if (tn == NULL)
    return;
  print_tree(tn->left);
  printf("%s\t%d\n", tn->key, tn->value);
  print_tree(tn->right);
}

typedef struct {
  size_t map_size;
  tree_node *root;
} map;

// Creates a new empty map on the heap
map *create_map() {
  map *mp = (map *)malloc(sizeof(map));

  if (mp == NULL) {
    printf("Unable to allocate memory\n");
    exit(1);
  }

  mp->root = NULL;
  mp->map_size = 0;

  return mp;
}

// Destroys the map, and frees up its memory
void destroy_map(map *mp) {
  if (mp == NULL) {
    printf("NULL map pointer\n");
    return;
  }
  destroy_tree(mp->root);
  free(mp);
}

// Adds the key-value pair (key, val) to the map
void define(map *mp, char *key, int val) {
  if (mp == NULL) {
    printf("NULL map pointer\n");
    return;
  }
  if (key == NULL) {
    printf("NULL key pointer\n");
    return;
  }
  tree_node *exists = find_node(mp->root, key);
  if (exists != NULL) {
    exists->value = val;
  } else {
    mp->root = insert_tree(mp->root, key, val);
    mp->map_size++;
  }
}

// Checks if the given key is in the map
_Bool contains_key(map *mp, char *key) {
  if (mp == NULL) {
    printf("NULL map pointer\n");
    return false;
  }
  if (key == NULL) {
    printf("NULL key pointer\n");
    return false;
  }
  return find_node(mp->root, key) != NULL;
}

// Returns the value associated with the given key;
// If the key is not there, output an error message to the
// console window, and return INT_MIN
int get_value(map *mp, char *key) {
  if (mp == NULL) {
    printf("NULL map pointer\n");
    return INT_MIN;
  }
  if (key == NULL) {
    printf("NULL key pointer\n");
    return INT_MIN;
  }
  return find_node(mp->root, key)->value;
}

// Returns the number of key-value pairs in the map
size_t map_size(map *mp) {
  if (mp == NULL) {
    printf("NULL map pointer\n");
    return 0;
  }
  return mp->map_size;
}

// Removes all of the key-value pairs from the map
void clear_map(map *mp) {
  if (mp == NULL) {
    printf("NULL map pointer\n");
    return;
  }
  destroy_tree(mp->root);
  mp->root = NULL;
  mp->map_size = 0;
}

// Outputs the key-value pairs in the map to the console window
void print_map(map *mp) {
  if (mp == NULL) {
    printf("NULL map pointer\n");
    return;
  }
  printf("[\n");
  print_tree(mp->root);
  printf("]\n");
}
