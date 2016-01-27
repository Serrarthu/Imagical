#ifndef __FILTER_H__
#define __FILTER_H__

#include <string>
#include <fstream>
#include <sstream>
#include "image_png.h"
#include "matrice.h"
#include "../../structure/headers/Data.h"
#include <omp.h>

#define testMin(a, b)  (((a) < (b)) ? (a) : (b))
#define testMax(a, b)  (((a) > (b)) ? (a) : (b))


class Filter
{
	public:
		Filter (string filename);
		Filter (Matrice* m, double f, double b);
		virtual ~Filter (){delete filter;};
		Filter(const Filter &f);
		const Filter &operator =(const Filter &f);
		
		void apply(ImagePNG* img);
		void display(){cout<< "factor= "<<factor<<", bias= "<<bias<<endl; filter->display();};

	private:
		double factor = 0;
		double bias = 0;
		Matrice* filter = new Matrice();
};

#endif /* __FILTER_H__ */

