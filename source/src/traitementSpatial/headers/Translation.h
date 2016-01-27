#ifndef TRANSLATION_H
#define TRANSLATION_H

#include "../../structure/headers/Command.h"
#include "../../base/headers/color.h"
#include "../../base/headers/image_png.h"

#include "../../structure/headers/Data.h"
#include <omp.h>

using namespace std;

class Translation : public Command
{
    public:
        Translation();
        Translation(Translation* pTranslation);
        Translation(string pStandAlone, string pParameter, string pNormal, string pDescription);
        virtual ~Translation();
        virtual void run(vector<string> pArgParam,string input, string output);
    protected:
    private:
        virtual bool isValid(vector<string> pArgParam);
        void translation(ImagePNG* img, int left, int up, Color* background);
};

#endif // TRANSLATION_H
