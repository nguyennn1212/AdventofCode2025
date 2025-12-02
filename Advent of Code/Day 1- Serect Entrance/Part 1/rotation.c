#include "rotation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LEN 256
#define DIAL 100

char *read_line(FILE *fname, char *buffer, size_t buffersize)
{
    if(fgets(buffer, buffersize, fname) == NULL)
    {
        return NULL;
    }

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') 
    {
        buffer[len - 1] = '\0';
    }
    return buffer;
}

int combination(const char *direction, int *position, int *zero_count)
{
    //different error return cases
    if (direction == NULL || direction[0] == '\0')
    {
        return 0;
    }

    char left_or_right = direction[0];
    if(left_or_right != 'L' && left_or_right != 'R')
    {
        return 0;
    }

    int number_part = atoi(&direction[1]);
    if(number_part < 0)
    {
        return 0;
    }

    //take in direction and number
    if (*direction == 'L')
    {
        *position = (*position - number_part) %DIAL;

        if(*position < 0)
        {
            *position += DIAL; 
        }
    } 
    else 
    {
        *position = (*position + number_part) %DIAL;
    }

    if(*position == 0)
    {
        (*zero_count)++;
    }
    
    return 1; 
}



int main(int argc, char **argv)
{
    if(argc != 2) 
    {
        fprintf(stderr, "Usage: %s <input_file\n", argv[0]);
        return 1;
    }

    FILE *fpath = fopen(argv[1], "r");
    if(fpath == NULL)
    {
        perror("No file found.");
        return 1;
    }

    char line[MAX_LINE_LEN];
    int current_position = 50;
    int zero_count = 0;

    while(read_line(fpath, line, MAX_LINE_LEN) != NULL)
    {
        int past_position = current_position;

        if(combination(line, &current_position, &zero_count))
        {
            printf("Rotated %s:%d -> %d\n", line, past_position, current_position);
        }
    }

    fclose(fpath);
    printf("Password: %d\n", zero_count);
    return 0;
}