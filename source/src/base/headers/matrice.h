#ifndef MATRICE_H_
#define MATRICE_H_
#include <iostream>
using namespace std;

class Matrice{

public:
	Matrice();
	Matrice(int r , int c);
	Matrice(const Matrice &m);
	Matrice(int r, int c, int* m);
	~Matrice();
	void display();
	const Matrice &operator =(const Matrice &m);
	int operator()(unsigned short int i, unsigned short int j) const;
	int &operator()(unsigned short int i, unsigned short int j);
	
	int getRows(){return rows;};
	int getColumns(){return columns;};
	void init(int r, int c, int* m);
private:
	int rows = 0;
	int columns = 0;
	int** matrice = NULL;
};
#endif /* MATRICE_H_ */
