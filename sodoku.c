#include <stdio.h>
#include <stdlib.h>
#define BOARD 9
#define EMPTY 0
#define TRUE 1
#define FALSE 0

int** read_input(char *file_name);
int** create_array(int size);
int check_position(int** board, int x, int y, int value);
int* get_range(int num);
int backtracking_solver(int** board);
int find_next_cell(int** board, int next_x, int next_y);


int main(int argc, char* argv[]) 
{
    int** board;
    board = read_input(argv[1]);
    
    return 0;
}

int find_next_cell(int** board, int next_x, int next_y) 
{
   for (next_x = 0; next_x < BOARD; next_x++)
   { 
       for (next_y = 0; next_y < BOARD; next_y++) 
       { 
           if (board[next_x][next_y] == EMPTY)
               return TRUE;
       } 
   }
   return FALSE;
}

int backtracking_solver(int** board) 
{
    int x, y, value;
    if (!find_next_cell(board, x, y)) 
    {
        return TRUE; 
    }
    for (value = 1; value <= BOARD; value++) 
    {
        if (check_position(board, x, y, value)) {
            board[x][y] = value;
            if (backtracking_solver(board)) 
            {
                return TRUE;
            }
            board[x][y] = EMPTY;
        } 
    }
    return FALSE; 
}

int check_position(int** board, int x, int y, int value)
{
    int i, j;
    int* x_range;
    int* y_range;

    // check row
    for (i = 0; i < BOARD; i++) 
    {
        if (board[y][i] == value)
        {
            return FALSE;
        }
    }
    // check column
    for (i = 0; i < BOARD; i++) 
    {
        if (board[i][x] == value)
        {
            return FALSE;
        }
    }
    // check box
    x_range = get_range(x);
    y_range = get_range(y);
    for (i = x_range[0]; i <= x_range[1]; i++) 
    {
        for (j = y_range[0]; j <= y_range[1]; j++) 
        {
            if (board[i][j] == value) 
            {
                return FALSE;
            }
        }
    }
    return TRUE;
}

int* get_range(int num) 
{
    int start, end;
    int* range = malloc(2 * sizeof(int));
    if (num < 3) {
        range[0] = 0;
        range[1] = 2;
    } else if (num > 3 && num < 6){
        range[0] = 3;
        range[1] = 5;
    } else if (num > 6 && num < 8){
        range[0] = 6;
        range[1] = 7;
    }
    return range;
}

int** read_input(char *file_name) 
{
    FILE *input_file = fopen(file_name, "r");
    int** board = create_array(BOARD);
    int i, j;
    if (input_file == NULL) {
        printf("No file to read");
        return board;
    }
    while(!feof(input_file)) {
        for (i = 0; i < BOARD; i++) {
            for (j = 0; j < BOARD; j++)
            fscanf(input_file, "%1d", &board[i][j]);
        }
    } 
    return board;
}

int** create_array(int size) {
    int* cells = calloc(size * size, sizeof(int));
    int** multi_array = malloc(size * sizeof(int*));
    int i;
    for (i = 0; i < size; ++i) {
        multi_array[i] = cells + i * size;
    }
    return multi_array;
}
