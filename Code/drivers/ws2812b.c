// authored by: d3c4f

#include "ws2812b.h"
static void __attribute__ ((constructor)) Initialize(void);


// Initialize the RGB LED
static void Initialize()
{
  // Set RGB LED Data pin as an output
  LPC_GPIO->DIR[0] |= (1<<7);
}


// Set the color of the RGB LED
// Non-Standard Timing 1Wire Protocol. We'll just bit-bang this shiz
uint8_t SetRGBLEDColor( uint8_t red, uint8_t green, uint8_t blue )
{
  // TODO: all of this :S



  return 0;
}
