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
            (*ranges)[*count - 1].start = atoll(range_token);
            (*ranges)[*count - 1].end = atoll(dash_ptr + 1);
        }
        else
        {
            (*ranges)[*count - 1].start = atoll(range_token);
            (*ranges)[*count - 1].end = (*ranges)[*count - 1].start;
        }

        range_token = strtok(NULL, ",");
    }

    free(input_copy);
}

int is_invalid_id(long long number)
{
    char num_str[22];
    sprintf(num_str, "%lld", number);
    int len = strlen(num_str);

    if (len <= 1)
    {
        return 0;
    }

    int n = len / 2;  

    //extract first half
    char part_a[n + 1];
    strncpy(part_a, num_str, n);
    part_a[n] = '\0';

    //extract second half
    int part_b_len = len - n;
    char part_b[part_b_len + 1];
    strncpy(part_b, num_str + n, part_b_len);
    part_b[part_b_len] = '\0';

    //if both part are equal it's invalid
    if (strcmp(part_a, part_b) == 0)
    {
        return 1;
    }

    return 0;
}

long long add_ids(long long *invalid_ids, int count)
{
    long long sum = 0;
    for (int i = 0; i < count; i++)
    {
        sum += invalid_ids[i];
    }
    return sum;
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

    //store all invalid IDs
    long long *invalid_ids = NULL;
    int invalid_count = 0;

    printf("starting range iteration\n");

    //loop through each Range structure
    for (int i = 0; i < num_ranges; i++)
    {
        long long start = parsed_ranges[i].start;
        long long end = parsed_ranges[i].end;
        printf("\nProcessing Range %d: %lld to %lld\n", i + 1, start, end);

        //loop through every number from start range to end range
        for(long long j = start; j <= end; j++)
        {
            if(is_invalid_id(j))
            {
                //add to invalid_ids array
                invalid_count++;
                invalid_ids = (long long *)realloc(invalid_ids, invalid_count * sizeof(long long));
                if(invalid_ids == NULL)
                {
                    perror("Memory reallocation failed");
                    free(parsed_ranges);
                    return 1;
                }
                invalid_ids[invalid_count - 1] = j;
                printf("Invalid ID found: %lld\n", j);
            }
        }
    }

    //sum of all invalid IDs
    long long sum_of_invalid = add_ids(invalid_ids, invalid_count);
    printf("\nTotal invalid IDs found: %d\n", invalid_count);
    printf("The sum of all invalid IDs is: %lld\n", sum_of_invalid);

    free(invalid_ids);
    free(parsed_ranges);
    printf("\nProgram end.\n");
    return 0; 
}
