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

#ifndef __CONFIG_H__
#define __CONFIG_H__

struct config {
  char *fileName;
  int noffsets;
  unsigned long *offsets;
  char *chars;
  int slotSize;
  unsigned long base;
};

typedef struct config *config_t;

config_t readConfig(const char *cf);
void freeConfig(config_t conf);

int checkConfig(config_t conf);





#endif // __CONFIG_H__
