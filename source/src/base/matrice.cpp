#include "headers/matrice.h"

Matrice::Matrice() {
	Matrice(0,0);
}

Matrice::Matrice(int r, int c){
	rows=r;
	columns=c;
	matrice = new int * [r];
	for (int i=0; i<r; ++i) {matrice [i] = new int [c];}
}

Matrice::Matrice(int r, int c, int* m) {
	rows=r;
	columns=c;
	matrice = new int * [r];
	for(int i=0; i<r; i++) {
		matrice [i] = new int [c];
		for (int j =0; j<c; j++)
			matrice[i][j]=m[c*i+j];
	}
}

Matrice::~Matrice(){
	if (matrice) { 
		for(int i=0; i<rows ; i++) {delete matrice[i];}
		delete [] matrice;
	} 
}

Matrice::Matrice(const Matrice &m)
{
	rows=m.rows;
	columns=m.columns;
	matrice = new int * [rows];
	for (int i=0; i<rows; ++i) {matrice [i] = new int [columns];}
}

const Matrice &Matrice::operator =(const Matrice &m){
	if ( &m != this ) {
		rows=m.rows;
		columns=m.columns;
		for(int i = 0; i < rows; i++)
			for(int j = 0; j < columns; j++)	(*this)(i,j) = m(i,j);
	}
	return *this;
}


void Matrice::display(){
	cout<<"-----------------------------";
	cout << endl;
	for(int i=0; i<rows ; i++) {
		for(int j=0; j<columns ; j++) {cout<< (*this)(i,j) <<"  ";}
		cout << endl;
	}
	cout<<"-----------------------------";
	cout << endl;
}


int & Matrice::operator()(unsigned short int i, unsigned short int j)
{
	if (i>=rows && j>=columns) cout << "offset"<<endl;
	return matrice[i][j];
}

int Matrice::operator()(unsigned short int i, unsigned short int j) const
{
	if (i>=rows && j>=columns) cout << "offset"<<endl;
	return matrice[i][j];
}
