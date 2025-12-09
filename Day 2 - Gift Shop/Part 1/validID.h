#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    long long start;
    long long end;
} Range; 

int is_invalid_id(long long number);
long long add_ids(long long *invalid_ids, int count);
void parse_ranges(const char *input_string, Range **ranges, int *count);
