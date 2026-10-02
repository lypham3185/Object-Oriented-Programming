#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<random>

using namespace std;

//------------------------PROTOTYPE-------------------------------------------
void promptFile(vector<string> &);
void printVec(vector<string>);
int ranGen(int size);
bool readFile(string filename, vector<string> & vec);
bool writeFile(string filename, const vector<string> & v0, const vector<string> & v1);

int main()
{
    vector<string> roster;
    vector<string> qBank;
    readFile("2310_F26_Rosters.csv", roster);
    readFile("Questions.csv", qBank);
    // printVec(roster);
    // printVec(qBank);

    // cout << "Size of roster: " << roster.size() << endl;
    // cout << "Size of qBank: " << qBank.size() << endl;

    writeFile("Student_question_bank.csv", roster, qBank);
}

//------------------------DECLARATIONS-------------------------------------------
/**
 * @brief prompts the user to give a file to read
 */
void promptFile(vector<string> & v){
    cout << "file to read?\n";
    string myFile = "";
    cin >> myFile;
    readFile(myFile, v);
}

/**
 * @brief prints out the elements in v
 * @param v vector of strings to print
 */
void printVec(vector<string> v){
    for(int i = 0; i < v.size(); i++){
        cout << v[i] << endl;
    }
}

/**
 * @brief randomly returns an index from 0 to size-1
 * @param size number of questions
 * @return int index of question
 */
int ranGen(int size){
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, size - 1);
    return dist(gen);
}

/**
 * @brief reads contents of filename and populates into vec
 * @param filename name of the input file
 * @param vec vector filled with each line
 * @return true if the file opened, false otherwise
 */
bool readFile(string filename, vector<string> & vec) {
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file\n";
        return false;
    }

    string line;
    while (getline(inputFile, line)) {
        vec.push_back(line);
    }

    inputFile.close();
    return true;
}

/**
 * @brief writes to filename with the first column from v0, second column from v1
 * @param filename output file name
 * @param v0 student names
 * @param v1 questions
 *
 * pass by value:           vector<string> v0          copies the vector
 * pass by reference:       vector<string> & v0        no copy, can change it
 * pass by const reference: const vector<string> & v0  no copy, cannot change it
 */
bool writeFile(string filename, const vector<string> & v0, const vector<string> & v1){
    ofstream outputFile(filename);
    if (!outputFile) {
        cout << "Error: Could not create data.csv" << endl;
        return false;
    }

    for(int i = 0; i < v0.size(); i++){
        outputFile << v0[i] << "," << v1[ranGen(v1.size())] << endl;
    }
    outputFile.close();
    return true;
}