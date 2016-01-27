#ifndef DILATATION_H
#define DILATATION_H

#include "../../structure/headers/Command.h"
#include "../../base/headers/color.h"
#include "../../base/headers/image_png.h"
#include "../../base/headers/mask.h"

#include "../../structure/headers/Data.h"
#include <omp.h>

using namespace std;

class Dilatation : public Command
{
    public:
        Dilatation();
        Dilatation(Dilatation* pDilatation);
        Dilatation(string pStandAlone, string pParameter, string pNormal, string pDescription);
        virtual ~Dilatation();
        virtual void run(vector<string> pArgParam,string input, string output);
    protected:
    private:
        virtual bool isValid(vector<string> pArgParam);
        Color* dilatation(ImagePNG* img, Mask* m);
        void morphologie(ImagePNG* img, int order);
};

#endif // DILATATION_H
