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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "config.h"

#define LINELN 512
#define NPROBES 10


config_t readConfig(const char *cf) {
  config_t rv = NULL;
  char line[LINELN];
  FILE *f = fopen(cf, "r");
  if (f == NULL)
    return NULL;
  rv = malloc(sizeof(*rv));
  if (rv == NULL)
    goto err;
  bzero(rv, sizeof(*rv));
  rv->offsets = malloc(sizeof(unsigned long) * NPROBES);
  rv->chars = malloc(NPROBES);
  while (fgets(line, LINELN, f) != NULL) {
    char *cmd = strtok(line, " \n");
    char *arg1 = strtok(NULL, " \n");
    char *arg2 = strtok(NULL, " \n");

    if (cmd == NULL || cmd[0] == '#')
      continue;
    if (!strcmp(cmd, "map")) {
      if (arg1 == NULL)
	continue;
      if (rv->fileName)
	free(rv->fileName);
      rv->fileName = strdup(arg1);
      continue;
    }
    if (!strcmp(cmd, "probe")) {
      if (arg2 == NULL)
	continue;
      if (rv->noffsets == NPROBES)
	continue;
      sscanf(arg1, "%li", rv->offsets + rv->noffsets);
      rv->chars[rv->noffsets] = arg2[0];
      rv->noffsets++;
      continue;
    }
    if (!strcmp(cmd, "slot")) {
      if (arg1 == NULL)
	continue;
      sscanf(arg1, "%li", &rv->slotSize);
      continue;
    }
    if (!strcmp(cmd, "base")) {
      if (arg1 == NULL)
	continue;
      sscanf(arg1, "%li", &rv->base);
      continue;
    }
  }
  fclose(f);
  return rv;


err:
  freeConfig(rv);
  if (f != NULL)
    fclose(f);
  return NULL;
}





void freeConfig(config_t conf) {
  if (conf == NULL)
    return;
  if (conf->fileName != NULL)
    free(conf->fileName);
  if (conf->offsets != NULL)
    free(conf->offsets);
  if (conf->chars != NULL)
    free(conf->chars);
  free(conf);
}


int checkConfig(config_t conf) {
  if (conf == NULL)
    return 0;
  if (conf->fileName == NULL)
    return 0;
  if (conf->slotSize == 0)
    return 0;
  if (conf->noffsets == 0)
    return 0;
  return 1;
}

