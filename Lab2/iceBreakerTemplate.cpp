#include<iostream>
#include<fstream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<random>

using namespace std;

void promptFile(vector<string> &);
void printVec(vector<string>);
int ranGen(int size);
bool readFile(string filename, vector<string> & vec);
bool writeFile(string filename, const vector<string> & v0, const vector<string> & v1);

int main()
{
    srand(time(nullptr));
    vector<string> roster;
    vector<string> qBank;

    readFile("2310_F26_Rosters.csv", roster);
    readFile("Questions.csv", qBank);

    printVec(roster);
    printVec(qBank);
    cout << "Size of roster: " << roster.size() << endl;
    cout << "Size of qBank: " << qBank.size() << endl;

    writeFile("Student_question_bank.csv", roster, qBank);
}

void promptFile(vector<string> & v){
    cout << "file to read?\n";
    string myFile = "";
    cin >> myFile;
    readFile(myFile, v);
}

void printVec(vector<string> v){
    for(int i = 0; i < v.size(); i++){
        cout << v[i] << endl;
    }
}

int ranGen(int size){
    default_random_engine engine(time(nullptr));
    uniform_int_distribution<int> randomIndex(0, size - 1);
    return randomIndex(engine);
}

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