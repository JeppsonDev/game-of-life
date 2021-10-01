/*
 * Programmering i C
 * Fall 19
 * Mastery test 9

 * File:         mp9.c
 * Description:  A simple implementation of Conway's Game of Life.
 * Author:       Jesper Byström
 * CS username:  dv19jbm
 * Date:
 * Input:        Choice of initial configuration and then instruction
                 to step or exit.
 * Output:       Prints the game field in each step.
 * Limitations:  No validation of input.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "game_of_life.h"
#include "game_of_life_file_handler.h"

#define COLUMNS 20
#define ROWS 20

/* Declaration of functions */
void init_field(const int rows, const int cols,
                cell field[rows][cols]);

int check_prog_params(int argc, const char *argv[],
 FILE **in_file_p, FILE **out_file_p);

int get_size_of_grid_from_string(char* line, char seperator, int *field_size);



/* Description: Start and run games, interact with the user.
 * Input:       About what initial structure and whether to step or
 *              exit.
 * Output:      Prints information to the user, and the game field in
 *              each step.
 */

int main(int argc, char const *argv[])
{
    char line[BUFFER_SIZE];
    FILE *in_file_p;
    FILE *out_file_p;

    if(check_prog_params(argc, argv, &in_file_p, &out_file_p) != 0)
    {
        return 0;
    }

    int field_size[2] = {0, 0};

    //Read first line from file
    fgets(line, BUFFER_SIZE, in_file_p);

    if(get_size_of_grid_from_string(line, ',', field_size) != 0)
    {
        fprintf(stderr, "Incorrect configuration file format");
        return 0;
    }

    if(field_size[1] > ROWS || field_size[0] > COLUMNS)
    {
        fprintf(stderr, "The configuration is too big for the field\n");
        fprintf(stderr, "The field needs to be at least %d rows and %d columns", field_size[1], field_size[0]);
    }

    cell field[ROWS][COLUMNS];

    init_field(ROWS, COLUMNS, field);

    if(load_config_from_file(ROWS, COLUMNS, field, in_file_p) != 0)
    {
        return 0;
    }

    char next_command;

    do
    {
        print_world(ROWS, COLUMNS, field);

        step_to_next_generation(ROWS, COLUMNS, field);

        printf("Select one of the following options:\n\t(enter) Step\n\t(any) Save and exit\n");

        next_command = getchar();

        if(next_command == '\n')
        {
            update_world(ROWS, COLUMNS, field);
        }

    } while(next_command == '\n');

    //Something went wrong with saving config file
    if(save_config_to_file(ROWS, COLUMNS, field, out_file_p) != 0)
    {
        return 0;
    }

    return 0;
}

/* Description: Initialize all the cells to dead, then asks the user
 *              about which structure to load, and finally load the
 *              structure.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */

void init_field(const int rows, const int cols,
                cell field[rows][cols])
{
    for (int r = 0 ; r < rows ; r++)
    {
        for (int c = 0 ; c < cols ; c++)
        {
            field[r][c].current = DEAD;
        }
    }
}

/*
* Description: Checks the parameters to the program. Checks if the
* call to the program has the right number of
* parameters. Open the input and output files.
*
*
* Input: The parameters to the program and two pointers to file
* pointers.
*
* Output: Returns 0 when the files are correctly opened.
* Returns a non-zero value on failure.
*/

int check_prog_params(int argc, const char *argv[],
                      FILE **in_file_p, FILE **out_file_p)
{
    if(argc != 3)
    {
        fprintf(stderr, "Usage: %s <input configuration file> <output configuration file>", argv[0]);
        return -1;
    }

    *in_file_p = fopen(argv[1], "r");
    if(*in_file_p == NULL)
    {
        fprintf(stderr, "Could not open the file: %s\n", argv[1]);
        return -1;
    }

    *out_file_p = fopen(argv[2], "w");
    if(*out_file_p == NULL)
    {
        fprintf(stderr, "Could not open the file: %s\n", argv[2]);
        return -1;
    }

    return 0;
}

/*
* Description: Gets the size of a 2D field by a string with a seperator
*
*
* Input: What string to get the size from,
* what the seperator is and a pointer to an integer array with the size of 2 (vector)
*
* Output: Outputs the size into the
* vector array that field_size is pointing to
* Returns 0 on success, non-zero number on failure
*/

int get_size_of_grid_from_string(char* line, char seperator, int *field_size)
{
    int len = strlen(line);
    int index = 1;

    for(int i = 0; i <= len - 2; i++)
    {
        if(line[i] == seperator)
        {
            index--;
            continue;
        }
        else if(line[i] >= '0' && line[i] <= '9')
        {
            field_size[index] = (field_size[index] * 10) + (line[i] - '0');
        }
        else
        {
            return -1;
        }
    }

    return 0;
}
