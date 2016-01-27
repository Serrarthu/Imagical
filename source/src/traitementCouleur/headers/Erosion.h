#ifndef EROSION_H
#define EROSION_H

#include "../../structure/headers/Command.h"
#include "../../base/headers/color.h"
#include "../../base/headers/image_png.h"
#include "../../base/headers/mask.h"

#include "../../structure/headers/Data.h"
#include <omp.h>

using namespace std;

class Erosion : public Command
{
    public:
        Erosion();
        Erosion(Erosion* pErosion);
        Erosion(string pStandAlone, string pParameter, string pNormal, string pDescription);
        virtual ~Erosion();
        virtual void run(vector<string> pArgParam,string input, string output);
    protected:
    private:
        virtual bool isValid(vector<string> pArgParam);
        Color* erosion(ImagePNG* img, Mask* m);
        void morphologie(ImagePNG* img, int order);
};

#endif // EROSION_H
