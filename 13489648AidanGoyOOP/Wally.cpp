#include "Wally.h"

Wally::Wally() //Wally image function
{
	int R = 49; //Number of rows wally has
	int C = 36; //Number of columns wally has
	matrix = new double*[R];
	for (int x = 0; x < R; ++x) 
	{
		matrix[x] = new double[C];
		for (int y = 0; y < C; ++y)
		{  
			matrix[x][y] = 0.0;
		}
	}
}
void Conversion(int rows, int cols, double* data, Wally*& image)
{
	int total = 0; //variable for total

	//For converting colour codes
	for (int RCount = 0; RCount < rows; RCount++)
	{
		for (int CCount = 0; CCount < cols; CCount++)
		{
			image->getValue(RCount, CCount, data[total]); //Get value from matrix class
			total++;
		}
	}
}
int Wally::getCols() //Get columns
{
	return startColumns; //returns start column
}
void Wally::SetColumns(int col) //Set columns
{
	startColumns = col; //Sets start column
}
int Wally::GetRows() //Get Rows
{
	return startRow; //Returns start row
}
void Wally::SetRows(int row) //Set Rows
{
	startRow = row; //Sets start row
}