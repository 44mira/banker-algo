/*
 * Legolas Tyrael B. Lada 2-BSCS
 * 2022-04734
 */

#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using std::string, std::vector;

typedef vector<int> row;
typedef vector<vector<int>> matrix;

/*
 * RES_TYPE PROCESS_COUNT
 * INSTANCE PER TYPE
 * PROCESS_NAME INSTANCE MAX_INSTANCE
 */

void parseFile(string filename, matrix &allocatedMatrix, matrix &maxMatrix,
               vector<int> &resourceInstances);
void displayInfo(matrix &allocatedMatrix, matrix &maxMatrix,
                 vector<int> &resourceInstances);
void displayMatrix(matrix &matrix);

int main(int argc, char *argv[]) {
  string filename = argv[1] ? argv[1] : "";
  if (filename == "") {
    std::cerr << "Please provide a file to parse\n\n"
                 "Usage: ./lada <filename>\n";
    return 1;
  }

  vector<int> resourceInstances;
  matrix allocatedMatrix, maxMatrix;
  parseFile(filename, allocatedMatrix, maxMatrix, resourceInstances);

  displayInfo(allocatedMatrix, maxMatrix, resourceInstances);

  return 0;
}

/**
 * Takes a filename and parses the file into the format specified by the
 * assignment.
 *
 * @param filename The name of the file to parse
 * @return 0 if successful, 1 if file not found
 */
void parseFile(string filename, matrix &allocatedMatrix, matrix &maxMatrix,
               vector<int> &resourceInstances) {
  int resourceTypesCount, processCount, resourceInstanceCount;

  // open file in read mode
  std::ifstream parsedFile(filename);
  if (parsedFile.rdstate() & std::ifstream::failbit) {
    std::cerr << "File not found\n";
    return;
  }

  // read the first two lines
  parsedFile >> resourceTypesCount >> processCount;
  for (int i = 0; i < resourceTypesCount; i++) {
    parsedFile >> resourceInstanceCount;
    resourceInstances.push_back(resourceInstanceCount);
  }

  int col;

  // read the rest of the file
  for (int i = 0; i < processCount; i++) {
    row columns;
    parsedFile.ignore(3, ' '); // skip the process name

    // first half of columns
    for (int j = 0; j < resourceTypesCount; j++) {
      parsedFile >> col;
      columns.push_back(col);
    }
    allocatedMatrix.push_back(columns);
    columns.clear();

    // second half of columns
    for (int j = 0; j < resourceTypesCount; j++) {
      parsedFile >> col;
      columns.push_back(col);
    }
    maxMatrix.push_back(columns);
    columns.clear();
  }

  parsedFile.close();
}

/**
 * Displays the information parsed from the file
 *
 * @param allocatedMatrix The matrix of allocated resources
 * @param maxMatrix The matrix of maximum resources
 * @param resourceInstances The vector of resource instances
 */
void displayInfo(matrix &allocatedMatrix, matrix &maxMatrix,
                 vector<int> &resourceInstances) {

  for (int i = 1; i <= resourceInstances.size(); i++) {
    std::cout << "Resource " << i << "(R" << i << ") = " << std::setw(3)
              << resourceInstances[i - 1] << " instances\n";
  }

  std::cout << "\nAllocated Resources for the " << allocatedMatrix.size()
            << " processes:\n\n";
  displayMatrix(allocatedMatrix);

  std::cout << "\nMaximum Resources for the " << maxMatrix.size()
            << " processes:\n\n";
  displayMatrix(maxMatrix);

  matrix needMatrix;
  matrixSubtract(maxMatrix, allocatedMatrix, needMatrix);

  std::cout << "\nNeed matrix for the 5 processes:\n\n";
  displayMatrix(needMatrix);
}

/**
 * Takes a matrix and displays it in a tabular format
 *
 * @param matrix The matrix to display
 */
void displayMatrix(matrix &matrix) {
  // header row
  std::cout << std::left << std::setw(10) << "Process ";
  for (int i = 1; i <= matrix[0].size(); i++) {
    std::cout << "R" << std::left << std::setw(3) << i << " ";
  }

  std::cout << "\n";

  for (int i = 0; i < matrix.size(); i++) {
    std::cout << "P" << std::setw(9) << i + 1;
    for (int j = 0; j < matrix[i].size(); j++) {
      std::cout << std::setw(4) << matrix[i][j] << " ";
    }
    std::cout << "\n";
  }
}

