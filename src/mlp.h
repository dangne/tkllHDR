/*
 * mlp.h
 *
 *  Created on: Jun 16, 2019
 *      Author: tienanh
 */

#ifndef SRC_MLP_H_
#define SRC_MLP_H_

#include <math.h>
#include "matrix.h"
#include "layers.h"
#include "xil_printf.h"

// Number of units in each layer
#define UNIT_LAYER_INPUT	784
#define UNIT_LAYER_1		64
#define UNIT_LAYER_OUTPUT	10

// Define macros
#define RELU(a) {													\
    for (int i = 0 ; i < LEN(a) ; ++i)								\
        for (int j = 0 ; j < LEN(a[0]) ; ++j)						\
            a[i][j] = (a[i][j] > 0 ? a[i][j] : 0);					\
}

#define SOFTMAX(a) {												\
    double sum = 0;													\
	for(int i = 0 ; i < LEN(a) ; i++)								\
    	for (int j = 0 ; j < LEN(a[0]) ; j++)						\
            sum += (a[i][j] = exp(a[i][j]));						\
	for(int i = 0 ; i < LEN(a) ; i++)								\
    	for (int j = 0 ; j < LEN(a[0]) ; j++)						\
    		a[i][j] /= sum;											\
}

#define MLP(input) {												\
	xil_printf("Inside MLP\n");										\
    double w0[UNIT_LAYER_INPUT][UNIT_LAYER_1] = WEIGHT_0;			\
    xil_printf("Inside MLP 1\n");									\
    double b0[1][UNIT_LAYER_1] = BIAS_0;							\
    xil_printf("Inside MLP 2\n");									\
    double w1[UNIT_LAYER_1][UNIT_LAYER_OUTPUT] = WEIGHT_1;			\
    xil_printf("Inside MLP 3\n");									\
    double b1[1][UNIT_LAYER_OUTPUT] = BIAS_1;						\
    xil_printf("Inside MLP 4\n");									\
    																\
    double hidden[1][64];											\
    MUL(hidden, input,  w0);										\
    ADD(hidden, hidden, b0);										\
    RELU(hidden);													\
																	\
	xil_printf("Inside MLP 5\n");									\
    double output[1][10];											\
    MUL(output, hidden, w1);										\
    ADD(output, output, b1);										\
    RELU(output);													\
    SOFTMAX(output);												\
    																\
	xil_printf("Inside MLP 6\n");									\
	result = 0;														\
    for (int i = 0 ; i < LEN(output[0]) ; i++)						\
    	if (output[0][i] > output[0][result])						\
    		result = i;												\
																	\
	xil_printf("Inside MLP 7\n");									\
}
#endif /* SRC_MLP_H_ */