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
int find_next_cell(int** board, int* next_row, int* next_col);
void print_board(int** board);

int main(int argc, char* argv[]) 
{
    int** board;
    board = read_input(argv[1]);
    printf("Input: \n");
    print_board(board);
    if (backtracking_solver(board)) 
    {
        printf("Solved! \n");
        print_board(board);
    }
    else {
        printf("Cannot be solved.");
    }
    
    return 0;
}

int find_next_cell(int** board, int* next_row, int* next_col) 
{
    int row, col;
    for (row = *next_row; row < BOARD; row++)
    { 
        for (col = *next_col; col < BOARD; col++) 
        { 
             if (board[row][col] == EMPTY)
             {
                 *next_row = row;
                 *next_col = col;
                 return TRUE;
             }
        } 
    }
    return FALSE;
}

int backtracking_solver(int** board) 
{
    int row, col, value;
    int* next_row = calloc(1, sizeof(int));
    int* next_col = calloc(1, sizeof(int));
    if (!find_next_cell(board, next_row, next_col)) 
    {
        return TRUE; 
    } 
    find_next_cell(board, next_row, next_col);
    for (value = 1; value <= BOARD; value++) 
    {
        if (check_position(board, *next_row, *next_col, value)) 
        {
            board[*next_row][*next_col] = value;
            if (backtracking_solver(board)) 
            {
                return TRUE;
            }
        }
        board[*next_row][*next_col] = EMPTY;
    }
    free(next_row);
    free(next_col);
    return FALSE;
}

int check_position(int** board, int row, int col, int value)
{
    int i, j;
    int* row_range;
    int* col_range;
    
    // check row
    for (i = 0; i < BOARD; i++) 
    {
        if (board[row][i] == value)
        {
            return FALSE;
        }
    }
    // check column
    for (i = 0; i < BOARD; i++) 
    {
        if (board[i][col] == value)
        {
            return FALSE;
        }
    }
    // check box
    row_range = get_range(row);
    col_range = get_range(col);
    for (i = row_range[0]; i <= row_range[1]; i++) 
    {
        for (j = col_range[0]; j <= col_range[1]; j++) 
        {
            if (board[i][j] == value) 
            {
                return FALSE;
            }
        }
    }
    free(row_range);
    free(col_range);
    return TRUE;
}

int* get_range(int num) 
{
    int start, end;
    int* range = calloc(2, sizeof(int));
    if (num < 3) {
        range[0] = 0;
        range[1] = 2;
    } else if (num >= 3 && num < 6){
        range[0] = 3;
        range[1] = 5;
    } else if (num >= 6 && num < 9){
        range[0] = 6;
        range[1] = 8;
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
    fclose(input_file);
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

void print_board(int **board) {
    int i, j;
    for (i = 0; i < BOARD; i++) {
        for (j = 0; j < BOARD; j++) {
            if (j == BOARD - 1) {
                printf("%d\n", board[i][j]);
                
            } else {
                printf("%d ", board[i][j]);
            }
        }
    }
}

