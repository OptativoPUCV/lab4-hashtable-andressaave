#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
  if (map == NULL)
  {
    return;
  }
  if (map->capacity == map->size)
  {
    enlarge(map);
  }
  
  long pos = hash(key,map->capacity);

  while(map->buckets[pos] != NULL && map->buckets[pos]->key != NULL){
      if(is_equal(key,map->buckets[pos]->key) == 0)
      {
        return;
      }
      pos = (pos+1) % map->capacity;
    }

  map->buckets[pos]->key = key; 
  map->buckets[pos]->value = value;
  map->size++;

  map->current = pos;
}

void enlarge(HashMap * map) {
  
  Pair **old_buckets = map->buckets;
  long old_capacity = map->capacity;

 
  map->capacity *= 2;

  
  map->buckets = (Pair **)calloc(map->capacity, sizeof(Pair *));

 
  map->size = 0;

  
  for (int i = 0; i < old_capacity; i++) {
      if (old_buckets[i] != NULL && old_buckets[i]->key != NULL) {
          insertMap(map, old_buckets[i]->key, old_buckets[i]->value);
      }
  }

 
  free(old_buckets);
  
  enlarge_called = 1; 

}


HashMap * createMap(long capacity) {
  HashMap * map = (HashMap*) malloc(sizeof(HashMap));
  map->buckets = (Pair**) calloc(capacity, sizeof(Pair*));
  map->size = 0;
  map->capacity = capacity;
  map->current = -1;
  
  return map;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   
  long pos = hash(key,map->capacity);

  while(map->buckets[pos] != NULL && map->buckets[pos]->key != NULL){
      if(is_equal(key,map->buckets[pos]->key) == 0)
      {
        return map->buckets[pos];
      }
      pos = (pos+1) % map->capacity;
    }

  return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
