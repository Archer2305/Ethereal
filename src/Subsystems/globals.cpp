#include "main.h"
#include "globals.hpp"
#include "pneumatics.hpp"

okapi::Controller controller;

pneumaticSys wings('A', WINGS_ACTUATE);
pneumaticSys blocker('H', BLOCKER_ACTUATE);
    
