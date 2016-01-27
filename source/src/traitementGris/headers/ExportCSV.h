#ifndef EXPORTCSV_H
#define EXPORTCSV_H

#include <fstream>
#include <sstream>
#include "../../structure/headers/Command.h"
#include "../../base/headers/color.h"
#include "../../base/headers/image_png.h"

#include "../../structure/headers/Data.h"
#include <omp.h>

using namespace std;

class ExportCSV : public Command
{
    public:
        ExportCSV();
        ExportCSV(ExportCSV* pExportCSV);
        ExportCSV(string pStandAlone, string pParameter, string pNormal, string pDescription);
        virtual ~ExportCSV();
        virtual void run(vector<string> pArgParam,string input, string output);
    protected:
    private:
        virtual bool isValid(vector<string> pArgParam);
        void exportCSV(ImagePNG* img, string filename);
        int* histogram(ImagePNG* img);
        int pixelToGrey(ImagePNG* img, int i, int j);
};

#endif // EXPORTCSV_H
