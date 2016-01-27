#include "headers/Inversion.h"

Inversion::Inversion(): Command("inversion","","","Inversion") {}

Inversion::~Inversion(){}

Inversion::Inversion(Inversion* pInversion): Command(pInversion) {}

Inversion::Inversion(string pStandAlone, string pParameter, string pNormal, string pDescription): Command(pStandAlone,pParameter,pNormal,pDescription) {}

bool Inversion::isValid(vector<string> pArgParam){
unused(pArgParam);
if (pArgParam.size() == 0) return true;
else return false;
}

void Inversion::run(vector<string> pArgParam,string input, string output){
	unused(pArgParam);
	ImagePNG* img = new ImagePNG();
	img->load(input);
	double start = Data::get_time();
	inversion(img);
	if (Data::CHRONO)	cout << description<<" effectue en " << 1000*(Data::get_time() - start)<<" ms"<<endl;
	img->save(output);
}

void Inversion::inversion(ImagePNG* img) {
	#pragma omp parallel for schedule(static) num_threads(Data::NB_THREADS)
	for (unsigned int i = 0; i < img->getHeight(); i += 1)
	{
		for (unsigned int j = 0; j < img->getWidth(); j += 1)
		{
			img->red(i,j)=255-img->red(i,j);
			img->green(i,j)=255-img->green(i,j);
			img->blue(i,j)=255-img->blue(i,j);
		}
	}
}
