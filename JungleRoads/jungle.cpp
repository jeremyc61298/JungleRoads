// -------------------------------------------------
// jungle.cpp
// Jeremy Campbell
// Practice with minimal spanning tree algorithm
// -------------------------------------------------
#include <iostream>
#include <fstream>

using std::cerr;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;

int main()
{
	ifstream fin("jungle.in");
	
	if (!fin.is_open())
	{
		cerr << "Input file could not be opened." << endl;
		return -1;
	}

	ofstream fout("jungle.out");

}