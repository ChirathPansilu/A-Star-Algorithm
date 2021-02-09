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

enum class State { kEmpty, kObstacle, kClosed };

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

	cout<< "board.size() or i:"<<board.size()<<", board[0].size() or j:"<<board[0].size() << "\n";
	
	return board;
}

// Heuristic function - calculates the manhattan distance
int Heuristic(int x1, int y1, int x2, int y2)
{
	return abs(x1-x2) + abs(y1-y2);
}

void AddToOpen( int x, int y, int g, int h, vector<vector<int>> &open_nodes, vector<vector<State>> &grid )
{
	vector<int> node{x,y,g,h};
	open_nodes.push_back(node);
	grid[x][y] = State::kClosed;  //x is measured vertically and y horizontally
}

// Search function stub
vector<vector<State>> Search(vector<vector<State>> grid, int initial_point[2], int goal_point[2])
{
	cout << "No path found!\n";
	vector<vector<State>> solution{};
	return solution;
}

string CellString(State cell)
{
	switch(cell)
	{
		case State::kObstacle:	return "⛰️   ";
		case State::kClosed: return "x   ";
		default: return "0   ";
	}
}

void PrintBoard(const vector<vector<State>> board)
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
	// Test the solution stub
	int initial_point[2] {0,0};
	int goal_point[2] {4,5};

	string file_path = "files/1.board.txt"; 	
	vector<vector<State>> board = ReadBoardFile(file_path);
	
	auto solution = Search(board, initial_point, goal_point);
	PrintBoard(solution);

	//Tests
	TestHeuristic();
	TestAddToOpen();
}
