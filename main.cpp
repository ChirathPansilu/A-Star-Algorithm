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

enum class State { kEmpty, kObstacle };

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

// Heuristic function - calculates the manhattan distance
int Heuristic(int x1, int y1, int x2, int y2)
{
	return abs(x1-x2) + abs(y1-y2);
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
		case State::kObstacle:
			return "⛰️   ";
		default: // When State::kEmpty
			return "0   ";
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

// Test for heuristic
void TestHeuristic() {
	cout << "----------------------------------------------------------" << "\n";
	cout << "Heuristic Function Test: ";
	if (Heuristic(1, 2, 3, 4) != 4) {
		cout << "failed" << "\n";
		cout << "\n" << "Heuristic(1, 2, 3, 4) = " << Heuristic(1, 2, 3, 4) << "\n";
		cout << "Correct result: 4" << "\n";
		cout << "\n";
	} else if (Heuristic(2, -1, 4, -7) != 8) {
		cout << "TestHeuristic Failed" << "\n";
		cout << "\n" << "Heuristic(2, -1, 4, -7) = " << Heuristic(2, -1, 4, -7) << "\n";
		cout << "Correct result: 8" << "\n";
		cout << "\n";
	} else {
		cout << "passed" << "\n";
	}
	cout << "----------------------------------------------------------" << "\n";
}


int main()
{
	// Test the solution stub
	int initial_point[2] {0,0};
	int goal_point[2] {4,5};

	string file_path = "files/1.board.txt"; 	
	vector<vector<State>> board;
	board = ReadBoardFile(file_path);			   
	
	auto solution = Search(board, initial_point, goal_point);

	PrintBoard(solution);

	//Tests
	TestHeuristic();
}