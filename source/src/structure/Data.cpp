#include "headers/Data.h"

#include "../traitementCouleur/headers/Difference.h"
#include "../traitementCouleur/headers/Dilatation.h"
#include "../traitementCouleur/headers/Erosion.h"
#include "../traitementCouleur/headers/Inversion.h"
#include "../traitementCouleur/headers/Saturation.h"

#include "../traitementFiltre/headers/Filtrage.h"
#include "../traitementFiltre/headers/Gradient.h"
#include "../traitementFiltre/headers/Skiz.h"

#include "../traitementGris/headers/Binarisation.h"
#include "../traitementGris/headers/ExportCSV.h"
#include "../traitementGris/headers/GrayScale.h"

#include "../traitementSpatial/headers/Translation.h"
#include "../traitementSpatial/headers/Rotation.h"

int Data::NB_THREADS = 1;
bool Data::CHRONO = false;

void Data::initialize(Facade* facade){
    facade->addStandAlone(new Inversion());
    facade->addStandAlone(new GrayScale());
    facade->addStandAlone(new Binarisation());
    facade->addStandAlone(new Gradient());
    facade->addStandAlone(new Skiz());

    facade->addParameter(new Saturation());
    facade->addParameter(new Translation());
    facade->addParameter(new Rotation());
    facade->addParameter(new ExportCSV());
    facade->addParameter(new Difference());
    facade->addParameter(new Erosion());
    facade->addParameter(new Dilatation());
    facade->addParameter(new Filtrage());
    
    facade->addParameter(new Parallel());
    facade->addStandAlone(new Chrono());
}

void Data::execute(Facade* facade){
	facade->parseFlag();
}

double Data::get_time() {
	struct timeval tv;
	gettimeofday(&tv,0);
	return (double) tv.tv_sec+tv.tv_usec*1e-6;
}
