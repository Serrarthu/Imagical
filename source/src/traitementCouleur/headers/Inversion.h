#ifndef INVERSION_H
#define INVERSION_H

#include "../../structure/headers/Command.h"
#include "../../base/headers/color.h"
#include "../../base/headers/image_png.h"

#include "../../structure/headers/Data.h"
#include <omp.h>

using namespace std;

class Inversion : public Command
{
    public:
        Inversion();
        Inversion(Inversion* pInversion);
        Inversion(string pStandAlone, string pParameter, string pNormal, string pDescription);
        virtual ~Inversion();
        virtual void run(vector<string> pArgParam,string input, string output);
    protected:
    private:
        virtual bool isValid(vector<string> pArgParam);
        void inversion(ImagePNG* img);
};

#endif // INVERSION_H
