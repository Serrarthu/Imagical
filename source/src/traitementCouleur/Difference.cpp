#include "headers/Difference.h"

Difference::Difference(): Command("","difference","","Difference") {}

Difference::~Difference(){}

Difference::Difference(Difference* pDifference): Command(pDifference) {}

Difference::Difference(string pStandAlone, string pParameter, string pNormal, string pDescription): Command(pStandAlone,pParameter,pNormal,pDescription) {}

bool Difference::isValid(vector<string> pArgParam){
unused(pArgParam);
if (pArgParam.size() == 1) {
	ifstream file(pArgParam[0]);
	if (file.good()) return true;
	else return false;
}
else return false;
}

void Difference::run(vector<string> pArgParam,string input, string output){
	unused(pArgParam);
	ImagePNG* img = new ImagePNG();
	img->load(input);
	ImagePNG* img2 = new ImagePNG();
	img2->load(pArgParam[0]);
	double start = Data::get_time();
	difference(img, img2);
	if (Data::CHRONO)	cout << description<<" effectue en " << 1000*(Data::get_time() - start)<<" ms"<<endl;
	img->save(output);
}

void Difference::difference(ImagePNG* img1, ImagePNG* img2) {
	#pragma omp parallel for schedule(static) num_threads(Data::NB_THREADS)
	for (int i = 0; i < (signed)img1->getHeight(); i += 1)
	{
		if (i >= (signed)img2->getHeight()) i = img1->getHeight()-1;
		else{
		for (int j = 0; j < (signed)img1->getWidth(); j += 1)
		{
			if (j >= (signed)img2->getWidth()) i = img1->getWidth()-1;
			else{
			float coeff = img2->alpha(i,j)/255.0;
			img1->red(i,j)=max(0, img1->red(i,j) - (int)(img2->red(i,j)*coeff));
			img1->green(i,j)=max(0, img1->green(i,j) - (int)(img2->green(i,j)*coeff));
			img1->blue(i,j)=max(0, img1->blue(i,j) - (int)(img2->blue(i,j)*coeff));
			}
		}
		}
	}
}
