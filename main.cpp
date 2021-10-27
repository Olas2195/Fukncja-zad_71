#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

class Zadanie71{
	double t[5][4];
	
	public:
		ifstream we;
		ofstream wy;
		Zadanie71();
		~Zadanie71();
		void wczytaj();
		double funkcja(double x, int i);
		double ekstremum();
		void miejsce_zerowe();
		double szukanie(double x1, double x2, int i);
};

Zadanie71::Zadanie71() {
	we.open("funkcja.txt");
	wy.open("wyniki_funkcja.txt");
}

void Zadanie71::wczytaj() {
	if(we.good()) {
		while(!we.eof()) {
			for(int i=0; i<5; i++) {
				for(int j=0; j<4; j++) {
					we>>t[i][j];
				}
			}
		}
	}
}

double Zadanie71::funkcja(double x, int i) {
	i = i-1;
	return round((t[i][0]+t[i][1]*x+t[i][2]*x*x+t[i][3]*x*x*x)*100000)/100000;
}

double Zadanie71::ekstremum() {
	//t[4][1]x+2*t[4][2]*x+3*t[4][3]*x*x
	double delta = pow(2.0*t[4][2], 2)-4.0*t[4][1]*3.0*t[4][3];
	double pierwiastek_delta = sqrt(delta);
	double x1= (-2.0*t[4][2]-pierwiastek_delta)/(2.0*3.0*t[4][3]);
	double x2= (-2.0*t[4][2]+pierwiastek_delta)/(2.0*3.0*t[4][3]);
	if(x1>=4 && x1<5) {
		return x1;
	}
	if(x2>=4 && x2<5) {
		return x2;
	}
}

void Zadanie71::miejsce_zerowe() {
	this->szukanie(0.0, 1.0, 1);
	this->szukanie(2.0, 3.0, 3);
	this->szukanie(3.0, 4.0, 4);
	this->szukanie(4.0, 5.0, 5);
}

double Zadanie71::szukanie(double x1, double x2, int i) {
	double fx1 = this->funkcja(x1, i);
	double fx2 = this->funkcja(x2, i);
	double srednia = (x1 + x2)/2;
	double fsrednia =this->funkcja(srednia, i);
	
	if((fx1<0.0 && fx2>0.0 && fsrednia<0.0) || (fx1>0.0 && fx2<0.0 && fsrednia>0.0)) {
		this->szukanie(srednia, x2, i);
	}
	if((fx1>0.0 && fx2<0.0 && fsrednia<0.0) || (fx1<0.0 && fx2>0.0 && fsrednia>0.0)) {
		this->szukanie(x1, srednia, i);
	}
	if(fsrednia==0.0) {
		cout<<srednia<<"\n";
		wy<<srednia<<"\n";
		return srednia;
	}
}

Zadanie71::~Zadanie71() {
	we.close();
	wy.close();
}

int main(int argc, char** argv) {
	Zadanie71 z71;
	z71.wczytaj();
	int i = 0;
	double x=1.5;
	if(x>=0 && x<1) {
		i = 1;
	} else if(x>=1 && x<2) {
		i = 2;
	} else if(x>=2 && x<3) {
		i = 3;
	} else if(x>=3 && x<4) {
		i = 4;
	} else if(x>=4 && x<5) {
		i = 5;
	}
	
	cout<<"Zadanie 1: "<<z71.funkcja(x, i)<<"\n";
	z71.wy<<"Zadanie 1: "<<z71.funkcja(x, i)<<"\n";
	cout<<"Zadanie 2: "<<z71.ekstremum()<<"\n";
	z71.wy<<"Zadanie 2: "<<z71.ekstremum()<<"\n";
	cout<<"Zadanie 3: \n";
	z71.wy<<"Zadanie 3: \n";
	z71.miejsce_zerowe();
	return 0;
}
