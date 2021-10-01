#ifndef ALIVE

#define ALIVE 'X'
#define DEAD '.'

typedef struct
{
  char current;
  char next;
} cell;

void step_to_next_generation(const int rows, const int cols,
          cell field[rows][cols]);

void get_living_neighbour_count(int x, int y, int *result, const int rows, const int cols,
          cell field[rows][cols]);

void print_world(const int rows, const int cols,
                 const cell field[rows][cols]);

void update_world(const int rows, const int cols,
                  cell field[rows][cols]);

#endif // ALIVE
