#include <stdio.h>
#include <stdlib.h>

/* XXX maybe change to atomic type
 * single threaded code can't race
 */
int seqno = 0;

/* return mininimum of a and b */
int
min(int a, int b)
{
    if (b < a)
        return b;
    else
        return a;
}

/* Find unique combinations of size 2 and size 3 tiles to
 * make up a strip of length 30.
 * strips: contains all such combinations
 * seq: current combination
 * seq_pos: position in seq
 * r_x: remaining number of size 2 tiles
 * r_y: remaining number of size 3 tiles
 */
static void
find_unique_strips(int *strips[], int seq[], int seq_pos, int r_x, int r_y)
{
    /* if no tiles remaining */
    if (r_x == 0 && r_y == 0)
    {
        strips[seqno] = (int *)malloc(30 * sizeof(int));

        if (strips[seqno] == NULL)
            printf("memory allocation failed\n");

        /* add seq found to unique strips */
        for (int i = 0; i < 30; i++)
            strips[seqno][i] = seq[i];
        /* increment seq number, this one has been used */
        seqno++;
    }

    /* try adding a tile of size 2 */
    if (r_x != 0)
    {
        seq[seq_pos] = 2;
        find_unique_strips(strips, seq, seq_pos + 1, r_x - 1, r_y);
    }

    /* try adding a tile of size 3 */
    if (r_y != 0)
    {
        seq[seq_pos] = 3;
        find_unique_strips(strips, seq, seq_pos + 1, r_x, r_y - 1);
    }
}

static bool
share_inner_edge(int seqno1, int seqno2)
{
   /* if 2 sums are = at any point, share inner edge
    * except last edge
    */
}

static void
compute_designs(int *strips[])
{
    /* there can be 11 lines */

}

int
main()
{
    /* strip of length 30 contains at most 30 tiles */
    int max_tiles = 30;

    int x[max_tiles];
    int y[max_tiles];
    int index = 0;
    int sum = 0;


    /* Find all couples (x, y) such that there can be x tiles of size 2
     * and y tiles of size 3 in a strip of length 30
     * 2x + 3y = 30
     */
    for (int i = 0; i < 30; i++)
    {
        /* strip length can't exceed 30 */
        if (2*i > 30)
            continue;

        for (int j = 0; j < 30; j++)
        {
            sum = 2*i + 3*j;

            /* couple found */
            if (sum == 30)
            {
                x[index] = i;
                y[index] = j;
                index++;
                break;

            /* strip too long */
            } else if (sum > 30)
                break;
        }
    }

    /* Print solutions */
    for (int i = 0; i < index; i++)
    {
      printf("Found 2*%d + 3*%d = 30 \n", x[i], y[i]);
    }

    /* Note: there are index couples that are solution */

    /* Find all unique possibilities for a strip of length 30 */

    int max_poss = 1000;
    int *strips[max_poss];

    int ind_str = 0;

    int min_xy = 0;
    int seq[30] = {0};

    /* For each couple (x, y)
     * TODO for all couples (index)
     */
    for (int i = 0; i < 2; i++)
    {
        /* Find unique possibilites for strip */
        find_unique_strips(strips, seq, 0, x[i], y[i]);
    }


    printf("\nall possible strips:\n");
    /* Print all possible strips */
    for (int i = 0; i < seqno; i++)
    {
        for (int j = 0; j < 30; j++)
            printf("%d", strips[i][j]);
        printf("\n");
    }
    printf("\ndone");

    /* TODO Find all possibilites (designs) for a parquet of 11 strips where
     * 2 adjacent strips can't share an inner edge
     */
     compute_designs(strips);

    /* Free memory */
    for (int i = 0; i < seqno; i++)
        free(strips[i]);

    printf("\ndone");

    return 0;
}
