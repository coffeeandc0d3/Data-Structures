///////////////////////////////////////////////////////////////////////////////////////////////

// -Program Summary:
// 
//  This program will seek to insert numerical data from an unsorted file. Data found in file must be numeric and within 0-99.
//  Will filter data in file for garbage items/non-numeric values.
//  Inserts numbers found in file into tree by iterating left or right, comparing values of proximal nodes. 
//  ->left nodes will be values less than insertion value, ->right nodes will be greater 
//  Once empty location is found, inserts node at that location. 
//  For each node created, it's corresponding depth counter is assigned. 
//
//  After populating tree, will write data to file in low-high order. 
//  To traverse tree leftward, program will pass nodes to tree recursively. 
//  Recursive logic will pass ea. node's ->right into function to access its ->left node's data.
//  Since left-ward values are lowest, data will be sorted throughout traversal.
//
//  Each node's value throughout traversal will be written to file (tree.txt) in current dir. 
//
//  Justin C. Shows
//  20201105
//
//  Justin C. Shows
//  20201105
// ////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <fstream>
using namespace std; 

struct node 
{
    int data;
    int depthCounter;
    
    node* left;
    node* right;
};

//  Inserts node at vacant location
struct node*& insert(node*&, int, int);

//  Read from unsorted file for #'s (0-99 only)
int readFile(ifstream&, node*&);

//  Prompt user for filename if not passed: 
string getFile();

//   Check if string is only a number:
bool isOnlyDigits(const string&);

//   Traverse tree leftward recursively
void inOrder(struct node*, ofstream&);

//  Files to read & write from:
string InputFile = "";
string OutputFile = "tree.txt";

//  Driver code: 
int main(int argc, char* argv[])
{
//  Get filename from user: 

    if (argc != 2) 
    {
        InputFile = getFile();
    } 

//  If user passed file in cmd line, grab it:

    else { InputFile = argv[1]; }

    if (InputFile == "") { cout << "Filename still not found, closing... "; return 1; }

    cout << "File entered: " << InputFile << endl << endl;

//  Create the root as the initial reference for tree:

    struct node* Root;

    Root = NULL;

//  Open file provided filename from user:

    ifstream file;
    file.open(InputFile);

//  Fill tree with data, updating root each time

    readFile(file, Root);
        
//  Will write to file the data from tree:

    ofstream writeFile;
    writeFile.open(OutputFile);

//  Traverse populated tree low-high:
    
    writeFile << "Data " << "\t" << "Level" << endl << endl;

    inOrder(Root, writeFile);

    cout << endl << "Data written to file (tree.txt). " << endl;

//  Finished w/ file: 

    file.close();

//  Finished writing to file w/ tree data: 

    writeFile.close();

    return 0;
}

//   If any character in string is not a number, returns false, otherwise true
bool isOnlyDigits(const string& stringOther)
{
    return (stringOther.find_first_not_of("0123456789") == string::npos);
}

//   Called if filename wasn't passed, returns string that represents filename to read from
string getFile()
{
    string userInput = "";
    cout << "Please enter filename: " << endl;

    cin >> userInput;

    return userInput;
}

//   Compares '< or >' for ea. node & the insertion value. Inserts at empty location:  
struct node*& insert(node*& Root, int data, int counter)
{
//  Base case is vacant node location after traversal
    if (Root == NULL)
    {
         Root = new (node);

         Root->left = NULL;
         Root->right = NULL;

         Root->depthCounter = counter;
         Root->data = data;

//       Show data from file in original order:
         cout << Root->data << "\t" << endl;
    }
    else
    {
//      Each new level, add depth counter
        ++counter;

        if (data < Root->data)
        {
              Root->left = insert(Root->left, data, counter);
        }
        else if (data > Root->data)
        {
              Root->right = insert(Root->right, data, counter);
        }
    }

    counter--;
    return Root;
}

//   Grabs each file value, checks for numbers 0-99 only & inserts them to tree:
int readFile(ifstream& readFile, node *&Root)
{
    if (readFile.is_open() == false) { cout << "Could not open or find file. " << endl; exit(1); }

    while (readFile && !readFile.eof())
    {
//      This will store each item of data found in file:
        string stringData = "";

//      Grab next set of characters in file, may or may not be valid data
        readFile >> stringData;
        
        if (stringData != "") 
        {
//           Check if characters just read are only digits
             if (isOnlyDigits(stringData) == true)
             {
//                This stores each valid number in file
                  int value = 0;

//                Convert valid number string to int:
                  value = stoi(stringData);

//                Insert new number into tree:
                  if (value >= 0 && value <= 99)
                  {
                      insert(Root, value, 0);
                  }   else { continue; }
             }
        }
    }
    
    return 0;
}

//   Traverses tree leftward by passing each node's ->right in function to access it's left node: 
void inOrder(struct node* Root, ofstream& writeFile)
{
    if (Root)
    {
         inOrder(Root->left, writeFile);

//       Write node value to file for each traversal 
         writeFile << Root->data << "\t" << Root->depthCounter << endl;

         inOrder(Root->right, writeFile);
    }

}
