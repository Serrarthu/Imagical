#include "headers/ExportCSV.h"

ExportCSV::ExportCSV(): Command("","exportCSV","","Export CSV") {}

ExportCSV::~ExportCSV(){}

ExportCSV::ExportCSV(ExportCSV* pExportCSV): Command(pExportCSV) {}

ExportCSV::ExportCSV(string pStandAlone, string pParameter, string pNormal, string pDescription): Command(pStandAlone,pParameter,pNormal,pDescription) {}

bool ExportCSV::isValid(vector<string> pArgParam){
unused(pArgParam);
if (pArgParam.size() == 1) {
	ifstream file(pArgParam[0]);
	if (file.good()) return true;
	else return false;
}
else return false;
}

void ExportCSV::run(vector<string> pArgParam,string input, string output){
	unused(pArgParam);
	ImagePNG* img = new ImagePNG();
	img->load(input);
	double start = Data::get_time();
	exportCSV(img,pArgParam[0].c_str());
	if (Data::CHRONO)	cout << description<<" effectue en " << 1000*(Data::get_time() - start)<<" ms"<<endl;
	img->save(output);
}

int* ExportCSV::histogram(ImagePNG* img) {
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

int ExportCSV::pixelToGrey(ImagePNG* img, int i, int j) {
	return img->red(i,j)*luminance[0] + img->green(i,j)*luminance[1] + img->blue(i,j)*luminance[2];
}

void ExportCSV::exportCSV(ImagePNG* img, string filename) {
	int* hist = histogram(img);
	ofstream file;
	file.open (filename);
	for (int i = 0; i < 256; i += 1){file << hist[i] <<";";}
	file << endl;
	file.close();
}
