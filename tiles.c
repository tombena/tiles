#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
 * strips_sums: contains all such combinations
 * under the form of partial sums.
 * for example, 2-2-3 becomes 2-4-7
 * seq: current tile sequence
 * (a full sequence is a strip)
 * seq_pos: position in tile sequence
 * r_x: remaining number of size 2 tiles
 * r_y: remaining number of size 3 tiles
 */
static void
find_unique_strips(int *strips_sums[], int seq[], int seq_pos, int r_x, int r_y)
{
    /* if no tiles remain */
    if (r_x == 0 && r_y == 0)
    {
        strips_sums[seqno] = (int *)malloc(15 * sizeof(int));

        if (strips_sums[seqno] == NULL)
            printf("memory allocation failed\n");

        /* add tile sequence found to unique strips
         * (under the form of partial sums)
         */
        strips_sums[seqno][0] = seq[0];
        for (int i = 1; i < 15; i++)
            strips_sums[seqno][i] = strips_sums[seqno][i - 1] + seq[i];

        /* increment seq number because this one has just been used */
        seqno++;
    }

    /* try adding a tile of size 2 */
    if (r_x != 0)
    {
        seq[seq_pos] = 2;
        find_unique_strips(strips_sums, seq, seq_pos + 1, r_x - 1, r_y);
    }

    /* try adding a tile of size 3 */
    if (r_y != 0)
    {
        seq[seq_pos] = 3;
        find_unique_strips(strips_sums, seq, seq_pos + 1, r_x, r_y - 1);
    }
}

/* check if 2 strips share an inner edge */
static bool
share_inner_edge(int *strips_sums[], int seqno1, int seqno2, int *compat[])
{
    /* use pre-computed results */
    if (compat[seqno1][seqno2] == 1 || compat[seqno2][seqno1] == 1)
    {
        //printf("pre-computed %d & %d\n", seqno1, seqno2);
        return true;
    }
    else if (compat[seqno1][seqno2] == 2 || compat[seqno2][seqno1] == 2)
    {
        //printf("pre-computed %d & %d\n", seqno1, seqno2);
        return false;
    }

    for (int i = 0; i < 15; i++)
    {
        /* sequence 1 has been read already */
        if (strips_sums[seqno1][i] == 0 ||
            strips_sums[seqno1][i] == 30)
            break;

        /* compare partial sums of both sequences
         * 2 sums being equal means tile share inner edge
         */
        for (int j = 0; j < 15; j++)
        {
            if (strips_sums[seqno1][i] == strips_sums[seqno2][j])
            {
                compat[seqno1][seqno2] = 1; // share inner edge
                return true;
            }
            else if (strips_sums[seqno2][j] == 0 ||
                     strips_sums[seqno2][j] == 30)
                break;
        }
    }

    printf("%d & %d sums always different\n", seqno1, seqno2);
    compat[seqno1][seqno2] = 2; // don't share inner edge
    return false;
}

/* compute number of designs of 11 stripes
 * that don't share inner edges
 * strips_sums: partial sums for all strips
 * cur_seqno: sequence number of the current strip
 * depth: number of strips selected so far
 */
static int
compute_designs(int *strips_sums[], int cur_seqno, int depth,
                int *compat[])
{
    /* max depth reached */
    if (depth == 11)
        return 1;

    int sum = 0;

    /* pick 1st strip */
    if (cur_seqno == -1)
    {
        /* pick any strip */
        for (int i = 0; i < seqno; i++)
            sum += compute_designs(strips_sums, i, 1, compat);
    }
    else
    {
        /* pick a strip that doesn't share inner edges
         * with the current strip
         */
        for (int i = 0; i < seqno; i++)
        {
            if (!share_inner_edge(strips_sums, i, cur_seqno, compat))
                sum += compute_designs(strips_sums, i, depth + 1, compat);
        }
    }

    /* check it doesn't have inner edge with previous line
     * note: we only need to know the previous strip to check
     * for overlap
     */

    return sum;
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
    /* partial sums in design */
    int *strips_sums[max_poss];

    int ind_str = 0;

    int min_xy = 0;
    int seq[15] = {0};

    /* For each couple (x, y)
     * TODO for all couples (index)
     */
    for (int i = 0; i < index; i++)
    {
        /* Find unique possibilites for strip */
        find_unique_strips(strips_sums, seq, 0, x[i], y[i]);
    }

    printf("\nall possible strips:\n");
    /* Print all possible strips */
    for (int i = 0; i < seqno; i++)
    {
        printf("i = %d :", i);
        for (int j = 0; j < 15; j++)
            printf("%d ", strips_sums[i][j]);
        printf("\n");
    }
    printf("\ndone\n");

    /* make a 2D array holding whether strips i and j
     * share inner edges (0, 1, 2)
     */
    int *compat[seqno];
    for (int i = 0; i < seqno; i++)
    {
        compat[i] = (int *)malloc(seqno * sizeof(int));
        /* zero the array */
        memset(compat[i], 0, seqno * sizeof(int));
    }

    /* Find all possibilites (designs) for a parquet of 11 strips where
     * 2 adjacent strips can't share an inner edge
     */
    int n_designs = compute_designs(strips_sums, -1, 0, compat);

    printf("%d possible designs found", n_designs);

    /* Free memory */
    for (int i = 0; i < seqno; i++)
    {
        free(strips_sums[i]);
        free(compat[i]);
    }

    printf("\ndone");

    return 0;
}
