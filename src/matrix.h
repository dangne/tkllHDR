/*
 * matrix.h
 *
 *  Created on: Jun 16, 2019
 *      Author: dangn
 */

#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include "xil_printf.h"

#define LEN(a) (sizeof(a)/sizeof(a[0]))

#define ADD(c, a, b) {																						\
    if (!(LEN(a) == LEN(b) && LEN(a) == LEN(c) && LEN(a[0]) == LEN(b[0]) && LEN(a[0]) == LEN(c[0]))){		\
        xil_printf("Error: Matrices dimensions mismatch.\n");												\
    } else {																								\
        for (int i = 0 ; i < LEN(c) ; ++i)																	\
            for (int j = 0 ; j < LEN(c) ; ++j)																\
                c[i][j] = a[i][j] + b[i][j];																\
    }																										\
}

#define MUL(c, a, b) {																						\
    if (LEN(a[0]) != LEN(b) || (LEN(c) != LEN(a)) || (LEN(c[0]) != LEN(b[0]))){								\
        xil_printf("Error: Matrices dimensions mismatch.\n");												\
    } else {																								\
	    for (int i = 0; i < LEN(c) ; i++)																	\
	        for (int k = 0; k < LEN(c[0]) ; k++)															\
	            for (int j = 0; j < LEN(b) ; j++)															\
	                c[i][j] += a[i][k] * b[k][j];															\
    }																										\
}

#endif /* SRC_MATRIX_H_ */