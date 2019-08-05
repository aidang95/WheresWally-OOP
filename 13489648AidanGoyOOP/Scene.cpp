#include "Scene.h"

Scene::Scene() //Cluttered scene function
{
	int C = 1024; //Number of columns in scene	
	int R = 768; //Number of rows in scene
	matrix = new double*[C];
	for (int x = 0; x < x; ++x)
	{
		matrix[x] = new double[R];
		for (int y = 0; y < R; ++y)
		{
			matrix[x][y] = 0.0;
		}
	}
}
void Conversion(int rows, int cols, double* data, Scene*& image) 
{
	int total = 0; //Variable for total

	//For converting colouur codes
	for (int RCount = 0; RCount < rows; RCount++) {
		for (int CCount = 0; CCount < cols; CCount++) {
			image->getValue(RCount, CCount, data[total]); //Get value from matrix class
			total++;
		}
	}
}
int SearchArea::GetRows() //Get rows
{
	return StartRows; //Return start rows
}
void SearchArea::setRows(int row) //Set rows
{
	StartRows = row; //Set start rows
}

int SearchArea::getCols() //Get columns
{
	return StartCols; //Return start columns
}
void SearchArea::setCols(int col) //Set columns
{
	StartCols = col; //Set start column
}

//SSD Value and return
void SearchArea::getValue(int SSDValue)
{
	SSD = SSDValue; //Sets SSD
}

float SearchArea::getValue()
{
	return SSD; //Returns SSD
}
//This is for drawing the location of wally
double* Scene::DrawBox(int lastCol, int lastRow, double* SceneData, int wallyRows, int WallyColumns, int SceneColumns)
{
	for (int CCount = lastCol; CCount <= lastCol + WallyColumns; CCount++)
	{
		for (int RCount = lastRow; RCount <= wallyRows + lastRow; RCount++)
		{	
			if (CCount == lastCol || CCount == WallyColumns + lastCol) //If column count is the last row or column count = last column + wally columns
			{
				for (int x = 0; x < 2; x++) //Setting size of box to be drawn
				{
					SceneData[SceneColumns * (RCount - x) + (CCount - x)] = 0;
				}
			}
			if (RCount == lastRow || RCount == lastRow + wallyRows) //If row count is the last row or row count = last row + wally rows
			{
				for (int x = 0; x < 2; x++) //Setting size of box to be drawn
				{
					SceneData[SceneColumns * (RCount - x) + (CCount - x)] = 0;
				}
			}
		}
	}
	return SceneData; //Returns scene data
}





