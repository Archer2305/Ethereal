#include "main.h"
#include "globals.hpp"
#include "pneumatics.hpp"

okapi::Controller controller;

pneumaticSys wings(WINGS_ADI, WINGS_ACTUATE);
pneumaticSys blocker(BLOCKER_ADI, BLOCKER_ACTUATE);
    
