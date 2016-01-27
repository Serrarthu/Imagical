#include "headers/Translation.h"

Translation::Translation(): Command("","translation","","Translation") {}

Translation::~Translation(){}

Translation::Translation(Translation* pTranslation): Command(pTranslation) {}

Translation::Translation(string pStandAlone, string pParameter, string pNormal, string pDescription): Command(pStandAlone,pParameter,pNormal,pDescription) {}

bool Translation::isValid(vector<string> pArgParam){
unused(pArgParam);
if (pArgParam.size() == 2 && atoi(pArgParam[0].c_str()) != 0 && atoi(pArgParam[1].c_str()) != 0) return true;
else return false;
}

void Translation::run(vector<string> pArgParam,string input, string output){
	unused(pArgParam);
	ImagePNG* img = new ImagePNG();
	img->load(input);
	double start = Data::get_time();
	cout << &img << endl;
	translation(img,atoi(pArgParam[0].c_str()),atoi(pArgParam[1].c_str()), new Color(0,0,0,255));
	if (Data::CHRONO)	cout << description<<" effectue en " << 1000*(Data::get_time() - start)<<" ms"<<endl;
	img->save(output);
}

void Translation::translation(ImagePNG* img, int left, int up, Color* background) {
cout << &img << endl;
	#pragma omp parallel for schedule(static) num_threads(Data::NB_THREADS)
	for (int i = 0; i < (signed)img->getHeight(); i += 1)
	{
		for (int j = 0; j < (signed)img->getWidth(); j += 1)
		{
		#pragma omp critical
		{
			if ((i+up >= (signed)img->getHeight()) || i+up <1 || (j+left >= (signed)img->getWidth()) || j+left <0) background->fill(img, i, j);
			else {
				Color* newColor=new Color(img->red(i+up, j+left), img->green(i+up, j+left), img->blue(i+up, j+left), img->alpha(i+up, j+left));
				newColor->fill(img, i, j);
			}
		}
		}
	}
}
