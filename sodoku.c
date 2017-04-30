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
int find_next_cell(int** board, int* next_x, int* next_y);
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

int find_next_cell(int** board, int* next_x, int* next_y) 
{
    int x, y;
    for (x = *next_x; x < BOARD; x++)
    { 
        for (y = *next_x; y < BOARD; y++) 
        { 
             if (board[x][y] == EMPTY)
             {
                 *next_x = x;
                 *next_y = y;
                 printf("debug next cell %d %d\n", *next_x, *next_y);
                 return TRUE;
             }
        } 
    }
    return FALSE;
}

int backtracking_solver(int** board) 
{
    int x, y, value;
    int* next_x = calloc(1, sizeof(int));
    int* next_y = calloc(1, sizeof(int));

    if (!find_next_cell(board, next_x, next_y)) 
    {
        return TRUE; 
    }
    find_next_cell(board, next_x, next_y);
    printf("debug next cell in solver %d %d\n", *next_x, *next_y);
    for (value = 1; value <= BOARD; value++) 
    {
        printf("debug value: %d\n", value);
        if (check_position(board, *next_x, *next_y, value)) {
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
            printf("row: %d, %d, %d\n", i, y, value);
            return FALSE;
        }
    }
    // check column
    for (i = 0; i < BOARD; i++) 
    {
        if (board[i][x] == value)
        {
            printf("col\n");
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
                printf("box\n");
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
    } else if (num > 6 && num <= 8){
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

