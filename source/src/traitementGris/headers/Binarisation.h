#ifndef BINARISATION_H
#define BINARISATION_H

#include <cmath>
#include "../../structure/headers/Command.h"
#include "../../base/headers/color.h"
#include "../../base/headers/image_png.h"

#include "../../structure/headers/Data.h"
#include <omp.h>

using namespace std;

class Binarisation : public Command
{
    public:
        Binarisation();
        Binarisation(Binarisation* pBinarisation);
        Binarisation(string pStandAlone, string pParameter, string pNormal, string pDescription);
        virtual ~Binarisation();
        virtual void run(vector<string> pArgParam,string input, string output);
    protected:
    private:
        virtual bool isValid(vector<string> pArgParam);
        void binarisation(ImagePNG* img, string filename);
        int* histogram(ImagePNG* img);
        int otsu(ImagePNG* img, int* histogram);
        int pixelToGrey(ImagePNG* img, int i, int j);
        void binarisation(ImagePNG* img, int threshold);
        void binarisation(ImagePNG* img);
};

#endif // BINARISATION_H
