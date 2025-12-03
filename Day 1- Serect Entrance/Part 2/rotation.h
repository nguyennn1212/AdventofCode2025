#ifndef ROTATION_H
#define ROTATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *read_line(FILE *fname, char *buffer, size_t buffersize);
int combination(const char *instruction, int *position, int *zero_count);

#endif