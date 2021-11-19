#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "hash.h"

int htsize = 10;

int main(int argc, char *argv[]) {
  int n = 8;	
  if (argc > 1) htsize = atoi(argv[1]);
  if (argc > 2) n = atoi(argv[2]);
  
  HASHTABLE *ht = new_hashtable(htsize);
  
  int i;
  char name[10];
  for (i=0; i<n; i++) {
	name[0] = i+'a';
  	name[1] = '\0';
	insert(ht, new_hashnode(name, i));
  }
  
  printf("hash table after insertion:ht1\n");
  display_hashtable(ht, 0);
  
  printf("\nsearch data by name:%s\n","a");
  HTNODE *hn = search(ht, "a");
  if (hn != NULL) {
    printf("ht1 search result:(%s, %d)\n", hn->name, hn->value);
  } else {
    printf("ht1 search result: not found\n");
  }

  printf("delete by name %s:ht2\n","a");
  delete(ht, "a");
  hn = search(ht, "a");
  if (hn != NULL) {
    printf("ht2 search result:(%s, %d)\n", hn->name, hn->value);
  } else {
    printf("ht2 search result: not found\n");
  }
 
  display_hashtable(ht, 0);
  display_hashtable(ht, 1);
  clean_hash(&ht);
  
  return 0;
}

