/*!	\file		stats_Functions.c
	\author		Vitor Vieira Antunes
	\date		2019-02-12

	Program reads numerical value  pairs from file, store the values in a Array Structure,
	perform statistical calculations and prints results to the screen.
	
*/

#define _CRT_SECURE_NO_WARNINGS
#include "stats.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>


/*
	swapArrayElements
	Purpose: Swaps 2 elements in an Array, and does the same operation in a second array
	Accepts: 2 arrays and 2 ints
	Returns: void
*/

void swapArrayElements(dataType inArray[], dataType inArray2[], int element1, int element2)
{
	dataType tempValue = inArray[element1];
	inArray[element1] = inArray[element2];
	inArray[element2] = tempValue;
	dataType tempValue2 = inArray2[element1];
	inArray2[element1] = inArray2[element2];
	inArray2[element2] = tempValue2;
}

/*
	heapify
	Purpose: Checks 3 elements in an array and puts the largest value in the lowest position of the 3.
			If any swaps are made, it calls the heapify method again on the new position of the lowest value
	Accepts: 2 arrays and 2 ints
	Returns:void
*/
void heapify(dataType inArray[], dataType inArray2[], int parentNode, int arraySize)
{
	//assumes that the parent value is the largests until proven otherwise
	int largestNode = parentNode;
	int leftNode = parentNode * 2;//finds the vale to the left of the parent node in the heap tree
	int rightNode = leftNode + 1;// finds the vale to the right of the parent node in the heap tree
	if (leftNode <= arraySize && inArray[leftNode - 1] > inArray[(largestNode - 1)])//if the left node is larger than the parent
	{
		largestNode = leftNode;//left node becomes the largest
	}
	if (rightNode <= arraySize && inArray[rightNode - 1] > inArray[(largestNode - 1)])//if the right node is largest
	{
		largestNode = rightNode;//right becomes the largest
	}
	//if there was a change in the largest value swap the elements and call the method again in the swapped element on the lower part of the node
	if (largestNode != parentNode)
	{
		swapArrayElements(inArray, inArray2, (largestNode - 1), (parentNode - 1));
		heapify(inArray, inArray2, largestNode, arraySize);
	}

}
/*
	heapSort
	Purpose: Sorting function that swap elements in an array in order of lowest to highest
	Accepts: 2 arrays and 1 size_t
	Returns: void
*/

void heapSort(dataType inArray[], dataType inArray2[], size_t arraySize)
{

	//assembles the heap tree so that every node has the highes value on top
	//loops the values in the array from the lowest node to the highest one
	for (int nodeindex = (arraySize / 2); nodeindex > 0; nodeindex--)
	{
		//heapfy the node
		heapify(inArray, inArray2, nodeindex, arraySize);
	}
	//loop that put the highes value on the end of the array and remove it from the tree and heapfy the tree until there are no values left on the heap tree
	for (int index = arraySize - 1; index >= 0; index--)
	{
		swapArrayElements(inArray, inArray2, index, 0);
		arraySize--;// remove the swaped value from the heapifying operations

		heapify(inArray, inArray2, 1, arraySize);
	}
}


/*
	array
	Purpose: Creates an Structure of 2 empty arrays and int values
	Accepts: nothing
	Returns: Structure of 2 empty arrays and int values
*/
array_t array() {
	array_t arr = { NULL,NULL, 0, 0 };
	return arr;
}

/*
	array_push_back
	Purpose: Add values to an Array and increases the array size if necessary
	Accepts: 1 Structure of arrays, 1 double value to be added, 1 int
	Returns: bool
*/
bool array_push_back(array_t* pArray, array_value_t value, int targetData) {
	

	// Expand if necessary
	if (pArray->nSize == pArray->nCapacity) {
		size_t newCapacity = pArray->nCapacity * 2;
		if (newCapacity == 0) ++newCapacity;
		array_value_t* pNewBlock = realloc(pArray->data1, newCapacity * sizeof(array_value_t));
		array_value_t* pNewBlock2 = realloc(pArray->data2, newCapacity * sizeof(array_value_t));
		if (pNewBlock == NULL || pNewBlock2 == NULL)
			return false;

		pArray->data1 = pNewBlock;
		pArray->data2 = pNewBlock2;
		pArray->nCapacity = newCapacity;

	}
	if (targetData == 0) // if the value is the X of the pair
	{
		pArray->data1[pArray->nSize] = value;
		return true;
	}
	else if (targetData == 1) // if the value is the Y of the pair
	{
		pArray->data2[pArray->nSize++] = value;
		return true;
	}
	else
	{
		return false;
	}
}
/*
	getMax
	Purpose: finds the largest value in a ordered array
	Accepts: 1 array and 1 size_t value
	Returns: double
*/
dataType getMax(dataType inArray[], size_t size)
{
	return inArray[(size - 1)];
}
/*
	getMin
	Purpose: finds the lowest value in a ordered array
	Accepts: 1 array and 1 size_t value
	Returns: double
*/
dataType getMin(dataType inArray[])
{
	return inArray[0];
}
/*
	median
	Purpose:finds the median value in a ordered array
	Accepts: 1 array and 1 size_t value
	Returns: double
*/
double median(dataType inArray[], size_t size)
{
	if (size % 2 == 0)//If the number of elements is even
	{
		return (double)((inArray[size / 2]) + (inArray[((size / 2) - 1)])) / 2.0;
	}
	else// if the number of elements is odd
	{

		return (double)inArray[size / 2];
	}
}
/*
	mean
	Purpose:finds the mean value in a ordered array
	Accepts: 1 array and 1 size_t value
	Returns: double
*/
double mean(dataType inArray[], size_t size)
{
	double total = 0;
	//add all the value and divide by the number of elements
	for (int index = 0; index < (int)size; index++)
	{
		total += inArray[index];
	}
	return total / size;

}


/*
	variance
	Purpose:finds the variance value in a ordered array
	Accepts: 1 array and 1 size_t value
	Returns: double
*/
double variance(dataType inArray[], size_t size)
{
	double total = 0;
	double dataMean = mean(inArray, size);// finds the mean
	for (int index = 0; index < (int)size; index++)
	{
		total += (pow(((double)(inArray[index]) - dataMean), 2));
	}
	return (total / (size));
}
/*
	stdDeviation
	Purpose:finds the stadard deviation value in a ordered array
	Accepts: 1 array and 1 size_t value
	Returns: double
*/
double stdDeviation(dataType inArray[], size_t size)
{
	return sqrt(variance(inArray, size));
}
/*
	modeDetector	
	Purpose: Find the number of modes in an ordered frequency array
	Accepts: 2 arrays and a size_t	
	Returns: int
*/
int modeDetector(dataType inArray[], dataType inArray2[], size_t arraySize)
{

	if (inArray[arraySize - 1] == inArray[0])//if all have the same frequency
		return 0;
	int nOfModes = 0;//no mode
	nOfModes++;
	for (size_t i = arraySize - 1; i > 0; i--)//loops the array from most frequent to least
	{
		if (inArray[i] == inArray[i - 1])//if the next value has the same frequency than the current one
		{
			nOfModes++;//increase the number of modes
		}
		else
		{
			return nOfModes;// return number of modes
		}
	}
	return 0;
}

/*
	absoluteDeviation
	Purpose: Finds the absolute deviation in an array base on a given central tendency
	Accepts: 1 array, 1 size_t and 1 double
	Returns: double
*/
double absoluteDeviation(dataType inArray[], size_t size, double centralTendency)
{
	double total = 0;
	double temp = 0;
	for (int index = 0; index < (int)size; index++)
	{

		temp = ((double)(inArray[index]) - centralTendency);
		if (temp < 0)//makes negative values positive
			temp = temp * (-1);
		total += temp;
	}
	return (total / (size));
}


/*
	RegLineA
	Purpose: Calculates the a variable of the Regression Line
	Accepts: 2 arrays of x and y ints; size_t representing the size of the arrays; double variable b
	Returns: double variable a
*/
double RegLineA(dataType inArray1[], dataType inArray2[], size_t size, double b)
{
	//declares variables
	double a = 0;
	double sumY = 0;
	double sumX = 0;
	//loops the arrays summing the values of x and y
	for (size_t i = 0; i < size; i++)
	{
		sumY += inArray2[i];
		sumX += inArray1[i];
	}
	//applies regression line formula
	a = (sumY - (b * sumX)) / size;
	return a;

}
/*
	RegLineB
	Purpose: Calculates the b variable of the Regression Line
	Accepts: 2 arrays of x and y ints; size_t representing the size of the arrays
	Returns: double variable b
*/
double RegLineB(dataType inArray1[], dataType inArray2[], size_t size)
{
	//declares variables
	double b = 0;
	double sumY = 0;
	double sumX = 0;
	double sumXY = 0;
	double sumX2 = 0;
	//loops the arrays summing the values of x and y
	for (size_t i = 0; i < size; i++)
	{
		sumY += inArray2[i];
		sumX += inArray1[i];
		sumXY += (inArray1[i] * inArray2[i]);
		sumX2 += pow(inArray1[i], 2);
	}
	//applies regression line formula
	b = ((size * sumXY) - (sumX * sumY)) / ((size * sumX2) - pow(sumX, 2));

	return b;
}
/*
	array_free
	Purpose: free the memory from the arrays of a arrays structure
	Accepts: Structure of arrays
	Returns: void
*/
void array_free(array_t* pArray)
{
	free(pArray->data1);
	free(pArray->data2);
}