#include <iostream>
#include <fstream>
#include <vector>
#include "idk.h"

using namespace std;
const int size = 9;

void intcopy(int (&test2)[size], const int* test1){
	for(int i = 0; i < size; i++){
		test2[i] = test1[i];
	}
}

int eliminate(Point *test[]){
	vector<int> temp;
	int counter = 0;
	for(int i = 0; i < size; i++){
		if(test[i] -> outputConfirmed() != 0)
			temp.push_back(test[i] -> outputConfirmed());
	}
	
	for(int i = 0; i < size; i++){
		if(test[i] -> outputConfirmed() == 0){
			for(int j = 0; j < temp.size(); j++){
				counter += test[i] -> deleteNumber(temp[j]);
			}
		}
	}
	return counter;
}

void basicstep(Point **lines[], Point **boxes[], Point **rows[]){
	int counter = 1;
	while(counter != 0){
		counter = 0;
			for(int i = 0; i < size; i++){
				counter += eliminate(lines[i]);
				counter += eliminate(rows[i]);
				counter += eliminate(boxes[i]);
		}	
	}
}

//there's only ONE SPOT available for a number in a row
//despite that ONE SPOT having possibilities for other numbers
int isolate(Point *test[]){
	int cake[size] = {0};
	int temp[size] = {0};
	for(int i = 0; i < size; i++){
		intcopy(temp, test[i] -> outputPossible());
		if(test[i] -> outputConfirmed() == 0){
			for(int j = 0; j < size; j++){
				cake[j] += temp[j];
			}
		}
	}

	int counter = -1;
	for(int i = 0; i < size; i++){
		if(cake[i] == 1)
			counter = i;
	}

	for(int i = 0; i < size; i++){
		intcopy(temp, test[i] -> outputPossible());
		if(temp[counter] != 0 && counter != -1){
			for(int j = 0; j < size; j++){
				if(j != counter){
					//cout << "DELETING NUMBER: " << j + 1 << endl;
					test[i] -> deleteNumber(j + 1);
				}
			}
		}
	}
	if(counter == -1)
		return 0;
	else
		return 1;
}

int main(int argc, char* argv[]){
	
	Point board[size][size];
	ifstream instr(argv[1]);
	if (!instr.good()) {
    	std::cerr << "Can't open " << argv[1] << " to read.\n";
    	return 0; //or exit
  	}

  	int input;
  	for(int i = 0; i < size; i++){
  		for(int j = 0; j < size; j++){
  			instr >> input;
  			if(input == 0)
  				board[i][j] = Point();
  			else
  				board[i][j] = Point(input);
  		}
  	}

  	cout << "Original: " << endl;
  	cout << string(25, '-') << endl;

  	for(int i = 0; i < size; i++){
  		cout << "| ";
  		for(int j = 0; j < size; j++){
  			cout << board[i][j].outputConfirmed() << " ";
  			if(j == 2 | j == 5) cout << "| ";
  		}
  		if(i == 2 | i == 5) cout << "|" << endl << string(25, '-') << endl;
  		else cout << "|" << endl;
  	}

  	cout << string(25, '-') << endl;

	Point **lines[size];
	Point **rows[size];
	for(int i = 0; i < size; i++){
		lines[i] = new Point *[size];
		rows[i] = new Point *[size];
		for(int j = 0; j < size; j++){
			lines[i][j] = &board[i][j];
			rows[i][j] = &board[j][i];
		}
	}

	Point **boxes[size];
	int counter = 0;
	for(int k = 0; k < 9; k+=3){
		for(int l = 0; l < 9; l += 3){
			boxes[counter] = new Point *[size];
			for(int j = 0; j < size / 3; j++){
				boxes[counter][j] = &board[k][j+l];
				boxes[counter][j+3] = &board[k+1][j+l];
				boxes[counter][j+6] = &board[k+2][j+l];
			}
			counter++;
		}
	}

	basicstep(lines, boxes, rows);
  	for(int i = 0; i < size; i++){
  		isolate(lines[i]);
  	}
  	basicstep(lines, boxes, rows);

  	cout << "Solved: " << endl;
  	cout << string(25, '-') << endl;
	for(int i = 0; i < size; i++){
  		cout << "| ";
  		for(int j = 0; j < size; j++){
  			cout << board[i][j].outputConfirmed() << " ";
  			if(j == 2 | j == 5) cout << "| ";
  		}
  		if(i == 2 | i == 5) cout << "|" << endl << string(25, '-') << endl;
  		else cout << "|" << endl;
  	}
  	cout << string(25, '-') << endl;

}