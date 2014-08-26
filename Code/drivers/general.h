// authored by: d3c4f

#ifndef __GENERAL_H
#define __GENERAL_H

#ifdef __cplusplus
  extern "C" {
#endif

#include "main.h"

uint8_t DebugLEDOn( void );
uint8_t DebugLEDOff( void );
uint8_t GetBatteryStatus( void );

#ifdef __cplusplus
}
#endif

#endif
