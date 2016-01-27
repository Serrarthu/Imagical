#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include "../../structure/headers/Command.h"
#include "../../base/headers/color.h"
#include "../../base/headers/image_png.h"

#include "../../structure/headers/Data.h"
#include <omp.h>

using namespace std;

class GrayScale : public Command
{
    public:
        GrayScale();
        GrayScale(GrayScale* pGrayScale);
        GrayScale(string pStandAlone, string pParameter, string pNormal, string pDescription);
        virtual ~GrayScale();
        virtual void run(vector<string> pArgParam,string input, string output);
    protected:
    private:
        virtual bool isValid(vector<string> pArgParam);
        void grayScale(ImagePNG* img);
        int pixelToGrey(ImagePNG* img, int i, int j);
};

#endif // GRAYSCALE_H
