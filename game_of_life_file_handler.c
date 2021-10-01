/*
 * Programmering i C
 * Fall 19
 * Mastery test 9

 * File:         game_of_life_handler.c
 * Description:  Handles the saving & loading of configuration files
 * Author:       Jesper Byström
 * CS username:  dv19jbm
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "game_of_life.h"
#include "game_of_life_file_handler.h"

/*
* Description: Load a configuration to the field array from a file.
*
*
* Input: The field array, its size and a file pointer to the
* file with the initial configuration.
*
* Output: Returns 0 on success, the field array is updated with
* the configuration from the file.
* Returns a non-zero value on failure.
* The file pointed to by fp is closed.
*/

int load_config_from_file(const int rows, const int cols,
 cell field[rows][cols], FILE *fp)
{
    char line[BUFFER_SIZE];
    int row_number = 0;

    while(fgets(line, BUFFER_SIZE, fp) != NULL)
    {
        //Read data from config file
        for(int i = 0; i < strlen(line); i++)
        {
            if(line[i] == '0')
            {
                field[row_number][i].current = DEAD;
            }
            else if(line[i] == '*')
            {
                field[row_number][i].current = ALIVE;
            }
        }

        row_number++;
    }

    if(fclose(fp) == EOF)
    {
        return -1;
    }

    return 0;
}

/*
* Description: Saves the current configuration of the field array to
* a specified file.
*
*
* Input: The field array, its size and a file pointer to the
* file where the final configuration should be saved.
*
* Output: Returns 0 on success, the current configuration in the
* field array is written to the file.
* Returns a non-zero value on failure.
* The file pointed to by fp is closed.
*/
int save_config_to_file(const int rows, const int cols,
 const cell field[rows][cols], FILE *fp)
{
    fprintf(fp, "%d,%d\n", rows, cols);

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if(field[i][j].current == ALIVE)
            {
                fprintf(fp, "%c", '*');
            }
            else if(field[i][j].current == DEAD)
            {
                fprintf(fp, "%c", '0');
            }
        }

        fprintf(fp, "\n");
    }

    if(fclose(fp) == EOF)
    {
        return -1;
    }

    return 0;
}
