#include "Matrix.h"

Matrix::Matrix() //Constructor
{

}

Matrix::~Matrix() //Destructor
{

}

Matrix::Matrix(int numRows, int numCols)
{
	R = numRows; // R = Num Rows
	C = numCols; // C = Num Cols
	
	matrix = new double*[R]; //New double rows
	for (int x = 0; x < R; ++x)
	{
		matrix[x] = new double[C]; //New double columns
		for (int y = 0; y < C; ++y)
		{
			matrix[x][y] = 0.0;
		}
	}
}
double* Matrix::get(int row, int col, int numrows, int numcols) //Get matrix area
{
	double* SearchArea = new double[numrows * numcols]; //Search area = Num rows x Num cols
	int total = 0; //Variable for total
	for (int RCount = row; RCount < row + numrows; RCount++)
	{
		for (int CCount = col; CCount < col + numcols; CCount++)
		{
			SearchArea[total] = matrix[RCount][CCount];
			total++; //Increases total
		}
	}
	return SearchArea; //Returns Matrix Area
}

double** Matrix::returnMatrix() const
{
	return matrix; //Returns the matrix
}

void Matrix::getValue(int row, int col, int value)
{
	matrix[row][col] = value; //Assigns a value
}


double Matrix::SSDCalculation(double* wallyMatrix, double* sceneMatrix, int wallyRows, int WallyColumns) //This is the SSD calculation
{

	double SSD = 0; //Variable for the SSD
	double difference = 0; //Variable for the difference

	for (int x = 0; x < wallyRows * WallyColumns; x++) //SSD calculations take place
	{
		if (wallyMatrix[x] < 255) //If wally matrix is less than 255
		{
			difference = sceneMatrix[x] - wallyMatrix[x]; //Difference = scene matrix - Wally matrix
			SSD += difference * difference; //SSD 
		}
	}

	return SSD; //Returns the SSD
}

double Matrix::getSSD() //This gets the SSD
{
	return SSD; //Returns the ssd
}

void Matrix::SetSSD(double Score) //This sets the SSD
{

	SSD = Score; //Sets SSD to what score is
}
