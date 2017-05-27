#include <iostream>
#include "percolation.h"
#include <cstdio>
#include <ctime>

using namespace std;

void test1() {
	Percolation p = Percolation( 5 );
	cout << "Percolates: " << p.percolates() << '\n';
	p.printGrid();
	p.open( 2, 2 );
	p.open( 3, 2 );
	p.fill();

	p.printGrid();
	cout << "Percolates: " << p.percolates() << '\n';
	p.open( 4, 2 );

	p.printGrid();
	cout << "Percolates: " << p.percolates() << '\n';
	cout << "p.open( 0, 0 )\n";
	p.open( 0, 0 );
	p.open( 0, 1 );
	p.open( 0, 2 );
	p.printGrid();
	cout << "Percolates: " << p.percolates() << '\n';

	p.open( 1, 2 );
	p.fill();
	p.printGrid();
	cout << "Percolates: " << p.percolates() << '\n';
	cout << "Num of open sites: " << p.numberOfOpenSites() << '\n';
}
double runSimulation(int gridSize, int cycles) {
	// runs the percolation simulation and returns the average percentage
	// of open sites required for the grid of size gridSize to percolate.
	int sum = 0;
	Percolation p = Percolation( gridSize );
		for ( int n = 0; n < cycles; n++ ) {
			while ( !p.percolates() ) {
				p.open( rand() % gridSize, rand() % gridSize);
				p.fill();
				//cout << "row:" << row << " col:" << col << '\n';
				if ( p.percolates() ) break;
			}
			// p.printGrid();
			//cout << "Percolates at " << ( (double)p.numberOfOpenSites() / pow( gridSize, 2 ) ) * 100 << "%\n";
			sum += ( (double)p.numberOfOpenSites() / pow( gridSize, 2 ) ) * 100;
			p = Percolation( gridSize );
	}
		return sum / cycles;
}

int main() {
	clock_t start;
	double duration;
	double threshold;
	int cycles = 100;
	for ( int n = 1; n < cycles; n++ ) {
		start = clock();
		threshold = runSimulation( 20, pow(5, n) );
		duration = ( clock() - start ) / (double)CLOCKS_PER_SEC;
		cout << "Time taken for " << pow(5, n) << " cycles: " << duration
			<< " seconds. Average percolation threshold: " << threshold << "%\n";
	}
	return 0;

}
