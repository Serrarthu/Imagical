#include "headers/Erosion.h"

Erosion::Erosion(): Command("","erosion","","Erosion") {}

Erosion::~Erosion(){}

Erosion::Erosion(Erosion* pErosion): Command(pErosion) {}

Erosion::Erosion(string pStandAlone, string pParameter, string pNormal, string pDescription): Command(pStandAlone,pParameter,pNormal,pDescription) {}

bool Erosion::isValid(vector<string> pArgParam){
unused(pArgParam);
if (pArgParam.size() == 1 && atoi(pArgParam[0].c_str()) != 0) return true;
else return false;
}

void Erosion::run(vector<string> pArgParam,string input, string output){
	unused(pArgParam);
	ImagePNG* img = new ImagePNG();
	img->load(input);
	double start = Data::get_time();
	morphologie(img,atoi(pArgParam[0].c_str()));
	if (Data::CHRONO)	cout << description<<" effectue en " << 1000*(Data::get_time() - start)<<" ms"<<endl;
	img->save(output);
}

Color* Erosion::erosion(ImagePNG* img, Mask* m) {
	Color* minColor = new Color(img, m->getMask()[0][0], m->getMask()[0][1]);
	vector< vector<int> > v = m->getMask();
	#pragma omp parallel for schedule(static) num_threads(Data::NB_THREADS)
	for (int i=0; i<(signed)v.size(); i++) {
		if (v[i][0] < (signed)img->getHeight() && v[i][0] >=0 && v[i][1] < (signed)img->getWidth() && v[i][1] >= 0) {
			Color* temp = new Color(img, v[i][0], v[i][1]);
			int grey = temp->toGrey();
			if(grey == 255) {
			i = v.size()-1;
			*minColor=*temp;
			}
			if ( grey < minColor->toGrey()) *minColor=*temp;
		}
	}
	return minColor;
}

void Erosion::morphologie(ImagePNG* img, int order) {
	ImagePNG* tmp = new ImagePNG(*img);
	Mask* m = new Mask(Shape::SQUARE, order);
	do{m->fill(tmp, erosion(img, m)); } while (m->moveToNext(img) !=-1 );
	*img=*tmp;
}
