#include <stdio.h>

int main()
{
    /* Find all couples (x, y) such that there can be x tiles of size 2
     * and y tiles of size 3 in a strip of length 30
     * 2x + 3y = 30
     */

    /* strip of length 30: at most 30 tiles */
    int max_tiles = 30;

    int x[max_tiles];
    int y[max_tiles];
    int index = 0;
    int sum = 0;

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



    /* Find all possibilites for a parquet of 11 strips where
     * 2 adjacent strips can't share an inner edge
     */

    return 0;
}
