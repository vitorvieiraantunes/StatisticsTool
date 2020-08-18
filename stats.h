/*!	\file		stats.h
	\author		Vitor Vieira Antunes
	\date		2019-02-12

	Program reads numerical value  pairs from file, store the values in a Array Structure,
	perform statistical calculations and prints results to the screen.
*/

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>


typedef double dataType;

void swapArrayElements(dataType inArray[], dataType inArray2[], int element1, int element2);


void heapify(dataType inArray[], dataType inArray2[], int parentNode, int arraySize);

void heapSort(dataType inArray[], dataType inArray2[], size_t arraySize);

typedef dataType array_value_t;

//Structure of 2 arrays and 2 values for size and capacity
typedef struct array_t_tag {
	array_value_t* data1;
	array_value_t* data2;
	size_t			nSize;
	size_t			nCapacity;
} array_t;

array_t array();

bool array_push_back(array_t* pArray, array_value_t value, int targetData); 

dataType getMax(dataType inArray[], size_t size);

dataType getMin(dataType inArray[]);

double median(dataType inArray[], size_t size);

double mean(dataType inArray[], size_t size);

double variance(dataType inArray[], size_t size);

double stdDeviation(dataType inArray[], size_t size);

int modeDetector(dataType inArray[], dataType inArray2[], size_t arraySize);

double absoluteDeviation(dataType inArray[], size_t size, double centralTendency);

double RegLineA(dataType inArray1[], dataType inArray2[], size_t size, double b);

double RegLineB(dataType inArray1[], dataType inArray2[], size_t size);

void array_free(array_t* pArray);
