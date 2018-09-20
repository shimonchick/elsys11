#include <iostream>
using namespace std;

class Point
{

private:
	int x;
	int y;

public:
	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	Point(){
		this->x = 0;
		this->y = 0;
	}
	void Print(){
		cout<<"(" << this->x << "," << this->y << ")" << endl;
	}
	int GetX(){
		return this->x;
	}
	void SetX(){
		this->x = x;
	}
	void Translate(int XOffset, int YOffset){
		this->x += XOffset;
		this->y += YOffset;

	}
	void Translate(Point other){
		//this->x += other.x;
		//this->y += other.y;
		this->Translate(other.x, other.y);
	}
};


int main(){

	Point p1;
	Point p2(-1, 20);
	p1.Print();
	p2.Print();
	cout << "x of p1" << p1.GetX()<< endl;

	p1.Translate(p2);
	p1.Print();
	return 0;
}
