#pragma once
#ifndef Wally_header
#define Wally_header
#include "matrix.h"
#include <stdio.h>
class Wally : public Matrix {
public: //Public Variables etc
	Wally();

	Wally(int cols, int rows)
		: Matrix(cols, rows)
	{

	}
	void SetRows(int row);
	void SetColumns(int col);
	int GetRows();
	int getCols();

protected: //Protected Variables
	int startRow; //Variable for the starting rows
	int startColumns; //Variable for the starting column
};

#endif
