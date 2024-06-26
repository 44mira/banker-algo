/*
 * Legolas Tyrael B. Lada 2-BSCS
 * 2022-04734
 */

#include "display.cpp"
#include "overloads.cpp"
#include <fstream>
#include <iostream>

using std::string;

void parseFile(string filename, matrix &allocatedMatrix, matrix &maxMatrix,
               vector<int> &resourceInstances);
void getAvailableRow(matrix &allocatedMatrix, vector<int> &resourceInstances,
                     row &availableRow);

int main(int argc, char *argv[]) {
  string filename = argv[1] ? argv[1] : "";
  if (filename == "") {
    std::cerr << "Please provide a file to parse\n\n"
                 "Usage: ./lada <filename>\n";
    return 1;
  }

  row resourceInstances, availableRow;
  matrix allocatedMatrix, maxMatrix, needMatrix;
  parseFile(filename, allocatedMatrix, maxMatrix, resourceInstances);

  // solve for the need matrix using matrix subtraction
  needMatrix = maxMatrix - allocatedMatrix;

  getAvailableRow(allocatedMatrix, resourceInstances, availableRow);
  displayInfo(allocatedMatrix, maxMatrix, resourceInstances, needMatrix,
              availableRow);

  runSafetyAlgorithm(allocatedMatrix, needMatrix, resourceInstances,
                     availableRow);

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
 * Calculates the available row by subtracting the total allocation from the
 * resource instances.
 *
 * @param allocatedMatrix The matrix containing the allocated resources
 * @param resourceInstances The vector containing the total resource instances
 * @param availableRow The row containing the available resources
 */
void getAvailableRow(matrix &allocatedMatrix, row &resourceInstances,
                     row &availableRow) {
  row totalAllocation;
  int column;
  for (int i = 0; i < allocatedMatrix[i].size(); i++) {
    column = 0;
    for (int j = 0; j < allocatedMatrix.size(); j++) {
      column += allocatedMatrix[j][i];
    }

    totalAllocation.push_back(column);
  }
  availableRow = resourceInstances - totalAllocation;
}
