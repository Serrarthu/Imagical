#ifndef SATURATION_H
#define SATURATION_H

#include <cstdlib>
#include "../../structure/headers/Command.h"
#include "../../base/headers/color.h"
#include "../../base/headers/image_png.h"

#include "../../structure/headers/Data.h"
#include <omp.h>

using namespace std;

class Saturation : public Command
{
    public:
        Saturation();
        Saturation(Saturation* pSaturation);
        Saturation(string pStandAlone, string pParameter, string pNormal, string pDescription);
        virtual ~Saturation();
        virtual void run(vector<string> pArgParam,string input, string output);
    protected:
    private:
        virtual bool isValid(vector<string> pArgParam);
        void saturation(ImagePNG* img, double f);
        int pixelToGrey(ImagePNG* img, int i, int j);
};

#endif // SATURATION_H
