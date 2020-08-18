/*!	\file		stats.c
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



int main(int argc, char* argv[]) {
	//add the source file as the file to parse
	FILE* stream = stdin;

	//create 3 structure of arrays
	array_t arrayStructure = array();//holds the x and y variables for the file variables
	array_t modearrayStructure = array();//holds the x values and frequencies
	array_t modearrayStructure2 = array();//holds the y values and frequencies


	// Check for too many arguments...
	if (argc > 2) {
		printf("Error: too many command-line arguments (%d)\n", argc);
		printf(
			"Usage: fcount_main [filename]\n"
			"\twhere filename is the name of a file.\n"
			"\tuse stdin if there is no filename.\n"
		);
		return EXIT_FAILURE;
	}
	// Check for filename...
	else if (argc == 2) {
		// Open the file in binary read mode.
		if ((stream = fopen(argv[1], "rb")) == NULL) {
			printf("error <%s> ", argv[1]);
			perror(" ");
			return EXIT_FAILURE;
		}
	}

	//declares variables
	char ch;
	bool endOfFile = false;
	dataType placeHolder = 0;// hold a temporary value from the file to be placed in the array
	int side = 1;//switch variable to flag if the value from the file goes in the x or y array
	int nOfModes;
	int nOfModes2;
	//loop that reads and writes numbers from file on arrays
	while (!endOfFile)
	{
		//loops while it can read numbers
		while (fscanf_s(stream, "%lf", &placeHolder) == 1)
		{
			//store number in the x array
			if (side == 1)
			{
				array_push_back(&arrayStructure, placeHolder, 0);
				side = 2;
			}
			//store number in the y array
			else if (side == 2)
			{
				array_push_back(&arrayStructure, placeHolder, 1);
				side = 1;
			}
		}
		//if end of file is reach, exits the loop
		if ((ch = fgetc(stream)) == EOF)
		{
			endOfFile = true;
		}
	}

	//loops the X values and register the frequencie of every value in another array
	for (int dataIndex = 0; dataIndex < (int)arrayStructure.nSize; dataIndex++)
	{
		bool isUnique = true;
		//checks if the value is already in the modearrayStructure, and increases the frequencie
		for (int modeIndex = 0; modeIndex < (int)modearrayStructure.nSize; modeIndex++)
		{
			if (arrayStructure.data1[dataIndex] == modearrayStructure.data1[modeIndex])
			{
				modearrayStructure.data2[modeIndex]++;
				isUnique = false;
			}

		}
		if (isUnique)//if the value was not in the array before, it is added to the array
		{
			array_push_back(&modearrayStructure, arrayStructure.data1[dataIndex], 0);
			array_push_back(&modearrayStructure, 1, 1);
		}

	}
	//loops the Y values and register the frequencie of every value in another array
	for (int dataIndex = 0; dataIndex < (int)arrayStructure.nSize; dataIndex++)
	{
		bool isUnique = true;
		//checks if the value is already in the modearrayStructure, and increases the frequencie
		for (int modeIndex = 0; modeIndex < (int)modearrayStructure2.nSize; modeIndex++)
		{
			if (arrayStructure.data2[dataIndex] == modearrayStructure2.data1[modeIndex])
			{
				modearrayStructure2.data2[modeIndex]++;
				isUnique = false;
			}

		}
		if (isUnique)//if the value was not in the array before, it is added to the array
		{
			array_push_back(&modearrayStructure2, arrayStructure.data2[dataIndex], 0);
			array_push_back(&modearrayStructure2, 1, 1);
		}

	}

	//Declaration of Bool variables that represent the type of modes of the data
	bool xHasNoMode = false;
	bool xIsMultiMode = false;
	bool yHasNoMode = false;
	bool yIsMultiMode = false;

	//Calculations for X
	//sort the arrays acording to the x values
	heapSort(arrayStructure.data1, arrayStructure.data2, arrayStructure.nSize);
	int size = arrayStructure.nSize;// size of the array
	dataType maxX = getMax(arrayStructure.data1, arrayStructure.nSize);// maximum X value
	dataType minX = getMin(arrayStructure.data1);// minimun X value
	double medianX = median(arrayStructure.data1, arrayStructure.nSize); // median X value
	double meanX = mean(arrayStructure.data1, arrayStructure.nSize); // Mean X value
	double varianceX = variance(arrayStructure.data1, arrayStructure.nSize); // variance X value
	double stdDevX = stdDeviation(arrayStructure.data1, arrayStructure.nSize); // Standard Deviation X value
	
	//Absolute Deviation for X
	double absDevMeanX = absoluteDeviation(arrayStructure.data1, arrayStructure.nSize, meanX);// according to the mean
	double absDevMedianX = absoluteDeviation(arrayStructure.data1, arrayStructure.nSize, medianX); // according to the Median
	double absDevModeX = 0; // Creates variable to possibly hold absolute Deviation for X according to the mode

	//Mode for X
	//sort the X frequency array 
	heapSort(modearrayStructure.data2, modearrayStructure.data1, modearrayStructure.nSize);
	nOfModes = modeDetector(modearrayStructure.data2, modearrayStructure.data1, modearrayStructure.nSize); //Number of X modes
	// Variable to hold the frequency and value of the mode
	dataType modeX; 
	int modeFrequX;
	//Depending on the number of modes, calculates the absolute deviation, and save the values of the mode and frequency in the variables
	if (nOfModes == 1)
	{
		modeX = modearrayStructure.data1[(modearrayStructure.nSize) - 1];
		modeFrequX = (int)modearrayStructure.data2[(modearrayStructure.nSize) - 1];
		absDevModeX = absoluteDeviation(arrayStructure.data1, arrayStructure.nSize, modeX);
	}
	else if (nOfModes == 0)
		xHasNoMode = true;
	else if (nOfModes > 1)
	{
		xIsMultiMode = true;
		modeFrequX = (int)modearrayStructure.data2[(modearrayStructure.nSize) - 1];
	}

	//Calculations for Y
	//sort the arrays acording to the y values
	heapSort(arrayStructure.data2, arrayStructure.data1, arrayStructure.nSize);
	dataType maxY = getMax(arrayStructure.data2, arrayStructure.nSize);	// maximum Y value
	dataType minY = getMin(arrayStructure.data2);	// minimun Y value
	double medianY = median(arrayStructure.data2, arrayStructure.nSize);// median Y value
	double meanY = mean(arrayStructure.data2, arrayStructure.nSize); // Mean Y value
	double varianceY = variance(arrayStructure.data2, arrayStructure.nSize);// variance Y value
	double stdDevY = stdDeviation(arrayStructure.data2, arrayStructure.nSize); // Standard Deviation Y value

	//Absolute Deviation for Y
	double absDevMeanY = absoluteDeviation(arrayStructure.data2, arrayStructure.nSize, meanY);//according to the Mean
	double absDevMedianY = absoluteDeviation(arrayStructure.data2, arrayStructure.nSize, medianY);//according to the Median
	double absDevModeY = 0;	// Creates variable to possibly hold absolute Deviation for Y according to the mode

	//Mode for Y
	//sort the X frequency array 
	heapSort(modearrayStructure2.data2, modearrayStructure2.data1, modearrayStructure2.nSize);
	nOfModes2 = modeDetector(modearrayStructure2.data2, modearrayStructure2.data1, modearrayStructure2.nSize);//number of Y modes
	// Variable to hold the frequency and value of the mode
	dataType modeY;
	int modeFrequY;

	//Depending on the number of modes, calculates the absolute deviation, and save the values of the mode and frequency in the variables
	if (nOfModes2 == 1)
	{
		modeY = modearrayStructure2.data1[(modearrayStructure2.nSize) - 1];
		modeFrequY = (int)modearrayStructure2.data2[(modearrayStructure2.nSize) - 1];
		absDevModeY = absoluteDeviation(arrayStructure.data2, arrayStructure.nSize, modeY);
	}		
	else if (nOfModes2 == 0)
		yHasNoMode = true;
	else if (nOfModes2 > 1)
	{
		yIsMultiMode = true;
		modeFrequY = (int)modearrayStructure2.data2[(modearrayStructure2.nSize) - 1];
	}

	//Sort by X
	heapSort(arrayStructure.data1, arrayStructure.data2, arrayStructure.nSize);
	//Calculates the Regression Line
	double regressionLineB = RegLineB(arrayStructure.data1, arrayStructure.data2, arrayStructure.nSize);
	double regressionLineA = RegLineA(arrayStructure.data1, arrayStructure.data2, arrayStructure.nSize, regressionLineB);
	double midX = (maxX + minX) / 2;
	double yAtMidX = (midX * regressionLineB) + regressionLineA;

	//Outliers
	int nOut2 = 0;//variable that holds the number of outliers
	int nOut3 = 0;
	//for loop that counts the number of outliersX2  
	for (size_t i = 0; i < arrayStructure.nSize; i++)
	{
		
		//if the difference between the element and the mean is bigger than 2 standard deviations, increase the outlier count
		if (((arrayStructure.data2[i] - meanY) > (2 * stdDevY) || (arrayStructure.data2[i] - meanY) < -(2 * stdDevY))
			&& (((arrayStructure.data2[i] - meanY) < (3 * stdDevY) || (arrayStructure.data2[i] - meanY) > -(3 * stdDevY))))
		{
			nOut2++;
		}
	}	
	//for loop that counts the number of outliersX3
	for (size_t i = 0; i < arrayStructure.nSize; i++)
	{
		//if the difference between the element and the mean is bigger than 2 standard deviations, increase the outlier count
		if ((arrayStructure.data2[i] - meanY) > (3 * stdDevY) || (arrayStructure.data2[i] - meanY) < -(3 * stdDevY))
		{
			nOut3++;
		}
	}
	

	//Printing results

	printf("Results:\n--------------------------------------------------------------\n");
	printf("# elements\t\t\t%d\t\t%d\n", size, size);
	printf("minimum\t\t\t\t%.3lf\t\t%.3lf\n", minX, minY);
	printf("maximum\t\t\t\t%.3lf\t\t%.3lf\n", maxX, maxY);
	printf("mean\t\t\t\t%.3lf\t\t%.3lf\n", meanX, meanY);
	printf("median\t\t\t\t%.3lf\t\t%.3lf\n", medianX, medianY);
	printf("mode\t\t\t\t");
	//Mode printing ----------------------------------------------------------------
	//X has no mode
	if (nOfModes == 0)
	{
		printf("no mode\t\t");
		if (nOfModes2 == 0)//Y has no mode
			printf("no mode\n");
		else if (nOfModes2 == 1)//Y has 1 mode
			printf("Freq. = %d\n\t\t\t\t\t\t%.3lf\n", modeFrequY,modeY);
		else if (nOfModes2 > 1)
		{
			printf("Freq. = %d\n", modeFrequY);
			for (int i = 1; i <= nOfModes2; i++)
			{
				printf("\t\t\t\t\t\t%.3lf\n ", modearrayStructure2.data1[(modearrayStructure2.nSize) - i]);
			}
		}
		
	}
	//X has 1 mode
	else if (nOfModes == 1)
	{
		printf("Freq. = %d\t", modeFrequX);
		if (nOfModes2 == 0)//Y has no mode
		{
			printf("no mode\n");
			printf("\t\t\t\t%.3lf\n", modeX);
		}
		else if (nOfModes2 == 1)//Y has 1 mode
		{
			printf("Freq. = %d\n", modeFrequY);
			printf("\t\t\t\t%.3lf\t\t%.3lf\n", modeX, modeY);
		}
		else if (nOfModes2 > 1)//Y is multimodal
		{
			printf("Freq. = %d\n", modeFrequY);
			printf("\t\t\t\t%.3lf\t\t%.3lf\n", modeX, modearrayStructure2.data1[(modearrayStructure2.nSize) - 1]);
			for (int i = 2; i <= nOfModes2; i++)
			{
				printf("\t\t\t\t\t\t%.3lf\n ", modearrayStructure2.data1[(modearrayStructure2.nSize) - i]);
			}
		}
	}
	//X is multimodal
	else if (nOfModes > 1)
	{
		printf("Freq. = %d\t", modeFrequX);
		if (nOfModes2 == 0)//Y has no mode
		{
			printf("no mode\n");
			for (int i = 1; i <= nOfModes; i++)
			{
				printf("\t\t\t\t%.3lf\n", modearrayStructure.data1[(modearrayStructure.nSize) - i]);
			}
		}
		else if (nOfModes2 == 1)//Y has 1 mode
		{
			printf("Freq. = %d\n", modeFrequY);
			printf("\t\t\t\t%.3lf\t\t%.3lf\n", modearrayStructure.data1[(modearrayStructure.nSize) - 1], modeY);
			for (int i = 2; i <= nOfModes; i++)
			{
				printf("\t\t\t\t%.3lf\n", modearrayStructure.data1[(modearrayStructure.nSize) - i]);
			}
		}
		else if (nOfModes2 > 1)//Y is multimodal
		{
			printf("Freq. = %d\n", modeFrequY);
			for (int i = 1; i <= nOfModes; i++)
			{
				printf("\t\t\t\t%.3lf", modearrayStructure.data1[(modearrayStructure.nSize) - i]);
				if (i <= nOfModes2)
					printf("\t\t%.3lf", modearrayStructure2.data1[(modearrayStructure2.nSize) - i]);
				printf("\n");
			}
		}
	}
	//End of mode printing ------------------------------------------------------------------
	printf("variance\t\t\t%.3lf\t\t%.3lf\n", varianceX, varianceY);
	printf("std. dev.\t\t\t%.3lf\t\t%.3lf\n", stdDevX, stdDevY);
	printf("mean absolute deviations:\n");
	printf("-> about the mean\t\t%.3lf\t\t%.3lf\n", absDevMeanX, absDevMeanY);
	printf("-> about the median\t\t%.3lf\t\t%.3lf\n", absDevMedianX, absDevMedianY);
	printf("-> about the mode");
	if (nOfModes==0)
		printf("\t\tno mode\t");
	else if (nOfModes==1)
		printf("\t\t%.3lf\t", absDevModeX);
	else if (nOfModes>1)
		printf("\t\tMulti-modal");
	if (nOfModes2 == 0)
		printf("\tno mode\n");
	else if (nOfModes2 == 1)
		printf("\t%.3lf\n", absDevModeY);
	else if (nOfModes2 > 1)
		printf("\tMulti-modal\n");
	printf("regression line\t\t\ta=%.3lf\tb=%.3lf\n", regressionLineA, regressionLineB);
	printf("Y at mid(X)\t\t\tx=%.3lf\ty=%.3lf\n", midX, yAtMidX);
	printf("Outliers(2x)\t\t\t");
	if (nOut2 > 0)
	{
		printf("# outliers =%d\n", nOut2);
		//loops the array looking for outlier values
		for (size_t i = 0; i < arrayStructure.nSize; i++)
		{

			//if the difference between the element and the mean is bigger than 2 standard deviations, prints the element
			if (((arrayStructure.data2[i] - meanY) > (2 * stdDevY) || (arrayStructure.data2[i] - meanY) < -(2 * stdDevY))
				&& (((arrayStructure.data2[i] - meanY) <= (3 * stdDevY) || (arrayStructure.data2[i] - meanY) >= -(3 * stdDevY))))
			{
				printf("\t\t\t\t%.3lf\t\t%.3lf\n", arrayStructure.data1[i], arrayStructure.data2[i]);
			}
		}
	}		
	else
		printf("no outliers\n");
	printf("Outliers(3x)\t\t\t");
	if (nOut3 > 0)
	{
		printf("# outliers =%d\n", nOut3);
		//loops the array looking for outlier values
		for (size_t i = 0; i < arrayStructure.nSize; i++)
		{

			//if the difference between the element and the mean is bigger than 2 standard deviations, prints the element
			if ((arrayStructure.data2[i] - meanY) > (3 * stdDevY) || (arrayStructure.data2[i] - meanY) < -(3 * stdDevY)) 
			{
				printf("\t\t\t\t%.3lf\t\t%.3lf\n", arrayStructure.data1[i], arrayStructure.data2[i]);
			}
		}
	}
	else
		printf("no outliers\n");

	//Releasing the memory
	array_free(&arrayStructure);
	array_free(&modearrayStructure);
	array_free(&modearrayStructure2);
	fclose(stream);

	return EXIT_SUCCESS;

}