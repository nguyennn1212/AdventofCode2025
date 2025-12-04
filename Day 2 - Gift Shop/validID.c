#include "validID.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void parse_ranges(const char *input_string, Range **ranges, int *count) 
{
    char *input_copy = strdup(input_string);
    if (input_copy == NULL)
    {
        perror("Memory allocation failed");
        return;
    }

    *count = 0;
    *ranges = NULL; //initalize array pointer

    char *range_token; //split individual ranges (",")
    range_token = strtok(input_copy, ",");

    while (range_token != NULL)
    {
        (*count)++;
        *ranges = (Range *)realloc(*ranges, (*count) * sizeof(Range));
        if(*ranges == NULL)
        {
            perror("Memory reallocation failed");
            free(input_copy);
            return;
        }

        char *dash_ptr = strchr(range_token, '-');

        if (dash_ptr != NULL)
        {
            *dash_ptr = '\0';
            (*ranges)[*count - 1].start = atoi(range_token);
            (*ranges)[*count - 1].end = atoi(dash_ptr + 1);
        }
        else 
        {
            (*ranges)[*count - 1].start = atoi(range_token);
            (*ranges)[*count - 1].end = (*ranges)[*count - 1].start;
        }

        range_token = strtok(NULL, ",");
    }

    free(input_copy);
}

int main()
{
    FILE *file;
    char buffer[1024];
    Range *parsed_ranges = NULL;
    int num_ranges = 0;
    const char *filename = "input.txt";

    file = fopen(filename, "r");
    if(file == NULL) 
    {
        perror("Error opening file");
        return 1;
    }
    if(fgets(buffer, sizeof(buffer), file) == NULL)
    {
        fprintf(stderr, "File is empty or error during read.\n");
        fclose(file);
        return 1;
    }
    fclose(file);
    buffer[strcspn(buffer, "\n")] = 0; //remove new line

    parse_ranges(buffer, &parsed_ranges, &num_ranges);

    if (num_ranges == 0)
    {
        printf("No ranges were sucessfully parsed. Exiting.\n");
        return 0;
    }

    printf("Input \"%s\" parsed into %d ranges .\n", buffer, num_ranges);

    //iterate through each number
    printf("starting range iteration\n");

    //loop through reach Range structure
    for (int i = 0; i < num_ranges; i++)
    {
        int start = parsed_ranges[i].start;
        int end = parsed_ranges[i].end;
        
        printf("\nProcessing Range %d: %d to %d\n", i + 1, start, end);
        
        //loop through every number from start range to end range
        for(int j = start; j <= end; j++)
        {
            printf("%d\n",j);
        }
    }
    
    free(parse_ranges);
    printf("\nProgram end.\n");
    return 0; 
}
