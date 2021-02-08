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

int main()
{
	string file_path = "files/1.board.txt"; 	
	vector<vector<State>> board;
	board = ReadBoardFile(file_path);			   
	PrintBoard(board);
}