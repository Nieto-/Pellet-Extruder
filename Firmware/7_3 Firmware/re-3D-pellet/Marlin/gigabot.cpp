// gigabot.cpp
//
// This source file is intended to isolate customized code for Marlin by 
// separating them into sections
//

#include "systems.h"

#if SYSTEM_SECTION == SUBSECTION(TEMPERATURE, 5)

#if HAS_TEMP_BED

// Derived from RepRap FiveD extruder::getTemperature()
// For bed temperature measurement.
float Temperature::analog2tempBed(const int raw) {
  #if ENABLED(BED_USES_THERMISTOR)
    float celsius = 0;
    byte i;

    for (i = 1; i < BEDTEMPTABLE_LEN; i++) {
      if (PGM_RD_W(BEDTEMPTABLE[i][0]) > raw) {
        celsius  = PGM_RD_W(BEDTEMPTABLE[i - 1][1]) +
                   (raw - PGM_RD_W(BEDTEMPTABLE[i - 1][0])) *
                   (float)(PGM_RD_W(BEDTEMPTABLE[i][1]) - PGM_RD_W(BEDTEMPTABLE[i - 1][1])) /
                   (float)(PGM_RD_W(BEDTEMPTABLE[i][0]) - PGM_RD_W(BEDTEMPTABLE[i - 1][0]));
        break;
      }
    }

    // Overflow: Set to last value in the table
    if (i == BEDTEMPTABLE_LEN) celsius = PGM_RD_W(BEDTEMPTABLE[i - 1][1]);

    return celsius;

  #elif defined(BED_USES_AD595)

    return (((((raw * 5.0) / 1024.0) / .005) / OVERSAMPLENR) * TEMP_SENSOR_AD8495_GAIN) + TEMP_SENSOR_AD8495_OFFSET;

  #else

    UNUSED(raw);
    return 0;

  #endif
}

#endif // HAS_TEMP_BED

#define SECTION_OVERRIDE

#endif


