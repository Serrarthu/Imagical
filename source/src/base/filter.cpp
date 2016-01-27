#include "headers/filter.h"

Filter::Filter (Matrice* m, double f, double b) {
	filter=m;
	factor=f;
	bias=b;
}


Filter::Filter (string filename){
	ifstream fichier(filename, ios::in);
	if(fichier)
	{	string line;
		int r;
		int c;

		getline(fichier, line);
		istringstream numberStream(line);
		numberStream >> factor;
		numberStream.seekg(ios::beg);

		getline(fichier, line);
		numberStream.str(line);
		numberStream >> bias;
		numberStream.seekg(ios::beg);

		getline(fichier, line);
		numberStream.str(line);
		numberStream >> r;
		numberStream.seekg(ios::beg);

		getline(fichier, line);
		numberStream.str(line);
		numberStream >> c;
		numberStream.seekg(ios::beg);

		filter = new Matrice(r,c);
		int i=0;
		double temp;
		while(getline(fichier, line)) {
			numberStream.str(line);
			numberStream.seekg(ios::beg);
			for (int j = 0; j< c; j++)
			{
				numberStream>>temp;
				(*filter)(i,j)=temp;
			}
			i++;
		}
		fichier.close();
	}
	else	cerr << "Impossible d'ouvrir le fichier !" << endl;
}


void Filter::apply(ImagePNG* img){
	#pragma omp parallel for schedule(static) num_threads(Data::NB_THREADS)
	for(int x = 0; x < (signed)img->getHeight(); x++)
	{
		for(int y = 0; y < (signed)img->getWidth(); y++)
		{
			double red = 0.0, green = 0.0, blue = 0.0;
			for(int filterX = 0; filterX < filter->getColumns(); filterX++)
			{
				for(int filterY = 0; filterY < filter->getRows(); filterY++)
				{
					int imageX = (int((x + filterX + img->getHeight()))) % (img->getHeight());
					int imageY = (int((y + filterY + img->getWidth()))) % (img->getWidth());
					red += img->red(imageX, imageY) * ((*filter)(filterX,filterY));
					green += img->green(imageX,imageY) * ((*filter)(filterX,filterY));
					blue += img->blue(imageX,imageY) *((*filter)(filterX,filterY));
				}
			}	
			img->red(x,y) = (int)testMin(testMax(factor * red + bias, 0), 255);
			img->green(x,y) = (int)testMin(testMax(factor * green + bias, 0), 255);
			img->blue(x,y) = (int)testMin(testMax(factor * blue + bias, 0), 255);
		}
	}
}
