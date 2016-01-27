#include "headers/GrayScale.h"

GrayScale::GrayScale(): Command("gray","","","Gray Scale") {}

GrayScale::~GrayScale(){}

GrayScale::GrayScale(GrayScale* pGrayScale): Command(pGrayScale) {}

GrayScale::GrayScale(string pStandAlone, string pParameter, string pNormal, string pDescription): Command(pStandAlone,pParameter,pNormal,pDescription) {}

bool GrayScale::isValid(vector<string> pArgParam){
unused(pArgParam);
if (pArgParam.size() == 0) return true;
else return false;
}

void GrayScale::run(vector<string> pArgParam,string input, string output){
	unused(pArgParam);
	ImagePNG* img = new ImagePNG();
	img->load(input);
	double start = Data::get_time();
	grayScale(img);
	if (Data::CHRONO)	cout << description<<" effectue en " << 1000*(Data::get_time() - start)<<" ms"<<endl;
	img->save(output);
}

int GrayScale::pixelToGrey(ImagePNG* img, int i, int j) {
	return img->red(i,j)*luminance[0] + img->green(i,j)*luminance[1] + img->blue(i,j)*luminance[2];
}

void GrayScale::grayScale(ImagePNG* img) {
	#pragma omp parallel for schedule(static) num_threads(Data::NB_THREADS)
	for (unsigned int i = 0; i < img->getHeight(); i += 1)
	{
		for (unsigned int j = 0; j < img->getWidth(); j += 1)
		{
			int grey = pixelToGrey(img, i, j);
			img->red(i,j)=grey;
			img->green(i,j)=grey;
			img->blue(i,j)=grey;
		}
	}
}
