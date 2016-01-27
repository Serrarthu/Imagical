#include "headers/Binarisation.h"

Binarisation::Binarisation(): Command("binarisation","","","Binarisation") {}

Binarisation::~Binarisation(){}

Binarisation::Binarisation(Binarisation* pBinarisation): Command(pBinarisation) {}

Binarisation::Binarisation(string pStandAlone, string pParameter, string pNormal, string pDescription): Command(pStandAlone,pParameter,pNormal,pDescription) {}

bool Binarisation::isValid(vector<string> pArgParam){
unused(pArgParam);
if (pArgParam.size() == 0) return true;
else return false;
}

void Binarisation::run(vector<string> pArgParam,string input, string output){
	unused(pArgParam);
	ImagePNG* img = new ImagePNG();
	img->load(input);
	double start = Data::get_time();
	binarisation(img);
	if (Data::CHRONO)	cout << description<<" effectue en " << 1000*(Data::get_time() - start)<<" ms"<<endl;
	img->save(output);
}

int* Binarisation::histogram(ImagePNG* img) {
	static int hist[256];
//	initialisation de tout les champs a 0
	for (int i = 0; i < 256; i += 1){hist[i]=0;}
//	construction de l'histogramme en niveaux de gris
	#pragma omp parallel for schedule(static) num_threads(Data::NB_THREADS)
	for (int i = 0; i < (signed)img->getHeight(); i += 1)
	{
		for (int j = 0; j < (signed)img->getWidth(); j += 1)
		{
			int grey = pixelToGrey(img, i, j);
			hist[grey]++;
		}
	}
	return hist;
}

int Binarisation::otsu(ImagePNG* img, int* histogram) {
	double  w = 0;                // first order cumulative
	double  u = 0;                // second order cumulative
	double  uT = 0;               // total mean level

	double  x,y;		// working variables
	double threshold = 0.0;

	double  histNormalized[256];  // normalized histogram values

	// Create normalised histogram values
	// (size=image width * image height)
	for (int i=0; i<256; i++) {
		histNormalized[i] = histogram[i]/(float)(img->getHeight()*img->getWidth());
		uT+=(i+1)*histNormalized[i];
	}
	for (int i=0; i<256; i++) {
		w+=histNormalized[i];
		u+=(i+1)*histNormalized[i];
		x = (uT * w - u);
		y = (x * x) / ( w * (1.0-w) );
		if (y>threshold) threshold=y;
	}
	return (int)(2*sqrt(threshold));
}

int Binarisation::pixelToGrey(ImagePNG* img, int i, int j) {
	return img->red(i,j)*luminance[0] + img->green(i,j)*luminance[1] + img->blue(i,j)*luminance[2];
}

void Binarisation::binarisation(ImagePNG* img, int threshold) {
	Color* white = new Color(255,255,255,255);
	Color* black = new Color(0,0,0,255);
	#pragma omp parallel for schedule(static) num_threads(Data::NB_THREADS)
	for (int i = 0; i < (signed)img->getHeight(); i += 1)
	{
		#pragma omp parallel for schedule(static) num_threads(Data::NB_THREADS)
		for (int j = 0; j < (signed)img->getWidth(); j += 1)
		{
			int grey = pixelToGrey(img, i, j);
			if (grey >= threshold) white->fill(img, i,j);
			else black->fill(img, i,j);
		}
	}
}

void Binarisation::binarisation(ImagePNG* img) {binarisation(img, otsu(img, histogram(img)));}
