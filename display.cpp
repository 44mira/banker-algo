#pragma once

#include "overloads.cpp"
#include <iomanip>
#include <iostream>

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

/**
 * Displays the information parsed from the file
 *
 * @param allocatedMatrix The matrix of allocated resources
 * @param maxMatrix The matrix of maximum resources
 * @param resourceInstances The vector of resource instances
 */
void displayInfo(matrix &allocatedMatrix, matrix &maxMatrix,
                 vector<int> &resourceInstances, matrix &needMatrix) {

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

  std::cout << "\nNeed matrix for the 5 processes:\n\n";
  displayMatrix(needMatrix);

  int allocated;

  std::cout << "\nAvailable instances for each resource type: (";
  for (int i = 0; i < resourceInstances.size(); i++) {
    std::cout << "R" << i + 1
              << ((i == resourceInstances.size() - 1) ? "" : ",");
  }
  std::cout << ") = (";
  for (int i = 0; i < resourceInstances.size(); i++) {
    allocated = 0;

    for (int j = 0; j < allocatedMatrix.size(); j++) {
      allocated += allocatedMatrix[j][i];
    }

    std::cout << resourceInstances[i] - allocated
              << ((i == resourceInstances.size() - 1) ? "" : ",");
  }
  std::cout << ")\n";
}
