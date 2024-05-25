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
  std::string buf;
  std::ifstream parsedFile(filename); // read file

  if (parsedFile.rdstate() & std::fstream::failbit) {
    std::cerr << "File not found\n";
    return 1;
  }

  getline(parsedFile, buf); // get resource type count and process count
  std::stringstream ss(buf);

  int resourceTypesCount, processCount;
  ss >> resourceTypesCount >> processCount;

  std::vector<std::vector<int>> instancePerType;

  for (int i = 0; i < processCount; i++) {
    getline(parsedFile, buf);

    std::stringstream ss(buf);
    std::vector<int> instance;

    int temp;
    while (ss >> temp) {
      instance.push_back(temp);
    }
    instancePerType.push_back(instance);
  }

  for (auto i : instancePerType) {
    for (auto j : i) {
      std::cout << j << " ";
    }
    std::cout << "\n";
  }

  return 0;
}
