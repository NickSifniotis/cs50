/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;
int zero_value;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
int get_board(int);
void set_board(int, int);
void swap_pieces(int, int);
void swap_pieces_2d(int, int, int, int);


int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    for (int i = 0, j = d*d; i < j; i ++)
        set_board(i, j - i - 1);
        
    if (d % 2 == 0)
        swap_pieces(d*d-2, d*d-3);
        
    zero_value = 0;
    set_board(d*d-1, zero_value);
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int x = 0; x < d; x ++)
    {
        for (int y = 0; y < d; y ++)
        {
            if (board[x][y] == zero_value)
                printf("   _");
            else
            {
                string spaces = (board[x][y] > 9) ? "  " : "   ";
                printf("%s%d", spaces, board[x][y]);
            }
        }
        
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // start by finding the two pieces
    int bx = -1;
    int by = -1;
    int ax = -1;
    int ay = -1;
    
    for (int x = 0; x < d; x++)
        for (int y = 0; y < d; y++)
        {
            if (board[x][y] == zero_value)
            {
                bx = x;
                by = y;
            }
            if (board[x][y] == tile)
            {
                ax = x;
                ay = y;
            }
        }
        
    // have we found them all?
    if (ax == -1 || bx == -1)
        return false;
        
    // this is a bit of magic
    // this metric counts the total number of horizontal and vertical moves
    // between the two points a and b.
    // a legal move can only be one space away
    int differential = abs(ax - bx) + abs(ay - by);
    if (differential != 1)
        return false;
        
    swap_pieces_2d(ax, ay, bx, by);
    return true;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    for (int i = 0, j = d*d-2; i < j; i ++)
        if (get_board(i) > get_board(i + 1) || get_board(i) == 0)
            return false;
            
    return true;
}

/**
 * Nick Sifniotis
 * 29 December 2015
 * 
 * Helpers functions to get and set game board state using one dimensional
 * access instead of two dimensional.
 */
void set_board(int index, int value)
{
    if (index < 0 || index >= (d * d))
        return;
        
    int x = index / d;
    int y = index % d;
     
    board[x][y] = value;
    return;
}
 
int get_board(int index)
{
    if (index < 0 || index >= (d * d))
        return -1;
        
    int x = index / d;
    int y = index % d;
     
    return board[x][y];
}


/**
 * Nick Sifniotis
 * 29 December 2015
 * 
 * Swap two pieces on the game board.
 * No legality checks are performed - this is a blind swap.
 */
void swap_pieces(int a, int b)
{
    int holding = get_board(a);
    set_board(a, get_board(b));
    set_board(b, holding);
}

void swap_pieces_2d(int xa, int ya, int xb, int yb)
{
    int holding = board[xa][ya];
    board[xa][ya] = board[xb][yb];
    board[xb][yb] = holding;
}