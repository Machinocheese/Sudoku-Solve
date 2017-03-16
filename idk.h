#ifndef IDK_H
#define IDK_H
#include <vector>

using namespace std;
class Point{
public:
	Point(const int& a){
		if(a < 1 || a > 9) throw ("Input must be 0 < x < 8"); //remember destructor isn't called
		for(int i = 0; i < 9; i++)
			possible[i] = 0;
		possible[a-1] = 1;
	}
	Point(){
		for(int i = 0; i < 9; i++){
			possible[i] = 1;
		}
	}

	int deleteNumber(const int& a){
		if(a < 1 || a > 9) return 0;
		if(possible[a-1] != 0){
			possible[a-1] = 0;
			return 1;
		}
		return 0;
	}

	const int* outputPossible() const{
		return possible;
	}

	int outputConfirmed(){
		int counter = 0;
		for(int i = 0; i < 9; i++){
			counter += possible[i];
		}
		if(counter == 1){
			for(int i = 0; i < 9; i++){
				if(possible[i] == 1)
					return i + 1;
			}
		} else{
			return 0;
		}
	}

private:
	int possible[9];

};



#endif