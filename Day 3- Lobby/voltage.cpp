#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main (int argc, char* argv[])
{
    std::string input_filename = "input.txt";
    if (argc > 1) 
    {
        input_filename = argv[1];
    }

    std::ifstream file(input_filename);
    if (!file.is_open())
    {
        std::cerr <<"Couldn't open file" << input_filename << std::endl;
        return 1;
    }

    std::string line;
    int total_joltage = 0;

    while(std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        int digit1 = 0;
        size_t first_max_pos = 0;
        bool found_first = false;

        if (line.length() > 1)
        {
            for (size_t i = 0; i < line.length() - 1; ++i)
            {
                if (line[i] >= '0' && line[i] <= '9')
                {
                    int current_digit = line[i] - '0';
                    if (!found_first || current_digit > digit1)
                    {
                        digit1 = current_digit;
                        first_max_pos = i;
                        found_first = true;
                    }
                }
            }
        }

        int digit2 = 0;
        bool found_second = false;

        if (found_first && first_max_pos + 1 < line.length())
        {
            for (size_t i = first_max_pos + 1; i < line.length(); ++i)
            {
                if (line[i] >= '0' && line[i] <= '9')
                {
                    int current_digit = line[i] - '0';
                    if (!found_second || current_digit > digit2)
                    {
                        digit2 = current_digit;
                        found_second = true;
                    }
                }
            }
        }

        total_joltage += digit1 * 10 + digit2;
    }

    std::cout << total_joltage << '\n';
    return 0;
}