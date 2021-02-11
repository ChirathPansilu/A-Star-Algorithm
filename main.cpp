#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using std::cout;
using std::vector;
using std::ifstream;
using std::string;
using std::istringstream;
using std::sort;

enum class State { kEmpty, kObstacle, kClosed, kPath };

vector<State> ParseLine(string line)
{
	vector<State> line_v {};
	istringstream myStream(line);
	int n;
	char c;
	while(myStream >> n >> c && c == ',')
	{
		switch(n)
		{
			case 0:
				line_v.push_back(State::kEmpty);
				break;
			case 1:
				line_v.push_back(State::kObstacle);
				break;
		}
	}
	return line_v;
}

vector<vector<State>> ReadBoardFile(string file)
{
	ifstream myFile(file);
	vector<vector<State>> board {};
	if(myFile)
	{
		string line;
		while(getline(myFile, line))
		{
			board.push_back(ParseLine(line));
		}

	}
	myFile.close();
	
	return board;
}

// Compare the F values of two cells.
bool Compare(const vector<int> node1, const vector<int> node2)
{
	return (node1[2]+node1[3] > node2[2]+node2[3]);
}

//Sort the two-dimensional vector of ints in descending order.
void CellSort(vector<vector<int>> *v) {
  sort(v->begin(), v->end(), Compare);
}

// Calculate the Manhattan Distance
int Heuristic(int x1, int y1, int x2, int y2)
{
	return abs(x1-x2) + abs(y1-y2);
}

// Check that a cell is valid: on the grid and not an obstacle and clear.
bool CheckValidCell(int x, int y,const vector<vector<State>> &grid)
{
	int gridX = grid.size();
	int gridY = grid[0].size();

	if ( 0<= x && x<gridX && 0<= y && y<gridY )
		return ( grid[x][y] == State::kEmpty );
	else
		return false;
}

// Add a node to open_nodes and mark grid cell as closed
void AddToOpen( int x, int y, int g, int h, vector<vector<int>> &open_nodes, vector<vector<State>> &grid )
{
	vector<int> node{x,y,g,h};
	open_nodes.push_back(node);
	grid[x][y] = State::kClosed;  //x is measured vertically and y horizontally
}

// Expand current node's neighbors and add them to open_nodes.
void ExpandNeighbors(const vector<int> &currentNode,
					const int goal[2], 
					vector<vector<int>> &open_nodes,
					vector<vector<State>> &grid)
{
	int currentNodeX = currentNode[0];
	int currentNodeY = currentNode[1];
	int currentNodeG = currentNode[2];

	// directional deltas
	const int delta[4][2] { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };

	// loop through potential neighbors
	for(auto dir: delta)
	{
		int potX = currentNodeX + dir[0];
		int potY = currentNodeY + dir[1];

		if ( CheckValidCell(potX, potY, grid) ) 
		{
			int potG = currentNodeG + 1 ;
			int potH = Heuristic(potX, potY, goal[0], goal[1]);
			AddToOpen(potX, potY, potG, potH, open_nodes, grid);
		}
	}
}

// Implementation of A* search algorithm
vector<vector<State>> Search(vector<vector<State>> grid, int init[2], int goal[2])
{	
	//create vector of open_nodes
	vector<vector<int>> open{};

	//initialize the starting node
	int x = init[0];
	int y = init[1];
	int g = 0;
	int h = Heuristic(x,y,goal[0],goal[1]);
	AddToOpen(x,y,g,h,open,grid);

  	while( ! open.empty() )
  	{
  		//Sort the open_nodes
  		CellSort(&open);
  		//get the node with the least f-value
  		vector<int> currentNode = open.back();
  		open.pop_back();
  		int currentNodeX = currentNode[0];
  		int currentNodeY = currentNode[1];
  		grid[currentNodeX][currentNodeY] = State::kPath;

  		// Check for Goal
  		if(currentNodeX == goal[0] && currentNodeY == goal[1]){
  			return grid;
  		}

  		// Expand search to current node's neighbors
  		ExpandNeighbors(currentNode, goal, open, grid);

  	}

	//We've run out of new nodes to explore and haven't found a path
	cout << "No path found!\n";
	return vector<vector<State>> {};
}

string CellString(State cell)
{
	switch(cell)
	{
		case State::kObstacle:	return "⛰️   ";
		case State::kPath: return "🚗   ";
		case State::kClosed: return "C   ";
		case State::kEmpty: return "0   ";
		default: return "?   ";
	}
}

void PrintBoard(const vector<vector<State>> &board)
{
	for(auto i:board)
	{
		for(auto j: i)
		{
			cout << CellString(j) << ' ' ;
		}
		cout << '\n';
	}
}

#include "tests.h"

int main()
{
	int initial_point[2] {0,0};
	int goal_point[2] {4,5};

	string file_path = "files/1.board.txt"; 	
	vector<vector<State>> board = ReadBoardFile(file_path);
	
	auto solution = Search(board, initial_point, goal_point);
	PrintBoard(solution);

	//Tests
	TestHeuristic();
	TestAddToOpen();
	TestCompare();
	TestSearch();
	TestCheckValidCell();
	TestExpandNeighbors();
}
