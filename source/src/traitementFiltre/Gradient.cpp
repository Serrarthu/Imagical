#include "headers/Gradient.h"

Gradient::Gradient(): Command("gradient","","","Gradient") {}

Gradient::~Gradient(){}

Gradient::Gradient(Gradient* pGradient): Command(pGradient) {}

Gradient::Gradient(string pStandAlone, string pParameter, string pNormal, string pDescription): Command(pStandAlone,pParameter,pNormal,pDescription) {}

bool Gradient::isValid(vector<string> pArgParam){
unused(pArgParam);
if (pArgParam.size() == 0) return true;
else return false;
}

void Gradient::run(vector<string> pArgParam,string input, string output){
	unused(pArgParam);
	ImagePNG* img = new ImagePNG();
	img->load(input);
	double start = Data::get_time();
	gradient(img);
	if (Data::CHRONO)	cout << description<<" effectue en " << 1000*(Data::get_time() - start)<<" ms"<<endl;
	img->save(output);
}

void Gradient::gradient(ImagePNG* img) {

	int * temp = new int[9];
	temp[0]=1;temp[1]=0;temp[2]=-1;temp[3]=1;temp[4]=0;temp[5]=-1;temp[6]=1;temp[7]=0;temp[8]=-1;
	Matrice* m = new Matrice(3,3,temp);
	Filter* f = new Filter(m, 1, 100);
	f->apply(img);
}
