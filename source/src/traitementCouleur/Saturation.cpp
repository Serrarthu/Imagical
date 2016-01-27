#include "headers/Saturation.h"

Saturation::Saturation(): Command("","saturation","","Saturation") {}

Saturation::~Saturation(){}

Saturation::Saturation(Saturation* pSaturation): Command(pSaturation) {}

Saturation::Saturation(string pStandAlone, string pParameter, string pNormal, string pDescription): Command(pStandAlone,pParameter,pNormal,pDescription) {}

bool Saturation::isValid(vector<string> pArgParam){
unused(pArgParam);
if (pArgParam.size() == 1 && atof(pArgParam[0].c_str()) != 0.0) return true;
else return false;
}

void Saturation::run(vector<string> pArgParam,string input, string output){
	unused(pArgParam);
	ImagePNG* img = new ImagePNG();
	img->load(input);
	double start = Data::get_time();
	saturation(img,atof(pArgParam[0].c_str()));
	if (Data::CHRONO)	cout << description<<" effectue en " << 1000*(Data::get_time() - start)<<" ms"<<endl;
	img->save(output);
}

int Saturation::pixelToGrey(ImagePNG* img, int i, int j) {
	return img->red(i,j)*luminance[0] + img->green(i,j)*luminance[1] + img->blue(i,j)*luminance[2];
}

void Saturation::saturation(ImagePNG* img, double f) {
	#pragma omp parallel for schedule(static) num_threads(Data::NB_THREADS)
	for (unsigned int i = 0; i < img->getHeight(); i += 1)
	{
		for (unsigned int j = 0; j < img->getWidth(); j += 1)
		{
			int grey = pixelToGrey(img, i, j);
			img->red(i,j)=testMin(255,testMax(0,grey + f*(img->red(i,j)-grey)));
			img->green(i,j)=testMin(255,testMax(0,grey + f*(img->green(i,j)-grey)));
			img->blue(i,j)=testMin(255,testMax(0,grey + f*(img->blue(i,j)-grey)));
		}
	}
}
