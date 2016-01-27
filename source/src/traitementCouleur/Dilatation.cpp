#include "headers/Dilatation.h"

Dilatation::Dilatation(): Command("","dilatation","","Dilatation") {}

Dilatation::~Dilatation(){}

Dilatation::Dilatation(Dilatation* pDilatation): Command(pDilatation) {}

Dilatation::Dilatation(string pStandAlone, string pParameter, string pNormal, string pDescription): Command(pStandAlone,pParameter,pNormal,pDescription) {}

bool Dilatation::isValid(vector<string> pArgParam){
unused(pArgParam);
if (pArgParam.size() == 1 && atoi(pArgParam[0].c_str()) != 0) return true;
else return false;
}

void Dilatation::run(vector<string> pArgParam,string input, string output){
	unused(pArgParam);
	ImagePNG* img = new ImagePNG();
	img->load(input);
	double start = Data::get_time();
	morphologie(img,atoi(pArgParam[0].c_str()));
	if (Data::CHRONO)	cout << description<<" effectue en " << 1000*(Data::get_time() - start)<<" ms"<<endl;
	img->save(output);
}

Color* Dilatation::dilatation(ImagePNG* img, Mask* m) {
	Color* maxColor = new Color(img, m->getMask()[0][0], m->getMask()[0][1]);
	vector< vector<int> > v = m->getMask();
	#pragma omp parallel for schedule(static) num_threads(Data::NB_THREADS)
	for (int i=0; i<(signed)v.size(); i++) {
		if (v[i][0] < (signed)img->getHeight() && v[i][0] >=0 && v[i][1] < (signed)img->getWidth() && v[i][1] >= 0) {
			Color* temp = new Color(img, v[i][0], v[i][1]);
			int grey = (new Color(img, v[i][0], v[i][1]))->toGrey();
			if(grey == 255) {
			i = v.size()-1;
			*maxColor=*temp;
			}
			else if (grey > maxColor->toGrey()) *maxColor=*temp;
		}
	}
	return maxColor;
}

void Dilatation::morphologie(ImagePNG* img, int order) {
	ImagePNG* tmp = new ImagePNG(*img);
	Mask* m = new Mask(Shape::SQUARE, order);
	do{m->fill(tmp, dilatation(img, m)); } while (m->moveToNext(img) !=-1 );
	*img=*tmp;
}
