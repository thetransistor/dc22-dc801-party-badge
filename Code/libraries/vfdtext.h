// authored by: d3c4f

#ifndef __VFDTEXT_H
#define __VFDTEXT_H

#ifdef __cplusplus
  extern "C" {
#endif

#include "main.h"

#define VFDTEXT_NUMOBJECTS  4      // Avoiding dynamic memory allocation...

typedef enum {
    DISABLED,
    RUNNING,
    STOPPED
} eVFDTextState;

typedef enum {
    NONE,       // No animation
    SCROLL,     // Scrolls in from left or right and stops
    BOUNCING,   // Bounces from the left to right, Repeating
    LOOPING,    // Looping Scroll, Repeating
    SLIDEIN,    // Animation
    SLIDEOUT,   // Animation
    ROLLIN,     // Animation
    ROLLOUT,    // Animation
    EXPLODE,    // Animation
    POWERUP,    // LowerCase to UpperCase Animation
    POWERDOWN,  // UpperCase to LowerCase Animation
    L33T,       // L33T Animation, Ongoing
    GLITCH      // Alpha-Numberic characters "freakout", Ongoing
} eVFDTextAnimation;

typedef struct {
    char* sourceText;
    uint8_t sourceLength;
    uint8_t y;
    uint8_t x;
    uint8_t width;
    uint32_t speed;
    eVFDTextAnimation style;
    eVFDTextState state;
    uint32_t lastUpdate;
    uint8_t direction;
    uint8_t count;
} VFDTextObject;


uint8_t VFDTextConfigure( uint8_t, char*, uint8_t, uint8_t, uint8_t, uint8_t, uint32_t, eVFDTextAnimation, eVFDTextState, uint8_t, uint8_t );
void VFDTextUpdate( void );
void VFDTextRefresh( uint8_t );


#ifdef __cplusplus
}
#endif

#endif
