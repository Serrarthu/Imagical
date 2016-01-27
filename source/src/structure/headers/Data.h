#ifndef __DATA_H__
#define __DATA_H__

#include "Facade.h"
#include "Command.h"
#include "Chrono.h"
#include "Parallel.h"
#include <sys/time.h>

using namespace std;

class Data
{
    public:
        static void initialize(Facade* facade);
        static void execute(Facade* facade);
        static double get_time();
        static int NB_THREADS;
        static bool CHRONO;
};

#endif // DATA_H
