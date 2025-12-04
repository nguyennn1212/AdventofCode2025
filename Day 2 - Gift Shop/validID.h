#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int start;
    int end;
} Range; 

void parse_ranges(const char *input_string, Range **ranges, int *count);
