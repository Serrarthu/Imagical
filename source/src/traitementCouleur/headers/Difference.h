#ifndef DIFFERENCE_H
#define DIFFERENCE_H

#include <cstdlib>
#include <fstream>
#include "../../structure/headers/Command.h"
#include "../../base/headers/color.h"
#include "../../base/headers/image_png.h"

#include "../../structure/headers/Data.h"
#include <omp.h>

using namespace std;

class Difference : public Command
{
    public:
        Difference();
        Difference(Difference* pDifference);
        Difference(string pStandAlone, string pParameter, string pNormal, string pDescription);
        virtual ~Difference();
        virtual void run(vector<string> pArgParam,string input, string output);
    protected:
    private:
        virtual bool isValid(vector<string> pArgParam);
        void difference(ImagePNG* img, ImagePNG* img2);
};

#endif
