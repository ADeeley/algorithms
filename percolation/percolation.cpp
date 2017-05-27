#include "percolation.h"
#include <iostream>
#include <vector>
#include "assert.h"

using namespace std;
const int open = 0;
const int blocked = -2;

Percolation::Percolation( int n ) {
	// Create an n*s size 2D vector
	vector<Sector> temp;
	// set sector ids from 1 to n. Must minus 1 to obtain index
	int id = 0; 
	for ( int row = 0; row < n; row++ ) {
		for ( int col = 0; col < n; col++ ) {
			temp.push_back( Sector(id) );
			id++;
		}
		grid.push_back( temp );
		temp.clear();
	}
	assert( grid.size() == n );
}

void Percolation::open( int row, int col ) {
	// first open the sector if not already open
	if (isOpen(row, col))
		return;
	grid[row][col].id = grid[row][col].id;
	grid[row][col].openSector = true;
	// next, check all sectors NESW of the sector and unite any 
	// open sectors
	if ( !row <= 0 ) {
		if ( isOpen(row-1, col) )
			unite( row, col, row - 1, col );
	}
	if ( row < grid.size()-1 ) {
		if ( isOpen(row+1, col) )
			unite( row, col, row + 1, col );
	}
	if ( !col <= 0 ) {
		if ( isOpen(row, col-1) )
			unite( row, col, row, col-1 );
	}
	if ( col < grid.size()-1) {
		if ( isOpen(row, col+1) )
			unite( row, col, row, col + 1 );
	}
}

bool Percolation::isOpen( int row, int col ) {
	if ( grid[row][col].openSector )
		return true;
	else
		return false;
}

bool Percolation::isFull( int row, int col ) {
	if ( grid[row][col].fullSector )
		return true;
	else
		return false;
}

int Percolation::numberOfOpenSites() {
	int sum = 0;
	for ( unsigned int row = 0; row < grid.size(); row++ )
		for ( unsigned int col = 0; col < grid.size(); col++ )
			if ( grid[row][col].openSector)
				sum += 1;
	return sum;

}

bool Percolation::percolates() {
	for ( int col = 0; col < grid.size() - 1; col++ ){
		if ( grid[grid.size() - 1][col].fullSector == true )
			return true;
	} 
	return false;
}
/*
void Percolation::printGrid() {
	cout << "printgrid start\n";
	for ( unsigned int row = 0; row < grid.size(); row++ ) {
		for ( unsigned int col = 0; col < grid.size(); col++ ) {
			cout << grid[row][col].id << 
				(grid[row][col].openSector == 1 ? 'o': 'c' ) <<
				(grid[row][col].fullSector == 1 ? 'f': 'e' ) << '\t';
	}
		cout << '\n';
	}
	cout << "\nprintgrid end\n";
}
*/
void Percolation::printGrid() {
	for ( unsigned int row = 0; row < grid.size(); row++ ) {
		for ( unsigned int col = 0; col < grid.size(); col++ ) {
			cout << (grid[row][col].fullSector == 1 ? 'f': 'e' ) ;
	}
		cout << '\n';
	}
}

void Percolation::unite( int rowA, int colA, int rowB, int colB ) {
	int pid = grid[rowA][colA].id;
	int qid = grid[rowB][colB].id;
	// change all sectors with id p to id q
	for ( unsigned int a = 0; a < grid.size(); a++ ) {
		for ( unsigned int b = 0; b < grid.size(); b++ ) {
			if ( grid[a][b].id == pid )
				grid[a][b].id = qid;
		}
	}
}
void Percolation::fill() {
	for ( unsigned int row = 0; row < grid.size(); row++ ) {
		for ( unsigned int col = 0; col < grid.size(); col++ ) {
			if ( row == 0 && isOpen( row, col ) && !isFull( row, col ) )
				grid[row][col].fullSector = true;
			if ( isOpen( row, col ) ) {
				if ( !row <= 0 )
					if ( isFull( row - 1, col ) )
						grid[row][col].fullSector = true;

				if ( row < grid.size() - 1 )
					if ( isFull( row + 1, col ) )
						grid[row][col].fullSector = true;

				if ( !col <= 0 )
					if ( isFull( row, col - 1 ) )
						grid[row][col].fullSector = true;

				if ( col < grid.size() - 1 )
					if ( isFull( row, col + 1 ) )
						grid[row][col].fullSector = true;
			}
		}
	}
}
