#ifndef GRADIENT_H
#define GRADIENT_H

#include <cstdlib>
#include "../../structure/headers/Command.h"
#include "../../base/headers/color.h"
#include "../../base/headers/image_png.h"
#include "../../base/headers/filter.h"

#include "../../structure/headers/Data.h"
#include <omp.h>


using namespace std;

class Gradient : public Command
{
    public:
        Gradient();
        Gradient(Gradient* pGradient);
        Gradient(string pStandAlone, string pParameter, string pNormal, string pDescription);
        virtual ~Gradient();
        virtual void run(vector<string> pArgParam,string input, string output);
    protected:
    private:
        virtual bool isValid(vector<string> pArgParam);
        void gradient(ImagePNG* img);
};

#endif
