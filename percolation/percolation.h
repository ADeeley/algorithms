#pragma once
#include <vector>

using namespace std;

struct Sector {
	Sector( int i ) :
		id{ i } {};
	int id;
	bool openSector = false;
	bool fullSector = false;
};

class Percolation {
public:
	Percolation( int n );
	void open( int row, int col );
	bool isOpen( int row, int col );
	bool isFull( int row, int col );
	int numberOfOpenSites();
	bool percolates();
	void printGrid(); // test method
	void unite( int rowA, int colA, int rowB, int colB );
	void fill();
private:
	vector<vector<Sector>>grid;
};
