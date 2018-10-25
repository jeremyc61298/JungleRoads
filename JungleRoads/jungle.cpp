// -------------------------------------------------
// jungle.cpp
// Jeremy Campbell
// Practice with minimal spanning tree algorithm
// Prim's Algorithm
// -------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using std::cerr;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;
using std::set;

class RoadMap
{
public:
	explicit RoadMap(int size);
	void inputRoads(ifstream &fin);
	int findMinimumTotalCost();

private:
	// These vectors are conceptually indexed using letters A-Y
	// but they are actually indexed using the underlying integer 
	// implementation when being accessed
	vector<vector<int>> adjacency;
	vector<char> parents;
	vector<int> costs;
	set<char> villages;

	template <typename T>
	void print2DVector(const vector<vector<T>> &v, string name);
};


RoadMap::RoadMap(int size)
{
	adjacency.resize(size, vector<int>(size, INT_MAX));
	parents.resize(size, NULL);
	costs.resize(size, INT_MAX);
}

void RoadMap::inputRoads(ifstream &fin)
{
	for (int i = 0; i < adjacency.size() - 1; i++)
	{
		char village;
		int numRoads;
		fin >> village >> numRoads;
		villages.insert(village);

		for (int j = 0; j < numRoads; j++)
		{
			char nextVillage;
			int roadLength;
			fin >> nextVillage >> roadLength;

			// Converting from char to int in order to index vector
			int vIndex = village - 'A';
			int nvIndex = nextVillage - 'A';
			adjacency[vIndex][nvIndex] = roadLength;
			adjacency[nvIndex][vIndex] = roadLength;
		}
	}
	// The last village was not read in from the file
	villages.insert('A' + adjacency.size() - 1);
	//print2DVector(adjacency, "Adjacency");
}

// Uses Prim's algorithm for Minimal Spanning Tree
int RoadMap::findMinimumTotalCost()
{
	set<char> t;
	// Root node will be last node
	costs[villages.size() - 1] = 0;

	while (t != villages)
	{
		char selected;
		int smallestValue = INT_MAX;
		for (char village : villages)
		{
			if (t.find(village) == t.end() && costs[village - 'A'] < smallestValue)
			{
				selected = village;
				smallestValue = costs[village - 'A'];
			}
		}
		
		t.insert(selected);
		for (char village : villages)
		{
			// If the village is not in set "t" and there is a road from selected->village 
			// which has a cost less than value[village]
			if (t.find(village) == t.end() && adjacency[selected - 'A'][village - 'A'] < costs[village - 'A'])
			{
				parents[selected - 'A'] = selected;
				costs[village - 'A'] = adjacency[selected - 'A'][village - 'A'];
			}
		}
	}

	// Sum of values is the totalCost
	int totalCost = 0;
	for (int cost : costs)
	{
		totalCost += cost;
	}

	return totalCost;
}

// Debug Method
template <typename T>
void RoadMap::print2DVector(const vector<vector<T>> &v, string name)
{
	cerr << name << ":" << endl;
	cerr << "-----------------------------" << endl;
	for (vector<T> row : v)
	{
		for (T item : row)
		{
			cerr << item << " ";
		}
		cerr << endl;
	}
	cerr << "-----------------------------" << endl;
}

int main()
{
	ifstream fin("jungle.in");
	
	if (!fin.is_open())
	{
		cerr << "Input file could not be opened." << endl;
		return -1;
	}

	ofstream fout("jungle.out");
	string line;
	fin >> line;

	while (line != "0")
	{
		RoadMap jungleRoads(stoi(line));
		jungleRoads.inputRoads(fin);
		fout << jungleRoads.findMinimumTotalCost();

		fin >> line;
		if (line != "0")
			fout << endl;
	}
}