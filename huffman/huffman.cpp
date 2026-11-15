// huffman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream> //read & write

//Betero -- using namespace to isolate what I added. Are we doing "using directive" or not?
using namespace std;

int main()
{
    if (argc < 2)
    {
        std::cerr << "Missing input file. Try again" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1], ios::in | ios::binary);

    if (!input)
    {
        cerr << "Cannot open input file." << endl;
    }
    
    std::cout << "Hello World!\n";

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
