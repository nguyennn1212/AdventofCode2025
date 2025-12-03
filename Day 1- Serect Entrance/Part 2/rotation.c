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



    //save position BEFORE updating it
    int past_position = *position;

    //take in direction and number
    if (*direction == 'L')
    {
        *position = (*position - number_part) % DIAL;

        if(*position < 0)
        {
            *position += DIAL;
        }
    }
    else
    {
        *position = (*position + number_part) %DIAL;
    }

    //implement a different zero count for part 2 of the puzzle
    *zero_count += number_part / DIAL;

    int temp = number_part % DIAL; //keep track of where the position would land

    //count the time the pointer passes through zero DURING rotation (not ending at zero)
    if(temp > 0 && past_position != 0)
    {
        if (left_or_right == 'R')
        {
            //going right: if old position + movement goes past 100, we passed through zero
            if (past_position + temp > DIAL)
            {
                (*zero_count)++;
            }
        }
        else // left_or_right == 'L'
        {
            //going left: if old position is less than movement, we passed through zero
            if (past_position < temp)
            {
                (*zero_count)++;
            }
        }
    }
    //count the number of time the point at zero
    if (*position == 0)
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