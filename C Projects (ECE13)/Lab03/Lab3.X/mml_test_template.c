// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"

// User libraries:
#include "MatrixMath.h"

// Global Variables
int functionpass;

// Module-level variables:
// Example Matrices:
float zero_matrix[3][3] = {
    {},
    {},
    {}
};
float matrix1[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};
float matrix2[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};
float matrix3[3][3] = {
    {1.1, 2.2, 3.3},
    {4.4, 5.5, 6.6},
    {7.7, 8.8, 9.9}
};
float matrix4[3][3] = {
    {-1, 2, 3},
    {4, 5, 6},
    {7, -8, 9}
};
float matrix5[3][3] = {
    {3, 2, 3},
    {5, 5, 6},
    {7, 10, 9}
};

float resul[2][2];

int main()
{
    BOARD_Init();

    printf("Beginning 1828506's mml test harness, compiled on %s %s\n\n", __DATE__, __TIME__);
    
    // Testing MatrixEquals
    int count = 0;                                  //internal counter to increment every single time a function passes.
    int test1 = MatrixEquals(matrix1, matrix2);         
    int test2 = MatrixEquals(zero_matrix, matrix1);
    
    if (test1 == 1){
        count++;
    }
    if (test2 == 0){
        count++;
    }
    if (count == 2){                                //if internal counter equals 2, it will increment the global variable by 1. 
        functionpass++;
    printf("PASSED (%d/2): MatrixEquals()\n", count);            //prints whether tests passes
    }
    
    // Testing MatrixMultiply
    int count2 = 0;

    float MatrixMul1[3][3];
    float MatrixMul2[3][3];
    
    MatrixMultiply(zero_matrix, matrix1, MatrixMul1);
    MatrixMultiply(matrix4, matrix3, MatrixMul2);
    
    float matrixMulEQ[3][3] = {             // This is the answer to matrix3 multiplied by matrix4 to compare
        {30.8, 35.2, 39.6},
        {72.6, 89.1, 105.6},
        {41.8, 50.6, 59.4}
    };
    
    int test3 = MatrixEquals(MatrixMul1, zero_matrix);
    int test4 = MatrixEquals(MatrixMul2, matrixMulEQ);
    
    if (test3 == 1){
        count2++;
    }
    if (test4 == 1){
        count2++;
    }
    if (count2 == 2){
        functionpass++;
    }
    printf("PASSED (%d/2): MatrixMultiply()\n", count2);
    
    // Testing ScalarMultiply
    int count3 = 0;
    
    float matrixSMul[3][3], matrixSMul2[3][3]; 
    
    MatrixScalarMultiply(0, matrix1, matrixSMul);
    MatrixScalarMultiply(-2, matrix3, matrixSMul2);
    
    float matrixSMulEQ[3][3] = {             // This is the answer to matrix3 scalar multiplied by -2
        {-2.2, -4.4, -6.6},
        {-8.8, -11, -13.2},
        {-15.4, -17.6, -19.8}
    };
    
    int test5 = MatrixEquals(zero_matrix, matrixSMul);
    int test6 = MatrixEquals(matrixSMulEQ, matrixSMul2);

    if (test5 == 1) {
        count3++;
    }
    if (test6 == 1) {
        count3++;
    }
    if (count3 == 2) {
        functionpass++;
    }
    printf("PASSED (%d/2): MatrixScalarMultiply()\n", count3);
    
    // Testing Determinant
    int count4 = 0;

    float test7 = MatrixDeterminant(matrix1);
    float test8 = MatrixDeterminant(matrix4);

    if (test7 == 0) {
        count4++;
    }
    if (test8 == -282) {
        count4++;
    }
    if (count4 == 2) {
        functionpass++;
    }
    printf("PASSED (%d/2): MatrixDeterminant()\n", count4);
    
    // Testing MatrixAdd
    float MatrixADD1[3][3];
    float MatrixADD2[3][3];
    
    MatrixAdd(zero_matrix, matrix1, MatrixADD1);        //Call MatrixAdd Function
    MatrixAdd(matrix1, matrix3, MatrixADD2);
    
    float matrixADDEQ[3][3] = {
        {2.1, 4.2, 6.3},
        {8.4, 10.5, 12.6},
        {14.7, 16.8, 18.9}
    };
        
    int counter5 = 0;                                 //internal counter
    
    int test9 = MatrixEquals(MatrixADD1, matrix1);       //Compare answers with MatrixAdd function and real output
    int test10 = MatrixEquals(MatrixADD2, matrixADDEQ);
    
    if (test9 != 0){
        counter5++;
    }
    if (test10 == 1){
        counter5++;
    }
    if (counter5 == 2){
        functionpass++;
    }
    printf("PASSED (%d/2): MatrixAdd()\n", counter5); 
    
    // Testing MatrixScalarAdd
    int count6 = 0;

    float matrixSAdd[3][3], matrixSAdd2[3][3];

    MatrixScalarAdd(1, zero_matrix, matrixSAdd);
    MatrixScalarAdd(-5, matrix1, matrixSAdd2);

    float matrixSAddEQ1[3][3] = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    float matrixSAddEQ2[3][3] = {
        {-4, -3, -2},
        {-1, 0, 1},
        {2, 3, 4}
    };

    int test11 = MatrixEquals(matrixSAdd, matrixSAddEQ1);
    int test12 = MatrixEquals(matrixSAdd2, matrixSAddEQ2);

    if (test11 == 1) {
        count6++;
    }
    if (test12 == 1) {
        count6++;
    }
    if (count6 == 2) {
        functionpass++;
    }
    printf("PASSED (%d/2): MatrixScalarAdd()\n", count6);
    
    // Testing MatrixInverse
    
    // Testing MatrixTranspose
    int count8 = 0;

    float matrixTrans1[3][3], matrixTrans2[3][3];

    MatrixTranspose(matrix1, matrixTrans1);
    MatrixTranspose(matrix5, matrixTrans2);

    float matrixTransposeEQ1[3][3] = {
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 9}
    };
    float matrixTransposeEQ2[3][3] = {
        {3, 5, 7},
        {2, 5, 10},
        {3, 6, 9}
    };

    int test15 = MatrixEquals(matrixTrans1, matrixTransposeEQ1);
    int test16 = MatrixEquals(matrixTrans2, matrixTransposeEQ2);

    if (test15 == 1) {
        count8++;
    }
    if (test16 == 1) {
        count8++;
    }
    if (count8 == 2) {
        functionpass++;
    }
    printf("PASSED (%d/2): MatrixTranspose()\n", count8);
    
    // Testing MatrixTrace
    int count9 = 0;

    float test17 = MatrixTrace(matrix1);
    float test18 = MatrixTrace(matrix4);
    
    if (test17 == 15) {
        count9++;
    }
    if (test18 == 13) {
        count9++;
    }
    if (count9 == 2) {
        functionpass++;
    }
    printf("PASSED (%d/2): MatrixTrace()\n", count9);
   
    /*
    // Testing MatrixSubmatrix
    int count10 = 0;

    float matrixplaceholder1[2][2] = {
        {},
        {}
    };
    float matrixplaceholder2[2][2] = {
        {},
        {}
    };
    
    MatrixSubmatrix(2, 2, matrix1, matrixplaceholder1);
    MatrixSubmatrix(1, 3, matrix4, matrixplaceholder2);
    
    
    
    float matrixSubEQ1[2][2] = {                // Real values for Submatrix
        {1, 3},
        {7, 9}
    };
    
    float matrixSubEQ2[2][2] = {
        {4, 5},
        {7, -8}
    };

    int test19 = MatrixEqSub(matrixplaceholder1, matrixSubEQ1);
    int test20 = MatrixEqSub(matrixplaceholder2, matrixSubEQ2);
    
    if (test19 == 1) {
        count9++;
    }
    if (test20 == 1) {
        count9++;
    }
    if (count10 == 2) {
        functionpass++;
    }
    printf("PASSED (%d/2): MatrixSubmatrix()\n", count10);
    */
    
    // Total Functions Passed
    printf("-------------------------------------\n");
    double passpercent = (functionpass/10.0) * 100;
    printf("%d out of 10 functions passed (%f%%).\n", functionpass, passpercent);
    
    

    // Function test for MatrixPrint using Matrix3
    printf("\nOutput of MatrixPrint(): \n");
    MatrixPrint(matrix3);
    
    // Hard Code Test of MatrixPrint() using Matrix3
    printf("\nExpected Output of MatrixPrint(): \n");
    printf(" ____________________ \n");
    printf("| 1.10 | 2.20 | 3.30 |\n");
    printf(" -------------------- \n");
    printf("| 4.40 | 5.50 | 6.60 |\n");
    printf(" -------------------- \n");
    printf("| 7.70 | 8.80 | 9.90 |\n");
    printf(" -------------------- \n");
    
    
    BOARD_End();
    while (1);
}

