#ifndef FILTRAGE_H
#define FILTRAGE_H

#include <cstdlib>
#include <fstream>
#include <sstream>
#include "../../structure/headers/Command.h"
#include "../../base/headers/color.h"
#include "../../base/headers/image_png.h"
#include "../../base/headers/filter.h"

#include "../../structure/headers/Data.h"
#include <omp.h>


using namespace std;

class Filtrage : public Command
{
    public:
        Filtrage();
        Filtrage(Filtrage* pFiltrage);
        Filtrage(string pStandAlone, string pParameter, string pNormal, string pDescription);
        virtual ~Filtrage();
        virtual void run(vector<string> pArgParam,string input, string output);
    protected:
    private:
        virtual bool isValid(vector<string> pArgParam);
        void filtrage(ImagePNG* img, string s);
};

#endif
