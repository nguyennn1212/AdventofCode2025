#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    long long start;
    long long end;
} Range; 

long long invalid_id(long long number);
void parse_ranges(const char *input_string, Range **ranges, int *count);
