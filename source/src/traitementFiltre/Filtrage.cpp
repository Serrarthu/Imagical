#include "headers/Filtrage.h"

Filtrage::Filtrage(): Command("","filtrage","","Filtrage") {}

Filtrage::~Filtrage(){}

Filtrage::Filtrage(Filtrage* pFiltrage): Command(pFiltrage) {}

Filtrage::Filtrage(string pStandAlone, string pParameter, string pNormal, string pDescription): Command(pStandAlone,pParameter,pNormal,pDescription) {}

bool Filtrage::isValid(vector<string> pArgParam){
unused(pArgParam);
if (pArgParam.size() == 1) {
	ifstream file(pArgParam[0]);
	if (file.good()) return true;
	else return false;
}
else return false;
}

void Filtrage::run(vector<string> pArgParam,string input, string output){
	unused(pArgParam);
	ImagePNG* img = new ImagePNG();
	img->load(input);
	double start = Data::get_time();
	filtrage(img,pArgParam[0].c_str());
	if (Data::CHRONO)	cout << description<<" effectue en " << 1000*(Data::get_time() - start)<<" ms"<<endl;
	img->save(output);
}

void Filtrage::filtrage(ImagePNG* img, string s) {
	Filter* f = new Filter(s);
	f->apply(img);
}
