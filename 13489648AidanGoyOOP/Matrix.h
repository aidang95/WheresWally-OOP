#pragma once
#define matrix_header


class Matrix {
public: //Public variables etc
	Matrix();
	Matrix(int numrows, int numcols);

	~Matrix();
	void getValue(int R, int C, int value);
	void SetSSD(double Score);
	double SSDCalculation(double* wallyMatrix, double* sceneMatrix, int wallyRows, int WallyColumns);
	double getSSD();
	double** returnMatrix() const;
	double* get(int row, int col, int R, int C);

protected: //Protected Variables
	double SSD; //Variable for the SSD
	int R; //Variable for rows
	int C;  //variable fow collumns
	double** matrix; 
};
