#include <iostream> //iostream
#include <fstream> //fstream
#include <sstream> //sstream
#include "Wally.h" //--
#include "Matrix.h" //--Header Files
#include "Scene.h" //--
using namespace std; 

double* readText(string fileName, int sizeRows, int sizeCols); //This allows the files to be read into the program
string WallyFile = "Wally_grey.txt";//Reads in the wally file
string SceneFile = "Cluttered_scene.txt";//Reads in the text file
void Conversion(int rows, int cols, double* data, Wally*& image); //Converts the pixels of wally grey into objects
void Conversion(int rows, int cols, double* data, Scene*& image);//Converts pixels of cluttered scene into object
void WritePGM(string filename, double* data, int sizeRows, int sizeCols, int Q); //Converts text to pgm
string Output = "Output.pgm"; //This is what the output file will be called

//Here is the menu system of the program, which gives two options to the user to the user, one to start the search and the other to close the program
int MainMenu() //This is where the user can decide if they want to either begin the search or close the program
{
	int selection; //For storing the users selection
	cout << "Please make a selection" << endl; 
	cout << "1 - Start" << endl; //Provides an option to begin the search for wally
	cout << "2 - End" << endl; //Provides an option to end the program
	cin >> selection; //Input stored here
	cout << "The program will end when the output file has been created - Please wait" << endl;
	return selection; //Returns user selection and perfroms the relvant action
}

int main() //Main starts here 
{
	int selection = MainMenu(); //Variable for main menu selection, calls main menu
	int RowsTotal; //Variable for total rows
	int ColumnTotal; //Variable for total columns
	int SSD; //variable for SSD
	int SceneRows = 768; //number of rows in the scene image
	int SceneColumns = 1024;// number of columns in the scene image
	int WallyRows = 49; // number of rows in the wally image
	int WallyColumns = 36; // number of columns in the wally image
	int Q = 255; //Q is used as it is greyscale 1 is for binary.
	double* SceneData; //Creates Scene data pointer
	double* WallyData; //Creates wally data pointer
	double* SearchArea; //Creates search area pointer
	Wally* WallyImage = new Wally();
	Scene* sceneImage = new Scene(SceneRows, SceneColumns); 
	SceneData = readText(SceneFile, SceneRows, SceneColumns); //Scene data stored into array
	WallyData = readText(WallyFile, WallyRows, WallyColumns); //Wally data stored into array
	Conversion(WallyRows, WallyColumns, WallyData, WallyImage); //Wally colour codes set
	Conversion(SceneRows, SceneColumns, SceneData, sceneImage); //Scene colour codes set
	double* wally_Matrix_Area = WallyImage->get(0, 0, WallyRows, WallyColumns); // Retrieves 1d array.
	Wally* Temporary = new Wally(); //Creates a temporary wally object used for the SSD comparisons

	//Menu system options, also used later when calling SSD and draw functions
	if (selection == 1) //If the user selects 1
	{
		ColumnTotal = 1; //This is how the search option finds wally
		RowsTotal = 1;
	}
	else if (selection == 2) //If the user selects 2
	{
		return 0; //This provides a way for the user to exit the program
	}
	// This is a loop that works out similarities in values and where SSD takes place from matrix
	for (int RCount = 0; RCount < SceneRows - WallyRows; RCount = RCount + RowsTotal) 
	{  
		for (int CCount = 0; CCount < SceneColumns - WallyColumns; CCount = CCount + ColumnTotal) 
		{
			// gets the 1d array
			SearchArea = sceneImage->get(RCount, CCount, WallyRows, WallyColumns);

			if (selection == 1) //Selection 1 from the menu will begin this search 
			{
				//ssd calculation is called from the matrix and calculations take place
				SSD = sceneImage->SSDCalculation(wally_Matrix_Area,SearchArea,WallyRows,WallyColumns); 
			}
			delete[] SearchArea; //Deletes data in the matrix

			if (RCount == 0 && CCount == 0) //If row count and Col Count are both 0
			{
				if (selection == 1) 
				{
					// Sets values in the temporary object
					Temporary->SetColumns(CCount); //Sets Columns
					Temporary->SetRows(RCount); //Sets Rows
					Temporary->SetSSD(SSD); //Sets SSD
				}
			}

			//if new ssd is smaller than what is currently stored, it will replace it.
			if (selection == 1) 
			{
				if (SSD < Temporary->getSSD()) 
				{
					Temporary->SetColumns(CCount); //Set columns
					Temporary->SetRows(RCount); //Sets rows - Sets values in the temp object created earlier
					Temporary->SetSSD(SSD); //set new SSD value
					
				}
			}
		}
	}
	//This draws on the scene using the draw function from the scene class and then outputs the file
	if (selection == 1)
	{	
			//Calls Draw Box from scene class to draw wallys location on the scene using data stored in the temportary object
			SceneData = sceneImage->DrawBox(Temporary->GetRows(),Temporary->getCols(),SceneData,WallyRows,WallyColumns,SceneColumns); 
			WritePGM(Output,SceneData,SceneRows,SceneColumns,Q); //Writes to PGM
	}
}
//Below is the Read/Write code provided with the assignment
//Reads the text file of sizes of Rows x Collumns and converts to an array of doubles
double* readText(string fileName, int sizeRows, int sizeCols)
{

	double* data = new double[sizeRows * sizeCols];

	int x = 0;

	ifstream myfile;
	myfile.open(fileName, ios::in);

	if (myfile.is_open())
	{

		while (myfile.good()) 
		{
			
			if (x > sizeRows * sizeCols - 1)
				break;
			myfile >> *(data + x);
			x++;
		}

		myfile.close();
	}

	else {
		cout << "Unable to open file" << endl;
	}

	return data;
}

// Converts the data to PGM
void WritePGM(string filename, double* data, int sizeRows, int sizeCols, int Q)
{

	int x;
	unsigned char* image;

	ofstream myfile;

	image = (unsigned char*)new unsigned char[sizeRows * sizeCols];

	// convert the integer values to unsigned char

	for (x = 0; x < sizeRows * sizeCols; x++)
		image[x] = (unsigned char)data[x];

	myfile.open(filename, ios::out | ios::binary | ios::trunc);

	if (!myfile) 
	{
		cout << "Unable to open file " << filename << endl;
		exit(1);
	}

	myfile << "P5" << endl;
	myfile << sizeCols << " " << sizeRows << endl;
	myfile << Q << endl;

	myfile.write(reinterpret_cast<char*>(image), (sizeRows * sizeCols) * sizeof(unsigned char));

	if (myfile.fail())
	{
		cout << "unable to write image" << filename << endl;
		exit(0);
	}

	myfile.close();

	delete[] image;
}