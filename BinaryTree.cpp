///////////////////////////////////////////////////////////////////////////////////////////////
// -Program Summary:
// 
//  This program will add numerical data only from a user-provided file to a binary tree. The
//  numerical values added will only be between 0 - 99. The program will filter out for any garbage
//  items in the file such as characters or anything else. Each number found will be inserted into
//  the tree, iterating either left or right depending on the value of the inserted node. Depth counters
//  will be assigned to each node created. Once tree is fully populated, the items in tree will be 
//  written to a file in low-high order by iterating to bottom of tree for lowest values first &
//  gradually returning the node greater than itself until reaching max value.
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

struct node*& insert(node*&, int, int);
struct node* readFile(ifstream&, node*&);

//  Prompt user for filename if not passed: 
string getFile();

//  Files
bool isOnlyDigits(const string&);

int readFile(ifstream&);

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
    
    writeFile << "[Data from Binary Tree in Lowest to High:] " << endl;

    inOrder(Root, writeFile);

    cout << "Data written to file (tree.txt) " << endl;

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

//  Once moving up, decrement depth counter
    counter--;
    return Root;
}

//     Grabs each file value, checks for numbers 0-99 only & inserts them to tree:
struct node* readFile(ifstream& readFile, node *&Root)
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
    return Root;
}

//   Write each node's value by calling itself, passing in each node's ->left & ->right 
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