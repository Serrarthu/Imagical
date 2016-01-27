#ifndef SKIZ_H
#define SKIZ_H

#include <cstdlib>
#include "../../structure/headers/Command.h"
#include "../../base/headers/color.h"
#include "../../base/headers/image_png.h"
#include "../../base/headers/filter.h"

#include "../../structure/headers/Data.h"
#include <omp.h>

using namespace std;

class Skiz : public Command
{
    public:
        Skiz();
        Skiz(Skiz* pSkiz);
        Skiz(string pStandAlone, string pParameter, string pNormal, string pDescription);
        virtual ~Skiz();
        virtual void run(vector<string> pArgParam,string input, string output);
    protected:
    private:
        virtual bool isValid(vector<string> pArgParam);
        void skiz(ImagePNG* img);
        int pixelToGrey(ImagePNG* img, int i, int j);
};

#endif
