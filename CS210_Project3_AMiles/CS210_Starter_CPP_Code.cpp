#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>

using namespace std;


/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("CS210_Starter_PY_Code");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int CallIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"CS210_Starter_PY_Code");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int CallIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"datamaths");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

/*
Description:
	Function to display main menu and returns user's choice in int format
Example:
	int userChoice = mainMenu();
Return:
	integers 1, 2, 3, or 4 depending on user's choice
*/
int MainMenu() {
	//display options 1-4 and validate input
	string userInput;

	//display menu options
	cout << "Please choose from the following:" << endl;
	cout << "1: Display list of purchased items with their respective purchase count" << endl;
	cout << "2: Display the number of times a specific item was purchased" << endl;
	cout << "3: Display item popularity histogram." << endl;
	cout << "4: Exit" << endl;

	//loop entry prompt until input is correct
	do{
		cout << "Enter 1, 2, 3, or 4: ";
		cin >> userInput;
	} while (userInput != "1" && userInput != "2" &&
			userInput != "3" && userInput != "4");

	//new line for spacing
	cout << endl;

	//return user's choice as integer
	return stoi(userInput);

}

/*
Description:
	Displays all items purchased from read file
Example:
	displayAllItemsCount();
Return:
	nothing, only displays to screen
*/
void DisplayAllItemsCount() {
	CallProcedure("DisplayAllItemCount");
}

/*
Description:
	Asks for requested item name, then displays purchase count of item. 
	if item was not found from data file, displays "was not found"
Example:
	displayItemCount();
Return:
	Nothing, only displays item count
*/
void DisplayItemCount() {
	//string to hold user request item name
	string userItem;
	//variable to hold item count
	int itemPurchaseCount;
	//prompt for item name
	cout << "Please enter an item name: ";
	//store item name
	cin >> userItem;
	//get item count from python code
	itemPurchaseCount = CallIntFunc("DisplayItemCount", userItem);
	//if item count was returned:
	if (itemPurchaseCount != -1) {
		//display it:
		cout << "Number of item purchased: " << itemPurchaseCount << endl;
	}
	else {
		cout << "Item '" << userItem << "' was not found in item purchase data." << endl;
	}

	//display new line for visual purposes
	cout << endl;
}

/*
Description:
	Prints character count number of times with no new line.
Example:
	printChars('*', 10);
	//prints: **********
Return:
	nothing, just prints to screen.
*/
void PrintChars(char character, int count) {
	//loop through count and print each character
	for (int i = 0; i < count; i++) {
		cout << character;
	}
}

/*
Description:
	Displays item histogram, also calls python function to create file with
	each item and it's count listed.
Example:
	displayItemHistorgram();
Return:
	returns nothing, just displays histogram of items.
*/
void DisplayItemHistogram() {
	//get variables ready to read a file and display contents
	string itemCountStr;
	int itemCount;
	string itemName;
	const int NAME_COL_WIDTH = 12;//to hold width of name column in histogram

	//have python write out the frequency file
	CallProcedure("WriteOutFrequency");

	//open up file for reading
	ifstream reader("frequency.dat");

	//title for displaying:
	cout << "Frequency Histogram:" << endl;

	string rawInput;
	//loop through file contents
	while (!reader.eof()) {
		//read item into item name
		reader >> itemName;
		//read count into temporary string
		reader >> itemCountStr;
		//convert count string to item's purchase count
		itemCount = stoi(itemCountStr);
		//display item and graph line
		cout << itemName;
		PrintChars(' ', NAME_COL_WIDTH - itemName.size());
		cout << '|';
		PrintChars('>', itemCount);
		cout << endl;

	}

	//print new line for visual effect
	cout << endl;

	//close file when done
	reader.close();

}


//main function
void main()
{
	//print title
	PrintChars('-', 51);
	cout << endl;
	cout << "Welcome to the Corner Grocer Item Tracking Program!" << endl;
	PrintChars('-', 51);
	cout << endl;

	//to keep track of exit condition
	bool userWantsExit = false;

	//main program loop
	while (!userWantsExit) {
		//start a logic switch on user menu choice
		switch (MainMenu()) {
		case 1:
			//display full list of items and their purchase count
			DisplayAllItemsCount();
			break;
		case 2:
			//display specific item count
			DisplayItemCount();
			break;
		case 3:
			//display item popularity histogram
			DisplayItemHistogram();
			break;
		case 4:
			//set our exit condition to true
			userWantsExit = true;
			break;
		}
	}//end program loop

}