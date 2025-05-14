#include <fstream>

#include "TestGameManager.h"
#include "Utils.h"

#define EXPECTED_FOLDER "./test/expected/"

TestGameManager initTestGameManager()
{
    TestGameManager gm;
    newRandomSeed();
    gm.generateBoard();

    return gm;
}

void writeInFile(std::string filename, std::string content)
{
    std::ofstream file;
    file.open(EXPECTED_FOLDER + filename);
    file << content;
    file.close();
}

std::string readFile(std::string filename)
{
    std::ifstream file { EXPECTED_FOLDER + filename };
    std::string content = "";
    std::string line;
    while ( std::getline (file,line) )
    {
      content += line + '\n';
    }

    file.close();
    return content;
}