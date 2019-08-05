#ifndef SearchArea_h
#define SearchArea_h
#include <stdio.h>
#include "matrix.h"

#pragma once

class SearchArea : public Matrix {
	SearchArea(int cols, int rows)
		: Matrix(cols, rows)
	{
	}
	void getValue(int SSDValue);
	void setRows(int row);
	void setCols(int col);
	float getValue();
	int GetRows();
	int getCols();


protected:
	float SSD; //Variable for sd
	int StartRows; //variable for startung row
	int StartCols; //variable for starting columns
};
class Scene : public Matrix {
public:
	Scene(int cols, int rows)
		: Matrix(cols, rows)
	{
	}
	Scene();

	double* DrawBox(int lastRow, int lastCol, double* SceneData, int wallyRows, int WallyColumns, int SceneColumns); //Draw Box
};

#endif
