/*
 * Programmering i C
 * Fall 19
 * Mastery test 9

 * File:         game_of_life.c
 * Description:  Implementation of all game of life related functions
 * Author:       Jesper Byström
 * CS username:  dv19jbm
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game_of_life.h"

/* Description: Steps the world forward one step
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */

void step_to_next_generation(const int rows, const int cols,
          cell field[rows][cols])
{
    int count = 0;

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            count = 0;
            get_living_neighbour_count(j, i, &count, rows, cols, field);

            if(field[i][j].current == ALIVE)
            {
                if(count < 2)
                {
                    field[i][j].next = DEAD;
                }
                else if(count > 3)
                {
                    field[i][j].next = DEAD;
                }
                else if(count == 2 || count == 3)
                {
                    field[i][j].next = ALIVE;
                }
            }
            else
            {
                if(count == 3)
                {
                    field[i][j].next = ALIVE;
                }
            }
        }
    }
}

/* Description: Gets the amount of living neighbours
 * Input:       Position of the cell to check, pointer to result
 *              and the field array and it's size
 * Output:      The field array is updated.
 */

void get_living_neighbour_count(int x, int y, int *result, const int rows, const int cols,
          cell field[rows][cols])
{
    if(y < rows-1)
    {
        if(field[y+1][x].current == ALIVE)
        {
            *result = *result + 1;
        }

        if(x > 0 && field[y+1][x-1].current == ALIVE)
        {
            *result = *result + 1;
        }

        if(x < cols-1 && field[y+1][x+1].current == ALIVE)
        {
            *result = *result + 1;
        }
    }

    if(y > 0)
    {
        if(field[y-1][x].current == ALIVE)
        {
            *result = *result + 1;
        }

        if(x > 0 && field[y-1][x-1].current == ALIVE)
        {
            *result = *result + 1;
        }

        if(x < cols-1 && field[y-1][x+1].current == ALIVE)
        {
            *result = *result + 1;
        }
    }

    if(x < cols-1 && field[y][x+1].current == ALIVE)
    {
        *result = *result + 1;
    }

    if(x > 0 && field[y][x-1].current == ALIVE)
    {
        *result = *result + 1;
    }
}

/* Description: Prints the world
 * Input:       The field array and its size.
 * Output:      Has no output
 */

void print_world(const int rows, const int cols,
                 const cell field[rows][cols])
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if(field[i][j].current == ALIVE)
            {
                printf("X ");
            }
            else
            {
                printf(". ");
            }
        }
        printf("\n");
    }
}

/* Description: Updates the world
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */

void update_world(const int rows, const int cols,
                  cell field[rows][cols])
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if(field[i][j].next == DEAD || field[i][j].next == ALIVE)
            {
                field[i][j].current = field[i][j].next;
            }
        }
    }
}
