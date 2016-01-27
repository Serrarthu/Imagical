#include "headers/Rotation.h"

Rotation::Rotation(): Command("","rotation","","Rotation") {}

Rotation::~Rotation(){}

Rotation::Rotation(Rotation* pRotation): Command(pRotation) {}

Rotation::Rotation(string pStandAlone, string pParameter, string pNormal, string pDescription): Command(pStandAlone,pParameter,pNormal,pDescription) {}

bool Rotation::isValid(vector<string> pArgParam){
unused(pArgParam);
if (pArgParam.size() == 1 && atof(pArgParam[0].c_str()) != 0.0) return true;
else return false;
}

void Rotation::run(vector<string> pArgParam,string input, string output){
	unused(pArgParam);
	ImagePNG* img = new ImagePNG();
	img->load(input);
	double start = Data::get_time();
	rotation(img,atof(pArgParam[0].c_str()), new Color(0,0,0,255));
	if (Data::CHRONO)	cout << description<<" effectue en " << 1000*(Data::get_time() - start)<<" ms"<<endl;
	img->save(output);
}

void Rotation::rotation(ImagePNG* img, double theta, Color* background){
	//conversion des degrees en gradians
	theta = theta*atan(1)/45;

	Color* newColor;
	ImagePNG* temp = new ImagePNG();

//	calcul de l'emplacement des coins de la nouvelle image
	double corner1x=(img->getHeight()*-sin(theta));
	double corner1y=(img->getHeight()*cos(theta));

	double corner2x=(img->getWidth()*cos(theta)-img->getHeight()*sin(theta));
	double corner2y=(img->getHeight()*cos(theta)+img->getWidth()*sin(theta));

	double corner3x=(img->getWidth()*cos(theta));
	double corner3y=(img->getWidth()*sin(theta));

//	calcul des dimensions de la nouvelle image
	int newHeight= (int)ceil(fabs(testMax(corner1x,testMax(corner2x,corner3x)))-testMin(0,testMin(corner1x,testMin(corner2x,corner3x))));
	int newWidth = (int)ceil(fabs(testMax(corner1y,testMax(corner2y,corner3y)))-testMin(0,testMin(corner1y,testMin(corner2y,corner3y))));

//	attribution des nouvelles dimensions
	temp->newImage(newWidth, newHeight);
	#pragma omp parallel for schedule(static) num_threads(Data::NB_THREADS)
	for (int i = 0; i < (signed)temp->getHeight(); i += 1)
	{
		for (int j = 0; j < (signed)temp->getWidth(); j += 1)
		{
			int posX=(int)floor((((i-temp->getHeight()/2.0)*cos(theta) + (j-temp->getWidth()/2.0)*sin(theta))+img->getHeight()/2.0));
			int posY=(int)floor((((j-temp->getWidth()/2.0)*cos(theta) - (i-temp->getHeight()/2.0)*sin(theta))+img->getWidth()/2.0));
			//si le point de la nouvelle image n'est pas dans l'image d'origine, on le remplie avec la couleur du background
			if (posX < 0 || posX >= (signed)img->getHeight() || posY < 0 || posY >= (signed)img->getWidth()) background->fill(temp, i,j);
			//sinon on remplie le pixel dans la nouvelle image
			else {
				newColor=new Color(img->red(posX, posY), img->green(posX, posY), img->blue(posX, posY), img->alpha(posX, posY));
				newColor->fill(temp, i, j);
			}
		}
	}
	*img= *temp;
}
