/* Le Duong Cong Duc - 1651044
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);
void transpose_64_64(int M, int N, int A[N][M], int B[M][N]);
/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N]) 
{
    int Bsize; //Size of block
    int row_block, col_block; //used to iterate over columns and rows of block
    int r, c; // used to iterate through each block in inner loops
    int temp = 0, d = 0; //d stands for diagonal, temp is for temporary variable
    // int v0,v1,v2,v3,v4; //Variables to be used in the N==64 case for various assignments within it
    
    // important info :  s=5, E=1, b=5 (32 sets, direct-mapped, 32 bytes per block)
    if (N == 32)
    {
        Bsize = 8; // choose B = 8 for optimization result
        //why choose 8*8 ? the cache can hold a entirely 8x8 block of data in this case. In another word, accessing the data within a 8x8 block will only cause cold misses. Therefore, we can divide the 32x32 matrix into 16 blocks with the size of 32x32, and transpose block by block
        /*
    2 outer loops iterates accross blocks / 2 inner loops iterate through each block. 
    */
        for(col_block = 0; col_block < N; col_block += Bsize)
        {
            for(row_block = 0; row_block < N; row_block += Bsize)
            {
                for(r = row_block; r < row_block + Bsize; r++)
                {
                    for(c = col_block; c < col_block + Bsize; c++)
                    {
                        //When row and collumn is not equal then we can change the value in B to the desired value in A
                        if(r != c)
                        {
                                B[c][r] = A[r][c];
                        }
                        
                        else 
                        {
                        //However, when row == column, it means we touched the diagonal of the square. Now, we are accessing A and B in the same innerloop, and A, B have differnt tags. For the diagonal blocks, there are conflicts when accessing the same row of A and B. This part should not be moved or reassigned to avoid misses. Instead, we used 2 temporary variable, 1 to store the position, 1 to store the value for later assign.  use temporary local variables to avoid having to re-access those elements
                        temp = A[r][c];
                        d = r;
                        }
                    }
                    // Each traverse only has 1 element in the diagonal line. So we will assign it here, outside of the loop.
                    if (row_block == col_block)	
                    {
                        B[d][d] = temp;
                    }
                }
            }
        }
    }

    /* Using Bsize = 4 here. 
    2 levels of loops are used 
    We assign elements in each row individually. Causes reduced missess. */
    else if (N == 64)
    {	
        transpose_64_64(M,N,A,B);
    }

    /* Random size. We use Bsize = 16 
    2 levels of loops are used to iterate over blocks in column major iteration and 2 levels are used to go through the blocks
    */
    else 
    {
        Bsize = 16;
        
        for (col_block = 0; col_block < M; col_block += Bsize)
        {
            for (row_block = 0; row_block < N; row_block += Bsize)
            {	
                /*not all blocks will be square, so (row_block + 16 > N) may get an invalid access. Therefore we need to regularly check for r<N and c<M */
                for(r = row_block; (r < N) && (r < row_block + Bsize); r++)
                {
                    for(c = col_block; (c < M) && (c < col_block + Bsize); c++)
                    {
                        //row and column are not same
                        if (r != c)
                        {
                                B[c][r] = A[r][c];
                        }
                        
                        //row and column same. process like 32 x 32 
                        else
                        {
                                temp = A[r][c];
                                d = r;
                        }
                    }
                    
                    //Diagonal
                    if(row_block == col_block) 
                    {
                        B[d][d] = temp;
                    }
                }
            }
        }
    }
}

// custom function solve 64x64 case
char transpose_64_64_desc[] = "Transpose the 64 x 64 matrix";
void transpose_64_64(int M, int N, int A[N][M], int B[M][N]) {
    int colIndex, rowIndex, k, a0, a1, a2, a3, a4, a5, a6, a7; // supporting variables
    // two loops to go through each row and column block 
    for(colIndex=0; colIndex<64; colIndex+=8 ) {
       	for(rowIndex=0; rowIndex<64; rowIndex+=8 ) {
        /* 
        The first loop is for a 4 collumn 8 row of A. In this loop we  use the supporting variables to store all elements of a row. Then we try to transpose with the right positions in B. However, we are doing on a 4row x 8 collumn B to avoid cache miss so not all elements will be transposed correctly. For example A[3][5] cannot be transposed to B[5][3]. Thus, elements which can't be transposed correctly will be stored in another location for later use.
        */ 
            for(k=0; k<4; k++) { 
                a0 = A[colIndex+k][rowIndex+0];
                a1 = A[colIndex+k][rowIndex+1];
                a2 = A[colIndex+k][rowIndex+2];
                a3 = A[colIndex+k][rowIndex+3];
                a4 = A[colIndex+k][rowIndex+4];
                a5 = A[colIndex+k][rowIndex+5];
                a6 = A[colIndex+k][rowIndex+6];
                a7 = A[colIndex+k][rowIndex+7];

                // In the code, I comment "Good job" for the elements that are transposed correctly. "Later use" for later assignment
                B[rowIndex+0][colIndex+k+0] = a0;   // good job
                B[rowIndex+0][colIndex+k+4] = a5;	// later use
                B[rowIndex+1][colIndex+k+0] = a1;	// good job
                B[rowIndex+1][colIndex+k+4] = a6;	//later use
                B[rowIndex+2][colIndex+k+0] = a2;	// good job
                B[rowIndex+2][colIndex+k+4] = a7;	//later use
                B[rowIndex+3][colIndex+k+0] = a3;	// good job
                B[rowIndex+3][colIndex+k+4] = a4;	// later use
            }

            /* Part B, moving sub-matrix b to sub-matrix c
             * and moving A->B for sub-matrix b and move matrix d
             */
            /*
            Now that we have dealt with the first 4 col 8 arrow of A. The next job to deal with the "later use" assignment above. The "later use" assignments that we did above have taken a lot of places, so we need to bring these elements to their right positions. 
             */
            a0 = A[colIndex+4][rowIndex+4];
            a1 = A[colIndex+5][rowIndex+4];
            a2 = A[colIndex+6][rowIndex+4];
            a3 = A[colIndex+7][rowIndex+4];
            a4 = A[colIndex+4][rowIndex+3];
            a5 = A[colIndex+5][rowIndex+3];
            a6 = A[colIndex+6][rowIndex+3];
            a7 = A[colIndex+7][rowIndex+3];

            B[rowIndex+4][colIndex+0] = B[rowIndex+3][colIndex+4];  // B[4][0] = a4 = A[0][4] For example
            B[rowIndex+4][colIndex+4] = a0;  // B[4][4] = A[4][4] For example
            B[rowIndex+3][colIndex+4] = a4;
            B[rowIndex+4][colIndex+1] = B[rowIndex+3][colIndex+5];
            B[rowIndex+4][colIndex+5] = a1;
            B[rowIndex+3][colIndex+5] = a5;
            B[rowIndex+4][colIndex+2] = B[rowIndex+3][colIndex+6];
            B[rowIndex+4][colIndex+6] = a2;
            B[rowIndex+3][colIndex+6] = a6;
            B[rowIndex+4][colIndex+3] = B[rowIndex+3][colIndex+7];
            B[rowIndex+4][colIndex+7] = a3;
            B[rowIndex+3][colIndex+7] = a7;

        	// this loops deal with the the remaning elements .
            for(k=0;k<3;k++) {

                a0 = A[colIndex+4][rowIndex+5+k];
                a1 = A[colIndex+5][rowIndex+5+k];
                a2 = A[colIndex+6][rowIndex+5+k];
                a3 = A[colIndex+7][rowIndex+5+k];
                a4 = A[colIndex+4][rowIndex+k];
                a5 = A[colIndex+5][rowIndex+k];
                a6 = A[colIndex+6][rowIndex+k];
                a7 = A[colIndex+7][rowIndex+k];

                B[rowIndex+5+k][colIndex+0] = B[rowIndex+k][colIndex+4];
                B[rowIndex+5+k][colIndex+4] = a0;
                B[rowIndex+k][colIndex+4] = a4;
                B[rowIndex+5+k][colIndex+1] = B[rowIndex+k][colIndex+5];
                B[rowIndex+5+k][colIndex+5] = a1;
                B[rowIndex+k][colIndex+5] = a5;
                B[rowIndex+5+k][colIndex+2] = B[rowIndex+k][colIndex+6];
                B[rowIndex+5+k][colIndex+6] = a2;
                B[rowIndex+k][colIndex+6] = a6;
                B[rowIndex+5+k][colIndex+3] = B[rowIndex+k][colIndex+7];
                B[rowIndex+5+k][colIndex+7] = a3;
                B[rowIndex+k][colIndex+7] = a7;

            }
        }
    }	
}


/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}
