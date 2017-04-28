#include <stdio.h>
#include <stdlib.h>
#define BOARD 9

int** read_input(char *file_name);
int** create_array(int size);
int check_board(int** board, int x, int y, int value);

int main(int argc, char* argv[]) 
{
    int** board;
    board = read_input(argv[1]);
    
    return 0;
}

int** backtracking_solver(int** board) 
{
    int i, j;
    int** remove_me;
    for (i = 0; i <= BOARD; i++) 
    {
        for (j = 0; j <= BOARD; j++) 
        {
            if (board[i][j] != 0) {
                continue;
            }
            // check row
            // check colunm
            // check box
            // if ok place a 1 in cell and go on
            // if in next check ""
        }
    }
    return remove_me; 
}

int check_board(int** board, int x, int y, int value)
{
    int i;
    // check row and column
    for (i = 0; i < BOARD; i++) 
    {
        if ((board[y][i] == value) || (board[i][x] == value))
        {
            return 0;
        }

    }
    return 1;

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
