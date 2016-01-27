#include "headers/Skiz.h"

Skiz::Skiz(): Command("skiz","","","Skiz") {}

Skiz::~Skiz(){}

Skiz::Skiz(Skiz* pSkiz): Command(pSkiz) {}

Skiz::Skiz(string pStandAlone, string pParameter, string pNormal, string pDescription): Command(pStandAlone,pParameter,pNormal,pDescription) {}

bool Skiz::isValid(vector<string> pArgParam){
unused(pArgParam);
if (pArgParam.size() == 0) return true;
else return false;
}

void Skiz::run(vector<string> pArgParam,string input, string output){
	unused(pArgParam);
	ImagePNG* img = new ImagePNG();
	img->load(input);
	double start = Data::get_time();
	skiz(img);
	if (Data::CHRONO)	cout << description<<" effectue en " << 1000*(Data::get_time() - start)<<" ms"<<endl;
	img->save(output);
}

int Skiz::pixelToGrey(ImagePNG* img, int i, int j) {
	return img->red(i,j)*luminance[0] + img->green(i,j)*luminance[1] + img->blue(i,j)*luminance[2];
}


void Skiz::skiz(ImagePNG* img) {
	ImagePNG* temp = new ImagePNG();
	temp->newImage(img->getHeight(), img->getWidth());

	Color* black = new Color(0,0,0,255);
	bool transformed = true;
	bool match = false;

	int filters[][4][4] = {{{1,2,0,0},
					{2,2,0,0},
					{0,0,0,0},
					{0,0,0,0}	},

				{	{0,0,2,1},
					{0,0,2,2},
					{0,0,0,0},
					{0,0,0,0}	},

				{	{0,0,0,0},
					{0,0,0,0},
					{2,2,0,0},
					{1,2,0,0}	},

				{	{0,0,0,0},
					{0,0,0,0},
					{0,0,2,2},
					{0,0,2,1}	},

				{	{1,1,1,1},
					{-1,2,2,-1},
					{0,0,0,0},
					{0,0,0,0}	},

				{	{0,0,-1,1},
					{0,0,2,1},
					{0,0,2,1},
					{0,0,-1,1}	},

				{	{0,0,0,0},
					{0,0,0,0},
					{-1,2,2,-1},
					{1,1,1,1}	},

				{	{1,-1,0,0},
					{1,2,0,0},
					{1,2,0,0},
					{1,-1,0,0}	}};
	while (transformed)
	{
		transformed = false;
		
		#pragma omp parallel for schedule(static) shared(temp) num_threads(Data::NB_THREADS)
		for (int i=0; i < (signed)img->getHeight() - 4; i++)
		{
			for (int j=0; j < (signed)img->getWidth() - 4; j++)
			{
				for (int f = 0; f < 8; f++)
				{
					match = true;
					for (int x = 0; x< 4; x ++)
					{
						for (int y = 0; y< 4; y ++)
						{
							if (((filters[f][x][y] == 0 || filters[f][x][y] == 2) & (pixelToGrey(img, i+x, j+y) != 255)) | (((filters[f][x][y] == 1) & (pixelToGrey(img, i+x, j+y) != 0))))
							{
								match = false;
								break;
							}
						}
						if (!match) break;
					}

					if (match) 
					{
						for (int x = 0; x< 4; x ++)
						{
							for (int y = 0; y< 4; y ++)
							{
								if (filters[f][x][y] == 2) black->fill(temp, i+x, j+y);
							}
						}
						transformed = true;
					}
				}
			}
		}
		*img = *temp;
	}
	*img = *temp;
}
