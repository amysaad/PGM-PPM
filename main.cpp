/*
 * Amy Saad
 * File: main.cpp
 *
 * Program to calculate paths with most and least elevation gain
 * through a visual terrain and generate output files in PGM and PPM formatting
 *
 * Classes: DEM, PPM, PGM
 * methods:
 * isIn(string pair): Checks if a given pair exists in the path.
 * pathExists(): checks if a path exist
 * getNumOfRows(): gets number of rows
 * getNumOfCols(): gets number of columns
 * getHighestElevation(): gets highest elevation
 * getLowestElevation(): gets lowest elevation
 * getElevation(int NumOfRows, int NumOfCols): gets elevation value at pair
 * getStart(): gets starting row
 * lowestPath(): finds path with the least elevation
 * highestPath(): finds path with the most elevation
 * readFile(string infile): reads data from file
 * showRowsAndCols() const: shows number of rows and columns
 * isMax(float value): checks for highest elevation
 * isMin(float value): checks for lowest elevation
 *
 * Input: integers, characters, string values
 * Output: terrain visualization
 *
*/

#include <iostream>
#include <string>
#include <fstream>
#include <istream>
#include <cfloat>
#include <algorithm>
using namespace std;

class DEM {
private:
    int NumOfRows;
    int NumOfCols;
    int StartOfRow = 0;
    float **grid;
    float HighestElevation = -FLT_MAX; // value in grid
    float LowestElevation = FLT_MAX; // value in grid
    string *path;
    bool CheckIsPath = false;

public:
    DEM() {
        NumOfRows = 0;
        NumOfCols = 0;
        grid = nullptr;
        path = nullptr;
    }

    bool isIn(string pair);
    bool pathExists();
    int getNumOfRows();
    int getNumOfCols();
    float getHighestElevation();
    float getLowestElevation();
    float getElevation(int x, int y);
    void getStart();
    void lowestPath();
    void highestPath();
    void readFile(string infile);
    void showRowsAndCols() const;
    void isMax(float value);
    void isMin(float value);
};

void DEM::readFile(string infile) {
    ifstream file(infile);
    if (!file.is_open()) {
        cout << "Can't open your file..." << endl;
        return;
    }

    string Line;
    file >> Line >> NumOfCols;
    file >> Line >> NumOfRows;
    path = new string[NumOfCols];
    grid = new float*[NumOfRows];
    for (int i = 0; i < NumOfRows; i++) {
        grid[i] = new float[NumOfCols];
    }

    for (int i = 0; i < NumOfRows; i++) {
        for (int j = 0; j < NumOfCols; j++) {
            file >> grid[i][j];
            isMin(grid[i][j]);
            isMax(grid[i][j]);
        }
    }

    file.close();
}

void DEM::showRowsAndCols() const {
    cout << "Rows: " << NumOfRows << endl;
    cout << "Columns: " << NumOfCols << endl;
}

void DEM::isMax(float value) {
    if (value > HighestElevation) {
        HighestElevation = value;
    }
}

void DEM::isMin(float value) {
    if (value < LowestElevation) {
        LowestElevation = value;
    }
}

bool DEM::isIn(string pair) {
    for(int i = 0; i < NumOfCols; i++) {
        if (path[i] == pair) {
            return true;
        }
    }
    return false;
}

void DEM::getStart() {
    bool Invalid = true;
    do {
        cout << "Enter the starting row: ";
        cin >> StartOfRow;
        if (StartOfRow > NumOfRows or StartOfRow < 0) {
            cout << "Hmm.. invalid row number..." << endl;
        }
        else {
            Invalid = false;
        }
    } while (Invalid);
    cout << "Starting row: " << StartOfRow << endl;
}

void DEM::lowestPath() {
    float currentElevation = grid[StartOfRow][0];
    int currentRow = StartOfRow;
    int currentCol = 0;
    int indexPath = 0;
    while (currentCol < NumOfCols - 1) {
        path[indexPath] = to_string(currentRow) + "," + to_string(currentCol);
        indexPath++;
        if (currentRow == 0) {
            if (currentElevation > grid[currentRow + 1][currentCol + 1]) {
                currentElevation = grid[currentRow + 1][currentCol + 1];
            }
            currentRow++;
            currentCol++;
        }
        else if (currentRow == NumOfRows) {
            if (currentElevation > grid[currentRow - 1][currentCol + 1]) {
                currentElevation = grid[currentRow - 1][currentCol + 1];
            }
            currentRow--;
            currentCol++;
        }
        else {
            if (currentElevation > grid[currentRow - 1][currentCol + 1]) {
                currentElevation = grid[currentRow - 1][currentCol + 1];
            }
            else if (currentElevation > grid[currentRow + 1][currentCol + 1]) {
                currentElevation = grid[currentRow + 1][currentCol + 1];
            }
            currentRow++;
            currentCol++;
        }
    }
    path[indexPath] = to_string(currentRow) + "," + to_string(currentCol);
    CheckIsPath = true;
}

void DEM::highestPath() {
    float currentElevation = grid[StartOfRow][0];
    int currentRow = StartOfRow;
    int currentCol = 0;
    int indexPath = 0;
    while (currentCol < NumOfCols - 1) {
        path[indexPath] = to_string(currentRow) + "," + to_string(currentCol);
        indexPath++;
        if (currentRow == 0) {
            if (currentElevation < grid[currentRow + 1][currentCol + 1]) {
                currentElevation = grid[currentRow + 1][currentCol + 1];
            }
            currentRow++;
            currentCol++;
        }
        else if (currentRow == NumOfRows) {
            if (currentElevation < grid[currentRow - 1][currentCol + 1]) {
                currentElevation = grid[currentRow - 1][currentCol + 1];
            }
            currentRow--;
            currentCol++;
        }
        else {
            if (currentElevation < grid[currentRow - 1][currentCol + 1]) {
                currentElevation = grid[currentRow - 1][currentCol + 1];
            }
            else if (currentElevation < grid[currentRow + 1][currentCol + 1]) {
                currentElevation = grid[currentRow + 1][currentCol + 1];
            }
            currentRow++;
            currentCol++;
        }
    }
    path[indexPath] = to_string(currentRow) + "," + to_string(currentCol);
    CheckIsPath = true;
}

int DEM::getNumOfRows() {
    return NumOfRows;
}

int DEM::getNumOfCols() {
    return NumOfCols;
}

float DEM::getHighestElevation() {
    return HighestElevation;
}

float DEM::getLowestElevation() {
    return LowestElevation;
}

float DEM::getElevation(int NumOfRows, int NumOfCols) {
    return grid[NumOfRows][NumOfCols];
}

bool DEM::pathExists() {
    return CheckIsPath;
}

class PPM : public DEM {
public:
    void writeFile(string outfile);
};

void PPM::writeFile(string outfile) {
    ofstream outFile(outfile);
    if (!outFile.is_open()) {
        return;
    }

    outFile << "255" << endl;

    float elevation = 0;
    int red, green, blue;
    string Pair;

    for (int i = 0; i < getNumOfRows(); i++) {
        for (int j = 0; j < getNumOfCols(); j++) {
            Pair = to_string(i) + "," + to_string(j);
            if (pathExists() and isIn(Pair)) {
                red = 0;
                green = 0;
                blue = 255;
            }
            else {
                elevation = getElevation(i, j);
                red = int(255 * ((elevation - getLowestElevation()) / (getHighestElevation() - getLowestElevation())));
                green = int(255 - 230 * ((getHighestElevation() - elevation) / (getHighestElevation() - getLowestElevation())));
                blue = 0;
            }
            outFile << red << " " << green << " " << blue << " ";
        }
    }

    outFile.close();
}

class PGM : public DEM {
public:
    void writeFile(string outfile);
};

void PGM::writeFile(string outfile) {
    ofstream file(outfile);
    if (!file.is_open()) {
        return;
    }

    file << "P2" << endl;
    file << getNumOfCols() << " " << getNumOfRows() << endl;
    file << "255" << endl;

    float current = 0;
    int grayScale;
    string pair;

    for (int i = 0; i < getNumOfRows(); i++) {
        for (int j = 0; j < getNumOfCols(); j++) {
            pair = to_string(i) + "," + to_string(j);
            if (pathExists() and isIn(pair)) {
                grayScale = 0;
            }
            else {
                current = getElevation(i, j);
                grayScale = int(255 * ((current - getLowestElevation()) / (getHighestElevation() - getLowestElevation())));
            }
            file << grayScale << " ";
        }
    }

    file.close();
}

bool isFileValid(const string &file) {
    ifstream filename(file);
    return filename.is_open();
}

int main() {
    PGM pgmData;
    PPM ppmData;
    char FileType;
    char userInput;
    string file;

    do {
        cout << "Menu ~~~~" << endl;
        cout << "g - Create new P(G)M object " << endl;
        cout << "p - Create new P(P)M object " << endl;
        cout << "d - (D)isplay number of rows/columns" << endl;
        cout << "s - Enter (s)tarting position row" << endl;
        cout << "l - Calculate path with (l)east elevation gain" << endl;
        cout << "m - Calculate path with (m)ost elevation gain" << endl;
        cout << "w - (W)rite output file " << endl;
        cout << "q - (Q)uit " << endl;
        cin >> userInput;

        if (userInput == 'g' or userInput == 'p') {
            FileType = userInput;
            cout << "Enter a .grd file: ";
            cin >> file;
            if (isFileValid(file)) {
                if (userInput == 'p') {
                    ppmData.readFile(file);
                }
                else {
                    pgmData.readFile(file);
                }
            }
            else {
                cout << "Can't open your file..." << endl;
            }
        }
        else if (userInput == 'd') {
            if (FileType == 'p') {
                ppmData.showRowsAndCols();
            }
            else {
                pgmData.showRowsAndCols();
            }
        }
        else if (userInput == 's') {
            if (FileType == 'p') {
                ppmData.getStart();
            }
            else {
                pgmData.getStart();
            }
        }
        else if (userInput == 'l') {
            if (FileType == 'p') {
                ppmData.lowestPath();
            }
            else {
                pgmData.lowestPath();
            }
        }
        else if (userInput == 'm') {
            if (FileType == 'p') {
                ppmData.highestPath();
            }
            else {
                pgmData.highestPath();
            }
        }
        else if (userInput == 'w') {
            if (FileType == 'p') {
                string filename;
                cout << "Enter the name of the file: ";
                cin >> filename;
                if (filename.find(".ppm") == string::npos) {
                    cout << "Hmm... that's not a .ppm file" << endl;
                }
                else {
                    ppmData.writeFile(filename);
                }
            }
            else {
                string filename;
                cout << "Enter the name of the file: ";
                cin >> filename;
                if (filename.find(".pgm") == string::npos) {
                    cout << "Hmm... that's not a .pgm file" << endl;
                }
                else {
                    pgmData.writeFile(filename);
                }
            }
        }
    } while (userInput != 'q');

    return 0;
}
