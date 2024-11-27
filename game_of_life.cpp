#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unistd.h> 
#include <string>
using namespace std;

const char ALIVE = 'X';
const char NOTALIVE = ' ';
const int PROB_ALIVE = 1; // probability of a cell being alive out of 10
const char SWITCH = 'R';  // R will Run forever, S will stop at each generation
const char* ERROR = "Error opening file!\n";

// Function prototypes
char lifeIsRandom();  // Randomly returns 'X' or ' '.
char** makeStartingGrid(int rows, int columns);  // Makes the starting grid.
void deleteGrid(char** grid, int rows);  // Frees memory used by the grid.
void showGrid(char** grid, int rows, int columns);  // Displays the grid.
char** makeNextGen(char** current, int rows, int columns);  // Generates next generation.
char checkSquare(char** current, int x, int y, int maxX, int maxY);  // Checks a square for the next generation.
char** readInAGrid(const string& filePath, int& rows, int& columns);  // Reads grid from file.
bool writeGridToFile(char** grid, const string& filePath, int rows, int columns);  // Writes grid to file.
char** userInputGrid(int rows, int columns);  // Allows user to input grid line by line.
void clearConsole();  // Clears the terminal screen.

int main() {
    int ROWS = 30;
    int COLUMNS = 80;
    srand((unsigned)time(NULL));
    char** currentGrid;
    int counter = 0;

    // Menu for grid choice
    int choice;
    cout << "Choose an option:\n";
    cout << "1. Read grid from file\n";
    cout << "2. Use default grid\n";
    cout << "3. Input grid manually\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();  // To ignore newline after entering the choice.

    // Grid initialization based on choice
    switch(choice) {
        case 1:
            {
                string filePath;
                cout << "Enter the file path: ";
                getline(cin, filePath);
                currentGrid = readInAGrid(filePath, ROWS, COLUMNS);
                break;
            }
        case 2:
            currentGrid = makeStartingGrid(ROWS, COLUMNS);
            break;
        case 3:
            currentGrid = userInputGrid(ROWS, COLUMNS);
            break;
        default:
            cout << "Invalid choice, using default grid.\n";
            currentGrid = makeStartingGrid(ROWS, COLUMNS);
    }

    while (true) {
        clearConsole();  // Clear the screen
        showGrid(currentGrid, ROWS, COLUMNS);  // Show the current grid
        usleep(100000);  // Sleep for 100ms
        char** nextGen = makeNextGen(currentGrid, ROWS, COLUMNS);
        deleteGrid(currentGrid, ROWS);
        currentGrid = nextGen;

        if (SWITCH == 'S') {  // Pause if SWITCH is 'S'
            char exit = getchar();
            if ((exit == 'x') || (exit == 'X')) {
                break;  // Exit the program if 'x' or 'X' is pressed
            }
        }
        counter++;
        if (counter > 25) { // Reset the grid after a number of cycles
            counter = 0;
            deleteGrid(currentGrid, ROWS);
            currentGrid = makeStartingGrid(ROWS, COLUMNS);
        }
    }
    deleteGrid(currentGrid, ROWS);  // Free the grid memory
    return 0;
}

char** readInAGrid(const string& filePath, int& rows, int& columns) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << ERROR;
        return nullptr;
    }

    string line;
    getline(file, line);  // Read first line (rows,columns)
    size_t commaPos = line.find(',');
    rows = stoi(line.substr(0, commaPos));
    columns = stoi(line.substr(commaPos + 1));

    char** grid = new char*[rows];
    int rowCount = 0;

    // Read each line from the file and process it to populate the grid
    while (getline(file, line) && rowCount < rows) {  
        // Dynamically allocate memory for the current row in the grid
        grid[rowCount] = new char[columns];

        // Iterate through each column in the grid
        for (int col = 0; col < columns; ++col) {  
            // Check if the current column index is within the length of the line
            // and the character is not a comma (',')
            if (col < line.length() && line[col] != ',') {  
                // If the character is 'x', mark it as alive; otherwise, mark it as not alive
                grid[rowCount][col] = (line[col] == 'x') ? ALIVE : NOTALIVE;  
            } else {
                // If the column index exceeds the line's length or it's a comma,
                // mark the cell as not alive
                grid[rowCount][col] = NOTALIVE;  
            }
        }
        // Move to the next row in the grid
        ++rowCount;  
    }

    while (rowCount < rows) {  // Fill remaining rows with dead cells.
        grid[rowCount] = new char[columns];
        fill(grid[rowCount], grid[rowCount] + columns, NOTALIVE);
        ++rowCount;
    }

    file.close();
    return grid;
} 

bool writeGridToFile(char** grid, const string& filePath, int rows, int columns) {
    ofstream file(filePath);
    if (!file.is_open()) {
        cout << "Error opening file for writing!\n";
        return false;
    }

    file << rows << "," << columns << endl;
    // Iterate through each row of the grid
    for (int i = 0; i < rows; ++i) {  
        // Iterate through each column of the current row
        for (int j = 0; j < columns; ++j) {  
            // Write the cell's state to the file:
            // If the cell is alive, write 'x'; otherwise, write a space (' ')
            file << (grid[i][j] == ALIVE ? "x" : " ") << ",";  
        }

        // Move the file write pointer back by one position to remove the trailing comma
        file.seekp(-1, ios_base::cur);  

        // Write a newline character to end the current row
        file << endl;  
    }

    // Close the file to ensure all data is saved and resources are released
    file.close();  
    return true;
}

char** userInputGrid(int rows, int columns) {
    char** grid = new char*[rows];
    cout << "Input grid row by row (each cell as 'x' for alive, ' ' for dead, separated by commas):\n";
    cin.ignore();  // Clear any remaining input buffer

    for (int i = 0; i < rows; ++i) {
        grid[i] = new char[columns];
        string rowInput;
        getline(cin, rowInput);
        for (int j = 0; j < columns; ++j) {
            if (j < rowInput.length() && rowInput[j] != ',') {
                grid[i][j] = (rowInput[j] == 'x') ? ALIVE : NOTALIVE;
            } else {
                grid[i][j] = NOTALIVE;
            }
        }
    }

    return grid;
}

void clearConsole() {
    system("clear");  // Clears the screen for macOS
}

char** makeStartingGrid(int rows, int columns) {
    char** grid = new char*[rows];
    for (int i = 0; i < rows; ++i) {
        grid[i] = new char[columns];
        for (int j = 0; j < columns; ++j) {
            grid[i][j] = lifeIsRandom();
        }
    }
    return grid;
}

void deleteGrid(char** grid, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
}

void showGrid(char** grid, int rows, int columns) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            cout << grid[i][j];
        }
        cout << '\n';
    }
}

char lifeIsRandom() {
    int value = 1 + (rand() % 10);
    return (value <= PROB_ALIVE) ? ALIVE : NOTALIVE;
}

char** makeNextGen(char** current, int rows, int columns) {
    char** nextGen = new char*[rows];
    for (int i = 0; i < rows; ++i) {
        nextGen[i] = new char[columns];
        for (int j = 0; j < columns; ++j) {
            nextGen[i][j] = checkSquare(current, i, j, rows, columns);
        }
    }
    return nextGen;
}

char checkSquare(char** current, int x, int y, int maxX, int maxY) {
    int liveNeighbors = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            int nx = x + i, ny = y + j;
            if (nx >= 0 && nx < maxX && ny >= 0 && ny < maxY) {
                liveNeighbors += (current[nx][ny] == ALIVE);
            }
        }
    }
    if (current[x][y] == ALIVE) {
        return (liveNeighbors == 2 || liveNeighbors == 3) ? ALIVE : NOTALIVE;
    } else {
        return (liveNeighbors == 3) ? ALIVE : NOTALIVE;
    }
}