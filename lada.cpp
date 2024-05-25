/*
 * Legolas Tyrael B. Lada 2-BSCS
 * 2022-04734
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

/*
 * RES_TYPE PROCESS_COUNT
 * INSTANCE PER TYPE
 * PROCESS_NAME INSTANCE MAX_INSTANCE
 */

int parse_file(std::string filename);

int main(int argc, char *argv[]) {
  std::string filename = argv[1] ? argv[1] : "";
  if (filename == "") {
    std::cerr << "Please provide a file to parse\n";
    return 1;
  }

  parse_file(filename);

  return 0;
}

/**
 * Takes a filename and parses the file into the format specified by the
 * assignment.
 *
 * @param filename The name of the file to parse
 * @return 0 if successful, 1 if file not found
 */
int parse_file(std::string filename) {
  int resourceTypesCount, processCount, resourceInstanceCount;

  // open file in read mode
  std::ifstream parsedFile(filename);
  if (parsedFile.rdstate() & std::ifstream::failbit) {
    std::cerr << "File not found\n";
    return 1;
  }

  // read the first two lines
  std::vector<int> resourceInstances;
  parsedFile >> resourceTypesCount >> processCount;
  for (int i = 0; i < resourceTypesCount; i++) {
    parsedFile >> resourceInstanceCount;
    resourceInstances.push_back(resourceInstanceCount);
  }

  std::vector<std::vector<int>> allocatedMatrix;
  std::vector<std::vector<int>> maxMatrix;
  int col;

  // read the rest of the file
  for (int i = 0; i < processCount; i++) {
    std::vector<int> columns;
    parsedFile >> col; // ignore process name

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
  return 0;
}
