/*
 * Copyright 2013,2014 The University of Adelaide
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>


#define MEMSIZE_MALLOCED	-1

struct memdata {
  void *allocaddrs;
  void *realaddress;
  int size; 
  struct memdata *next;
};

static struct memdata *allocd = NULL;

static struct memdata *memdata_new() {
  struct memdata *cur;
  for (cur = allocd; cur != NULL; cur = cur->next)
    if (cur->allocaddrs == NULL)
      return cur;
  cur = malloc(sizeof(struct memdata));
  bzero(cur, sizeof(cur));
  cur->next = allocd;
  allocd = cur;
  return cur;
}


void *map(const char *fn, int size) {
  int fd = open(fn, O_RDONLY);
  if (fd < 0) {
    perror(fn);
    exit(1);
  }

  if (size == 0) {
    struct stat st_buf;
    fstat(fd, &st_buf);
    size = st_buf.st_size;
  }

  void *rv = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
  close(fd);
  printf("Mapped at %p (0x%x)\n", rv, size);
  struct memdata *md = memdata_new();
  md->allocaddrs = md->realaddress = rv;
  md->size = size;
  return rv;
}


void *alignedalloc(int size, int align) {
  assert((align & (align - 1)) == 0);
  struct memdata *md = memdata_new();
  size += align -1;
  md->realaddress = malloc(size + align - -1);
  md->allocaddrs = (void *)((char *)md->realaddress + (align - ((int)md->realaddress & (align - 1))));
  md->size = MEMSIZE_MALLOCED;
  return md->allocaddrs;
}


void memfree(void *addr) {
  for (struct memdata *cur = allocd; cur != NULL; cur = cur->next)
    if (cur->allocaddrs == addr) {
      if (cur->size == MEMSIZE_MALLOCED) 
	free(cur->realaddress);
      else
	munmap(cur->realaddress, cur->size);
      cur->allocaddrs = NULL;
    }
}


