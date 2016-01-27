#ifndef ROTATION_H
#define ROTATION_H

#include <cmath>
#include "../../structure/headers/Command.h"
#include "../../base/headers/color.h"
#include "../../base/headers/image_png.h"

#include "../../structure/headers/Data.h"
#include <omp.h>

using namespace std;

class Rotation : public Command
{
    public:
        Rotation();
        Rotation(Rotation* pRotation);
        Rotation(string pStandAlone, string pParameter, string pNormal, string pDescription);
        virtual ~Rotation();
        virtual void run(vector<string> pArgParam,string input, string output);
    protected:
    private:
        virtual bool isValid(vector<string> pArgParam);
        void rotation(ImagePNG* img, double theta, Color* background);
};

#endif // ROTATION_H
