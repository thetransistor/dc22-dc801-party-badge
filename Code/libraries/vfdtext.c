// authored by: d3c4f

#include "vfdtext.h"
#include "drivers/vfd.h"
static void __attribute__ ((constructor)) Initialize(void);

static VFDTextObject VFDTexts[VFDTEXT_NUMOBJECTS];
static uint8_t VFDTextInverseCasing( uint8_t );
static uint8_t VFDText1337( uint8_t );
static uint8_t VFDTextToLower( uint8_t );
static uint8_t VFDTextToUpper( uint8_t );

static uint32_t randu( void );
static uint32_t rndSeed;


// Set the default values for the TextObjects
static void Initialize( void )
{
    // Iterate through each text object
    for( uint8_t temp = 0; temp < VFDTEXT_NUMOBJECTS; temp++ )
    {
        VFDTexts[temp].sourceText = 0; // Woooo, free stuff!
        VFDTexts[temp].sourceLength = 0;
        VFDTexts[temp].y = 0;
        VFDTexts[temp].x = 0;
        VFDTexts[temp].width = 0;
        VFDTexts[temp].speed = 0;
        VFDTexts[temp].style = NONE;
        VFDTexts[temp].state = DISABLED;
        VFDTexts[temp].lastUpdate = 0;
        VFDTexts[temp].direction = 0;
        VFDTexts[temp].count = 0;
    }
}


// Configure a VFDText 'object'
uint8_t VFDTextConfigure(
    uint8_t objNumber,
    char* text,
    uint8_t textLen,
    uint8_t y,
    uint8_t startx,
    uint8_t widthx,
    uint32_t newSpeed,
    eVFDTextAnimation newStyle,
    eVFDTextState newState,
    uint8_t newDir,
    uint8_t newCount
)
{
    // Validate Update
    if( objNumber > VFDTEXT_NUMOBJECTS ) return 1;
    if( textLen > VFD_BUFFER_LENGTH ) return 2;
    if( y >= VFD_BUFFER_HEIGHT ) return 3;
    if( startx > VFD_BUFFER_LENGTH ) return 4;
    if( startx + widthx > VFD_BUFFER_LENGTH ) return 4;
    if( newDir > 1 ) return 5;

    VFDTexts[objNumber].sourceText = text;
    VFDTexts[objNumber].sourceLength = textLen;
    VFDTexts[objNumber].y = y;
    VFDTexts[objNumber].x = startx;
    VFDTexts[objNumber].width = widthx;
    VFDTexts[objNumber].speed = newSpeed;
    VFDTexts[objNumber].style = newStyle;
    VFDTexts[objNumber].state = newState;
    VFDTexts[objNumber].lastUpdate = 0;
    VFDTexts[objNumber].direction = newDir;
    VFDTexts[objNumber].count = newCount;

    VFDTextRefresh(objNumber); // Do the initial drawing
    return 0;
}


// Update each object, in a timely mannor
void VFDTextUpdate()
{
    uint32_t currentTicks = getMsTicks();

    // Iterate through each text object
    for( uint8_t temp = 0; temp < VFDTEXT_NUMOBJECTS; temp++ )
    {
        // Check if needs updating
        if( VFDTexts[temp].state == DISABLED ||
            VFDTexts[temp].state == STOPPED ||
          ( VFDTexts[temp].lastUpdate + VFDTexts[temp].speed ) > currentTicks )
        {
            continue;
        }
        VFDTextRefresh(temp);
    }
}


// Update one object, regardless of timer / stopped state.
void VFDTextRefresh( uint8_t objNumber )
{
    if( VFDTexts[objNumber].state == DISABLED ) return;
    uint32_t currentTicks = getMsTicks();

    // Set the current position, return if there is an error
    if( VFDSetPosition( VFDTexts[objNumber].y, VFDTexts[objNumber].x ) ) return;

    // Process the next 'frame' (This could probably be greatly simplified...)
    switch( VFDTexts[objNumber].style )
    {
        case SCROLL:   // Scrolls in from left or right and stops
            if( VFDTexts[objNumber].direction == 0 ){
                // Left to Right
                if( VFDTexts[objNumber].count < VFDTexts[objNumber].width
                  || VFDTexts[objNumber].count < VFDTexts[objNumber].sourceLength )
                {
                    for( uint8_t temp = 0; temp < VFDTexts[objNumber].width
                      && temp < ( VFDTexts[objNumber].count + 1 ); temp++ )
                    {
                        if( VFDTexts[objNumber].count >= VFDTexts[objNumber].sourceLength
                          && VFDTexts[objNumber].count - temp >= (VFDTexts[objNumber].sourceLength) ){
                            VFDWriteChar( ' ' ); // Clear

                        } else {
                            VFDWriteChar( VFDTexts[objNumber].sourceText[ VFDTexts[objNumber].sourceLength - VFDTexts[objNumber].count + temp - 1 ] );
                        }
                    }
                    VFDTexts[objNumber].count++;
                } else {
                    VFDTexts[objNumber].state = STOPPED;
                }

            } else {
                // Right to Left
                if( VFDTexts[objNumber].count <= VFDTexts[objNumber].width
                  || VFDTexts[objNumber].count <= VFDTexts[objNumber].sourceLength )
                {
                    for( uint8_t temp = 0; temp < VFDTexts[objNumber].width; temp++ )
                    {
                        if( VFDTexts[objNumber].width >= VFDTexts[objNumber].count
                          &&  VFDTexts[objNumber].width - VFDTexts[objNumber].count > temp){
                            VFDWriteChar( '*' ); // Pad with leading spaces ...
                        } else if( temp - ( VFDTexts[objNumber].width - VFDTexts[objNumber].count ) < VFDTexts[objNumber].sourceLength ){
                            VFDWriteChar( VFDTexts[objNumber].sourceText[ temp - ( VFDTexts[objNumber].width - VFDTexts[objNumber].count ) ] );
                        } else {
                            VFDWriteChar( '$' ); // Clear trailing ...
                        }
                    }
                    VFDTexts[objNumber].count++;
                } else {
                    VFDTexts[objNumber].state = STOPPED;
                }

            }
            break;

        case POWERUP:    // LowerCase to UpperCase Animation
            for( uint8_t temp = 0; temp < VFDTexts[objNumber].width
              && temp < VFDTexts[objNumber].sourceLength; temp++ )
            {
                if( VFDTexts[objNumber].count % 5 == 0 && VFDTexts[objNumber].count >= 5 ){
                    VFDWriteChar( VFDTextToUpper( VFDTexts[objNumber].sourceText[temp] ) );
                } else {
                    VFDWriteChar( VFDTextToLower( VFDTexts[objNumber].sourceText[temp] ) );
                }
            }
            if( VFDTexts[objNumber].speed < 25 && VFDTexts[objNumber].count % 5 == 0 ){
                VFDTexts[objNumber].state = STOPPED;
            } else {
                VFDTexts[objNumber].count++;
                if( VFDTexts[objNumber].count % 5 == 0 ) VFDTexts[objNumber].speed /= 2;
            }
            break;

        case POWERDOWN:  // UpperCase to LowerCase Animation
            for( uint8_t temp = 0; temp < VFDTexts[objNumber].width
              && temp < VFDTexts[objNumber].sourceLength; temp++ )
            {
                if( VFDTexts[objNumber].count % 5 == 0 && VFDTexts[objNumber].count >= 5 ){
                    VFDWriteChar( VFDTextToLower( VFDTexts[objNumber].sourceText[temp] ) );
                } else {
                    VFDWriteChar( VFDTextToUpper( VFDTexts[objNumber].sourceText[temp] ) );
                }
            }
            if( VFDTexts[objNumber].speed < 25 && VFDTexts[objNumber].count % 5 == 0 ){
                VFDTexts[objNumber].state = STOPPED;
            } else {
                VFDTexts[objNumber].count++;
                if( VFDTexts[objNumber].count % 5 == 0 ) VFDTexts[objNumber].speed /= 2;
            }
            break;

        case L33T:       // L33T Animation, Ongoing
            for( uint8_t temp = 0; temp < VFDTexts[objNumber].width
              && temp < VFDTexts[objNumber].sourceLength; temp++ )
            {
                switch( randu() % 42 ){
                    case 1:
                        VFDWriteChar( VFDText1337( VFDTexts[objNumber].sourceText[temp] ) );
                        break;

                    default:
                        VFDWriteChar( VFDTexts[objNumber].sourceText[temp] );
                        break;
                }
            }
            break;

        case GLITCH:     // "freakout", Ongoing
            for( uint8_t temp = 0; temp < VFDTexts[objNumber].width
              && temp < VFDTexts[objNumber].sourceLength; temp++ )
            {
                switch( randu() % 100 ){
                    case 1:
                    case 2:
                        VFDWriteChar( VFDTextInverseCasing( VFDTexts[objNumber].sourceText[temp] ) );
                        break;

                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                        VFDWriteChar( VFDText1337( VFDTexts[objNumber].sourceText[temp] ) );
                        break;

                    case 8:
                        VFDWriteChar( ( randu() % 0xEF ) + 0x0F );
                        break;

                    default:
                        VFDWriteChar( VFDTexts[objNumber].sourceText[temp] );
                        break;
                }
            }
            VFDTexts[objNumber].speed = (randu() % 800) + 100;
            break;


        // TODO: Finish this up
        case BOUNCING:   // Bounces from the left to right, Repeating

        case LOOPING:    // Looping Scroll, Repeating

        case SLIDEIN:    // Animation

        case SLIDEOUT:   // Animation

        case ROLLIN:     // Animation

        case ROLLOUT:    // Animation

        case EXPLODE:    // Animation

        case NONE:       // No animation. Place text, keep updated
            if( VFDTexts[objNumber].width > VFDTexts[objNumber].sourceLength ){
                VFDWriteText( VFDTexts[objNumber].sourceText, VFDTexts[objNumber].sourceLength, VFDTexts[objNumber].y, VFDTexts[objNumber].x );
            } else {
                VFDWriteText( VFDTexts[objNumber].sourceText, VFDTexts[objNumber].width, VFDTexts[objNumber].y, VFDTexts[objNumber].x );
            }
            // VFDTexts[objNumber].state = STOPPED;
            break;

        default:
            break;
    }

    VFDTexts[objNumber].lastUpdate = currentTicks;
}


// Inverse Letter Casing
static uint8_t VFDTextInverseCasing( uint8_t original){
    // Uppercase to Lowercase
    if( original >= 0x41 && original <= 0x5A) return original + 0x20;

    // Lowercase to Uppercase
    if( original >= 0x61 && original <= 0x7A) return original - 0x20;

    return original; // Out of scope
}


// Make Alphas Lowercase
static uint8_t VFDTextToLower( uint8_t original){
    // Uppercase to Lowercase
    if( original >= 0x41 && original <= 0x5A) return original + 0x20;
    return original; // No updated needed
}


// Make Alphas Uppercase
static uint8_t VFDTextToUpper( uint8_t original){
    // Lowercase to Uppercase
    if( original >= 0x61 && original <= 0x7A) return original - 0x20;
    return original; // No updated needed
}


// Replace Vowels with Numbers, etc
static uint8_t VFDText1337( uint8_t original ){
    switch( original ){
        case 'A':
        case 'a':
            return '4';
            break;
        case 'B':
        case 'b':
            return '8';
            break;
        case 'C':
        case 'c':
            return '<';
            break;
        case 'E':
        case 'e':
            return '3';
            break;
        case 'G':
        case 'g':
            return '6';
            break;
        case 'I':
        case 'i':
        case 'L':
        case 'l':
            return '1';
            break;
        case 'O':
        case 'o':
            return '0';
            break;
        case 'S':
        case 's':
            return '5';
            break;
        case 'T':
        case 't':
            return '7';
            break;
        case '1':
            return '!';
            break;
        case '3':
            return 'E';
            break;
        case '4':
            return 'A';
            break;
        case '5':
            return 'S';
            break;
        case '6':
            return 'b';
            break;
        case '7':
            return 'T';
            break;
        case '8':
            return 'B';
            break;
        case '9':
            return 'g';
            break;
        case '0':
            return 'O';
            break;
        default:
            return original;
            break;
    }
    return original; // potato
}


// 'Random' Number Generator...
static uint32_t randu( void )
{
    if( rndSeed < 1 ) rndSeed = 1;
    static uint32_t x = 123456789;
    static uint32_t y = 362436069;
    static uint32_t z = 521288629;
    static uint32_t w = 88675123;
    uint32_t t;

    x = rndSeed;

    t = x ^ (x << 11);
    x = y; y = z; z = w;
    rndSeed = w = w ^ (w >> 19) ^ (t ^ (t >> 8));

    return rndSeed;

/*
    if( rndSeed < 1 ) rndSeed = 1;
    rndSeed = ((uint32_t) rndSeed * 65539UL) % 2147483648UL;
    return rndSeed;
*/
}
