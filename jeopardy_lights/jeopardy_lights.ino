#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_Circuit_Playground.h>

// Remote Codes
#define ADAF_MINI_VOLUME_DOWN  0xfd00ff
#define ADAF_MINI_PLAY_PAUSE  0xfd807f
#define ADAF_MINI_VOLUME_UP 0xfd40bf
#define ADAF_MINI_SETUP 0xfd20df
#define ADAF_MINI_UP_ARROW  0xfda05f
#define ADAF_MINI_STOP_MODE 0xfd609f
#define ADAF_MINI_LEFT_ARROW  0xfd10ef
#define ADAF_MINI_ENTER_SAVE  0xfd906f
#define ADAF_MINI_RIGHT_ARROW 0xfd50af
#define ADAF_MINI_0_10_PLUS 0xfd30cf
#define ADAF_MINI_DOWN_ARROW  0xfdb04f
#define ADAF_MINI_REPEAT  0xfd708f
#define ADAF_MINI_1 0xfd08f7
#define ADAF_MINI_2 0xfd8877
#define ADAF_MINI_3 0xfd48b7
#define ADAF_MINI_4 0xfd28d7
#define ADAF_MINI_5 0xfda857
#define ADAF_MINI_6 0xfd6897
#define ADAF_MINI_7 0xfd18e7
#define ADAF_MINI_8 0xfd9867
#define ADAF_MINI_9 0xfd58a7
// Remote Codes End

// Define the possible game states.
enum gameState
{
  initState = 0,
  waitState,
  askingQuestionState,
  buzzerState
};

// Variable that will hold the global current state of the game.
gameState currentState = initState;

//***************************************//
// Initialization.
//***************************************//


void setup() 
{
  // put your setup code here, to run once:
  CircuitPlayground.begin();
  CircuitPlayground.irReceiver.enableIRIn();
  Serial.begin(9600);
  readyForClicks();
}
//***************************************//


//***************************************//
// Main Loop
//***************************************//

void loop() 
{

  if( CircuitPlayground.rightButton() )
  {
    readyForClicks();
  }
  
  if( checkIrReceived() )
  {
    // Check which team pushed the button.
    switch( CircuitPlayground.irDecoder.value )
    {
      case ADAF_MINI_1:
        setAllLEDs(255,0,0);
      break;
      case ADAF_MINI_2:
        setAllLEDs(0,255,0);
      break;
      case ADAF_MINI_3:
        setAllLEDs(0,0,255);
      break;
      case ADAF_MINI_4:
        setAllLEDs(127,0,127);
      break;
    }
    delay(30000);
    CircuitPlayground.irReceiver.enableIRIn();
    setAllLEDs(255,255,255);
  }


}


//***************************************//

void setAllLEDs(int r, int g, int b)
{
  // Loop through all lights and set them to the same color.
  for( int i = 0; i < 10; ++i )
  {
    CircuitPlayground.setPixelColor(i, r, g, b);
  }
}

//*************************************/
// Goes through the logic to decode and 
// recieve IR signals. Ripped this off
// the CircuitPlayground sensor examples.
bool checkIrReceived()
{
    // Did we get any infrared signals?
  if (! CircuitPlayground.irReceiver.getResults()) 
  {
    return(false);
  }

  // Did we get any decodable messages?
  if (! CircuitPlayground.irDecoder.decode()) 
  {
    CircuitPlayground.irReceiver.enableIRIn(); // Restart receiver  
    return(false);
  }

  // We can print out the message if we want...
  CircuitPlayground.irDecoder.dumpResults(false);

  // Did we get any NEC remote messages?
  if (! CircuitPlayground.irDecoder.protocolNum == NEC) 
  {
    CircuitPlayground.irReceiver.enableIRIn(); // Restart receiver  
    return(false);
  }

  return(true);
  
}

void readyForClicks()
{
   // Loop through all lights and set them to the same color.
  for( int i = 0; i < 10; i += 2 )
  {
    CircuitPlayground.setPixelColor(i, 0, 255, 0 );
  }

   // Loop through all lights and set them to the same color.
  for( int i = 1; i < 10; i +=2 )
  {
    CircuitPlayground.setPixelColor(i, 255, 255, 255);
  }
}

//*************************************/
