#include <stdio.h>
#include <stdlib.h>
#define BOARD 9

int** read_input(char *file_name);
int** create_array(int size);
int check_position(int** board, int x, int y, int value);
int* get_range(int num);

int main(int argc, char* argv[]) 
{
    int** board;
    board = read_input(argv[1]);
    
    return 0;
}

int** backtracking_solver(int** board) 
{
    // TODO: add iteration counter. 
    // maybe watch it happen in real time?
    int i, j;
    // value stores
    int prev_value, cur_val = 1;
    int** remove_me;
    for (i = 0; i <= BOARD; i++) 
    {
        for (j = 0; j <= BOARD; j++) 
        {
            if (board[i][j] != 0) {
                continue;
            }
            // check board if ok to add number;
            // if ok place a 1 in cell and go on
            // if in next check ""
        }
    }
    return remove_me; 
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
            return 0;
        }
    }
    // check column
    for (i = 0; i < BOARD; i++) 
    {
        if (board[i][x] == value)
        {
            return 0;
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
                return 0;
            }
        }
    }
    return 1;
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
