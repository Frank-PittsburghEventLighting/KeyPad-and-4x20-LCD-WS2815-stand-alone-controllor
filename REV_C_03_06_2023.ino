String keyP = "";
int KeyFG = 0, x = 0;
char key2, key;
int RBright, BBright, GBright, GreenVal, RedVal, BlueVal;
int convKeyP = 11; int SpeedRate = 250;
int brightnessDownButton, brightnessUpButton, speedUpButton, speedDownButton;
int brightness = 128, brightnessRate, Speed;
#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <FastLED.h>

#define brightnessDownPin 2
#define brightnessUpPin 3
#define speedUpPin 4
#define speedDownPin 5
// LED setup
#define MASTER_BRIGHTNESS 100  // Set the master brigtness value [should be greater then min_brightness value].
#define MASTER_Speed 100       //   Adjusted for +0 Offset

#define MASTER_RED 255
#define MASTER_GREEN 255
#define MASTER_BLUE 255
#define LED_PIN     6
#define NUM_LEDS    64
#define BRIGHTNESS  100
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

//   *********   Start define Pallets   *********
CRGBPalette16 currentPalette;
CRGBPalette32 currentPalette32;
TBlendType    currentBlending;

extern CRGBPalette16 myRedBluePalette;
extern const TProgmemPalette16 myRedBluePalette_p PROGMEM;
extern CRGBPalette16 RWBPalette;
extern const TProgmemPalette16 RWB_p PROGMEM;
extern CRGBPalette16 Irish;
extern const TProgmemPalette16 Irish_p PROGMEM;

extern CRGBPalette32 Ocean;
extern const TProgmemPalette32 Ocean_p PROGMEM;
extern CRGBPalette32 FireFG;
extern const TProgmemPalette32 FireFG_p PROGMEM;

extern CRGBPalette16 myRedGreenXmassPalette;
extern const TProgmemPalette16 myRedGreenXmassPalette_p PROGMEM;


CRGB leds[NUM_LEDS];

// Keyboard setup
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {A0, A1, A2, A3};
byte colPins[COLS] = {A7, A6, A5};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// LCD setup
LiquidCrystal_I2C lcd(0x20,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  pinMode (brightnessDownPin, INPUT_PULLUP);
  pinMode (brightnessUpPin, INPUT_PULLUP);
  pinMode (speedUpPin, INPUT_PULLUP);
  pinMode (speedDownPin, INPUT_PULLUP); delay(10);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  delay(10);
  FastLED.setBrightness(BRIGHTNESS);
//  lcd.begin(20,4);
  lcd.init(); 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.clear();
  welcomeMsg();
  speedAndBrightnessControl();
    
}

void loop() {
      lcd.setCursor(0,0);
      lcd.print((String)"Please enter a   ");
      lcd.setCursor(0,1);
      lcd.print((String)"number from: 1 - 99");
      lcd.setCursor(0,2);
      lcd.print((String)"and then press '#' ");
  while (true) {
    x = 0;
    if ((key) && (key != '#')&& (key != '*')) {
      keyP = keyP + key; lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print((String)"Number Entered: " + keyP + "        ");
    }
    else if (key == '#') {
      convKeyP = keyP.toInt();
      keyP = ""; lcd.clear();
      break;
    }
    else if (key == '*') {
      lcd.clear();
      keyP = "";
      lcd.setCursor(0,0);
      lcd.print((String)"Please enter a   ");
      lcd.setCursor(0,1);
      lcd.print((String)"number from: 1 - 99");
      lcd.setCursor(0,2);
      lcd.print((String)"and then press #");
    }
    key = keypad.getKey();
  }

  while (true) {
    key = keypad.getKey(); // wait for you to input a pattern number,
    LoopFLed();
    speedAndBrightnessControl();
    if ((key) && (key != '#')&& (key != '*')) {
      //////DO NOTHING,
    }
    else if (key == '*') {////////BREAK OUT ONLY WHEN * IS PRESSED
      lcd.clear();
      keyP = "";
       lcd.setCursor(0,0);
      lcd.print((String)"Please enter a   ");
      lcd.setCursor(0,1);
      lcd.print((String)"number from: 1 - 99");
      lcd.setCursor(0,2);
      lcd.print((String)"and then press #");
      break;
    }
  }

}
void LoopFLed() {
  //   Preset Fills

//Keys 1 to 9
  if (  convKeyP == 1)  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
    fill_solid( leds, NUM_LEDS, CRGB::Red);
    displayPatternScene(convKeyP, "Red");
    FastLED.show();
  }
  else if (  convKeyP == 2)  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
    fill_solid( leds, NUM_LEDS, CRGB::Blue);
     key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
    displayPatternScene(convKeyP, "Blue");
     FastLED.show();
  }
  else if (  convKeyP == 3)  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
    fill_solid( leds, NUM_LEDS, CRGB::Orange);
    displayPatternScene(convKeyP, "Orange");
     FastLED.show();
  }
  else if (  convKeyP == 4)  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
    fill_solid( leds, NUM_LEDS, CRGB(0xFFFF20));
    displayPatternScene(convKeyP, "Lemon");
     FastLED.show();
  }
  else if (  convKeyP == 5)  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
    fill_solid( leds, NUM_LEDS, CRGB::Green);
    displayPatternScene(convKeyP, "Green");
     FastLED.show();
  }
  else if (  convKeyP == 6)  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
    fill_solid( leds, NUM_LEDS, CRGB::Cyan);
    displayPatternScene(convKeyP, "Cyan");
     FastLED.show();
  }

  else if (  convKeyP == 7)  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
    displayPatternScene(convKeyP, "Purple");
    fill_solid( leds, NUM_LEDS, CRGB::Purple);
     FastLED.show();
  }
  else if (  convKeyP == 8)  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
    fill_solid( leds, NUM_LEDS, CRGB(0xFF1040));
    displayPatternScene(convKeyP, "Magenta");
     FastLED.show();
  }

  else if (convKeyP == 9) {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
        fill_solid( leds, NUM_LEDS, CRGB::Violet);
        displayPatternChase(convKeyP, "Violet");      
    FastLED.show();
  }

//  Keys 10 to 19
  else if (convKeyP == 10) {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
    fill_solid( leds, NUM_LEDS, CRGB::DarkOrange);
    displayPatternScene(convKeyP, "Dark Orange");
    FastLED.show();
  }
  else if (convKeyP == 11) {
    
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
    fill_solid( leds, NUM_LEDS, CRGB::DeepSkyBlue);
    displayPatternScene(convKeyP, "Sky Blue");
    FastLED.show();
  }

  else if (convKeyP == 12) {
    
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
    fill_solid( leds, NUM_LEDS, CRGB::Pink);
    displayPatternScene(convKeyP, "Pink");
    FastLED.show();
  }
  else if (convKeyP == 13) {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
    fill_solid( leds, NUM_LEDS, CRGB::HotPink);
    displayPatternScene(convKeyP, "Hot Pink");
    FastLED.show();
  }
  else if (convKeyP == 14) {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
    fill_solid( leds, NUM_LEDS, CRGB::Gold);
    displayPatternScene(convKeyP, "Gold");
    FastLED.show();
  }
  else if (convKeyP == 15) {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
    fill_solid( leds, NUM_LEDS, CRGB::SeaGreen);
    displayPatternScene(convKeyP, "Sea Green");
    FastLED.show();
  }
  else if (convKeyP == 16) {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
    fill_solid( leds, NUM_LEDS, CRGB::Tomato);
    displayPatternScene(convKeyP, "Tomato");
    FastLED.show();
  }

  else if (  convKeyP == 17) //displays rgb and allows three (3) potentiometers to set the brightness of each colour
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
    fill_solid( leds, NUM_LEDS, CRGB::Coral);
    displayPatternScene(convKeyP, "Coral");
    FastLED.show();
  }

  else if (  convKeyP == 18) //displays rgb and allows three (3) potentiometers to set the brightness of each colour
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
    fill_solid( leds, NUM_LEDS, CRGB::LimeGreen);
    displayPatternScene(convKeyP, "LimeGreen");
    FastLED.show();
  }

  else if (  convKeyP == 19) //displays rgb and allows three (3) potentiometers to set the brightness of each colour
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
    fill_solid( leds, NUM_LEDS, CRGB::PowderBlue);
    displayPatternScene(convKeyP, "Powder Blue");
    FastLED.show();
  }

//  Keys # 20 to 29
  else if (  convKeyP == 20)
  {  
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
    currentPalette = RWB_p; currentBlending = NOBLEND;
    static uint8_t startIndex = 0;
    FillLEDsFromPaletteColors( startIndex);
     { if( random8() < 120)    //Good Amount of sparkles       
      leds[ random16(NUM_LEDS) ] += CRGB::White;} 
     { if( random8() < 120)
      leds[ random16(NUM_LEDS) ] += CRGB::White;}
   displayPatternScene(convKeyP, "Red White & Blue");
      FastLED.show();
  }
  else if (  convKeyP == 21)
  { 
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
    currentPalette =  RainbowStripeColors_p; currentBlending = NOBLEND;
  static uint8_t startIndex = 0;
  FillLEDsFromPaletteColors( startIndex); 
    displayPatternScene(convKeyP, "Rainbow Stripe");
     FastLED.show();
  }
  else if (  convKeyP == 22)
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
    currentPalette = ForestColors_p; currentBlending = LINEARBLEND;

    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */

    FillLEDsFromPaletteColors( startIndex);
    displayPatternScene(convKeyP, "Forest Colors");
     FastLED.show();
  }
  else if (  convKeyP == 23) //E  Gilter Rainbow
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
    displayPatternScene(convKeyP, "Sparkles White");
    static uint8_t gHue = 0;
    gHue = gHue + 2; /* motion speed */
    // Call the current pattern function once, updating the 'leds' array

    fill_rainbow( leds, NUM_LEDS, gHue, 4); //4 is a good Size(LEDs+=0)
    { if ( random8() < 120)   //Good Amount of sparkles
        key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
      leds[ random16(NUM_LEDS) ] += CRGB::White;
    }
    { if ( random8() < 120)
        key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
      leds[ random16(NUM_LEDS) ] += CRGB::White;
    }
       FastLED.show();
  }
  else if (  convKeyP == 24) //F
    // random colored speckles that blink in and fade smoothly  Popcorn
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
    static uint8_t gHue = 0;
    gHue = gHue + 1; /* motion speed */
    // Call the current pattern function once, updating the 'leds' array

    fadeToBlackBy( leds, NUM_LEDS, 10);  //(good fade #)
    int pos = random8(NUM_LEDS);
    leds[pos] += CHSV( gHue + random8(255), 255, 255);
    int pos2 = random8(NUM_LEDS);
    leds[pos2] += CHSV( gHue + random8(255), 255, 255); // Good 2*Times the dots
    displayPatternScene(convKeyP, "Fade colours");
     FastLED.show();
  }
  else if (  convKeyP == 25) //G
    // a colored dot sweeping back and forth, with fading trails
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
    displayPatternScene(convKeyP, "Sweep back&forth");
    static uint8_t gHue = 0;
    gHue = gHue + 1; /* motion speed */
    // Call the current pattern function once, updating the 'leds' array
    fadeToBlackBy( leds, NUM_LEDS, 20);
    int pos = beatsin16( 6, 0, NUM_LEDS - 1 ); // 6 is Good
    leds[pos] += CHSV( gHue, random8(255), 255);
   FastLED.show();
  }

  else if (  convKeyP == 26) //H
    //  Spew  Tape Ticker   Good Tweaked all parameters!!
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
    displayPatternScene(convKeyP, "Spew tape ticker");
    static uint8_t gHue = 0;
    gHue = gHue - 30; /* motion speed */
    const uint16_t spewSpeed = 200;  // rate of advance
    static boolean spewing = 0;  // pixels are On(1) or Off(0)
    static uint8_t count = 1;  // how many to light (or not light)
    static uint8_t temp = count;
    static uint8_t hue = random8();

    EVERY_N_MILLISECONDS(spewSpeed) {

      if (count == 0) {
        spewing = !spewing;
        if (spewing == 1) {
          count = random8(1, 9);  // random number for On pixels
        }
        else {
          count = random8(2, 4);  // random number for Off pixels
        }
        temp = count;
        hue = random8();
      }
      for (uint8_t i = NUM_LEDS - 1; i > 0; i--) {
        leds[i] = leds[i - 1]; // shift data down the line by one pixel
      }
      if (spewing == 1) {  // new pixels are On
        if (temp == count) {
          leds[0] = CHSV(hue - 5, 215, 255); // for first dot
          leds[1] = CHSV(hue - 5, 215, 255); // for second dot
          leds[2] = CHSV(hue - 5, 215, 255); // for third dot
          leds[3] = CHSV(hue - 5, 215, 255); // for forth dot
          leds[4] = CHSV(hue - 5, 215, 255); // for fifth dot
        } else {
          leds[0] = CHSV(hue, 255, 255 / (1 + ((temp - count) * 2)) ); // for following dots

        }
      } else {  // new pixels are Off
        leds[0] = CHSV(0, 0, 0); // set pixel 0 to black
      }

      count = count - 1;  // reduce count by one.
    }//end every_n

   FastLED.show();
  }
  else if (  convKeyP == 27) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
    fill_solid( leds, NUM_LEDS, CRGB::Red);
    displayPatternScene(convKeyP, "Red");
    FastLED.show();
      }
  else if (  convKeyP == 28) //L
  {
key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
    fill_solid( leds, NUM_LEDS, CRGB::Orange);
    displayPatternScene(convKeyP, "Orange");
     FastLED.show();
  }
  else if (  convKeyP == 29) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
    fill_solid( leds, NUM_LEDS, CRGB::Cyan);
    displayPatternScene(convKeyP, "Cyan");
     FastLED.show();
  }

  chasisToInsert();  //LOCATE THIS FUNCTION TO INPUT DESIRED PATTERN FROM 40-99

}

void FillLEDsFromPaletteColors( uint8_t colorIndex) //  Load 16 Color palette
{
  //     uint8_t brightness = 255;
  //        Loads color palette
  for ( int i = 0; i < NUM_LEDS; i++) {
//            key = keypad.getKey(); speedAndBrightnessControl();
//            if ((key) && (key == '*')) {
//            lcd.clear(); loop();}
    leds[i] = ColorFromPalette( currentPalette, colorIndex, MASTER_BRIGHTNESS, currentBlending);
    colorIndex += 3;
  }
}
void FillLEDsFromPaletteColors32( uint8_t colorIndex)  //  Load 32 Color palette
{
  //     uint8_t brightness = 255;
  //        Loads color palette(?)
  for ( int i = 0; i < NUM_LEDS; i++) {
//            key = keypad.getKey(); speedAndBrightnessControl();
//            if ((key) && (key == '*')) {
//            lcd.clear(); loop();}
    leds[i] = ColorFromPalette( currentPalette32, colorIndex, MASTER_BRIGHTNESS, currentBlending);
    colorIndex += 1;
  }
}

void speedAndBrightnessControl() {
  //  **********  Brightness Control      **********
  brightnessDownButton = digitalRead (brightnessDownPin);
  brightnessUpButton = digitalRead (brightnessUpPin);
  if (brightnessDownButton == LOW) {
    brightness = brightness - 6;
    if (brightness < 0) {
      brightness = 0;
    }
  }
  else if (brightnessUpButton == LOW) {
    brightness = brightness + 6;
    if (brightness >= 255) {
      brightness = 255;
    }
  }
  brightnessRate = map(brightness, 0, 255, 0, 100);
  delay(10);
  FastLED.setBrightness(brightness);  // Set master brightness based on button pressed

  // *********    END Brightness Control ***********

  // *********            SPEED          ***********

  speedUpButton = digitalRead (speedUpPin);
  speedDownButton = digitalRead (speedDownPin);
  if (speedUpButton == LOW) {
    SpeedRate = SpeedRate + 6;
    if (SpeedRate >= 500) {
      SpeedRate = 500;
    }
  }
  else if (speedDownButton == LOW) {
    SpeedRate = SpeedRate - 6;
    if (SpeedRate < 0 ) {
      SpeedRate = 0;
    }
  }
  Speed = map(SpeedRate, 0, 500, 0, 100);
  delay(10);
  FastLED.delay(SpeedRate);
  FastLED.show();   //Goto LoopFLed2  better responce0
  
}
void displayPatternChase(int numb, const char* description)
{
   key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
  lcd.setCursor(0, 0);
  lcd.print((String)"Chase: " + numb + "");
  lcd.setCursor(0, 1);
  lcd.print((String)description);
  lcd.setCursor(0, 2);
  lcd.print((String)"Dimmer"+ " " + brightnessRate + "%");
  lcd.setCursor(0, 3);
  lcd.print((String)"Speed" + " " + Speed + "%");
   key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
}
void displayPatternScene(int numb, const char* description)
{
   key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
  lcd.setCursor(0, 0);
  lcd.print((String)"Scene: " + numb + "");
  lcd.setCursor(0, 1);
  lcd.print((String) description);
  lcd.setCursor(0, 2);
  lcd.print((String)"Dimmer"+ " " + brightnessRate + "%");
  lcd.setCursor(0, 3);
  lcd.print((String)"Speed" + " " + Speed + "%");
   key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
}

void chasisToInsert() {

//  Keys # 30 to 39
  if (  convKeyP == 30) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
      currentPalette = RainbowColors_p; currentBlending = LINEARBLEND;
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
  FastLED.show();
    displayPatternChase(convKeyP,  "Rainbow Color");
    
  }
  else if (  convKeyP == 31) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
       currentPalette = myRedBluePalette_p; currentBlending = NOBLEND;    //Police
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
    displayPatternChase(convKeyP,  "Red and Blue");
       FastLED.show();
  }
  else if (  convKeyP == 32) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
      currentPalette = RainbowColors_p; currentBlending = LINEARBLEND;
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
  FastLED.show();
    displayPatternChase(convKeyP,  "Rainbow Color");
    
  }
  else if (  convKeyP == 33) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
       currentPalette = myRedBluePalette_p; currentBlending = NOBLEND;    //Police
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
    displayPatternChase(convKeyP,  "Red and Blue");
       FastLED.show();
  }
  else if (  convKeyP == 34) //L
  {
   key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
      currentPalette = RainbowColors_p; currentBlending = LINEARBLEND;
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
  FastLED.show();
    displayPatternChase(convKeyP,  "Rainbow Color");
    
  }
  else if (  convKeyP == 35) //L
  {
   key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
       currentPalette = myRedBluePalette_p; currentBlending = NOBLEND;    //Police
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
    displayPatternChase(convKeyP,  "Red and Blue");
       FastLED.show();
  }
  else if (  convKeyP == 36) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
      currentPalette = RainbowColors_p; currentBlending = LINEARBLEND;
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
  FastLED.show();
    displayPatternChase(convKeyP,  "Rainbow Color");
    
  }
  else if (  convKeyP == 37) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
       currentPalette = myRedBluePalette_p; currentBlending = NOBLEND;    //Police
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
    displayPatternChase(convKeyP,  "Red and Blue");
       FastLED.show();
  }
  else if (  convKeyP == 38) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
      currentPalette = RainbowColors_p; currentBlending = LINEARBLEND;
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
  FastLED.show();
    displayPatternChase(convKeyP,  "Rainbow Color");
    
  }
  else if (  convKeyP == 39) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
       currentPalette = myRedBluePalette_p; currentBlending = NOBLEND;    //Police
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
    displayPatternChase(convKeyP,  "Red and Blue");
       FastLED.show();
  }

//  Keys 40 to 49

  else if (  convKeyP == 40) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
      currentPalette = RainbowColors_p; currentBlending = LINEARBLEND;
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
  FastLED.show();
    displayPatternChase(convKeyP,  "Rainbow Color");
  }
  else if (  convKeyP == 41) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
       currentPalette = myRedBluePalette_p; currentBlending = NOBLEND;    //Police
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
    displayPatternChase(convKeyP,  "Red and Blue");
       FastLED.show();
  }
  else if (  convKeyP == 42) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
      currentPalette = RainbowColors_p; currentBlending = LINEARBLEND;
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
  FastLED.show();
    displayPatternChase(convKeyP,  "Rainbow Color");
  }
  else if (  convKeyP == 43) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
       currentPalette = myRedBluePalette_p; currentBlending = NOBLEND;    //Police
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
    displayPatternChase(convKeyP,  "Red and Blue");
       FastLED.show();
  }
  else if (  convKeyP == 44) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
      currentPalette = RainbowColors_p; currentBlending = LINEARBLEND;
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
  FastLED.show();
    displayPatternChase(convKeyP,  "Rainbow Color");
  }
  else if (  convKeyP == 45) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
       currentPalette = myRedBluePalette_p; currentBlending = NOBLEND;    //Police
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
    displayPatternChase(convKeyP,  "Red and Blue");
       FastLED.show();
  }
  else if (  convKeyP == 46) //L
  {key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
      currentPalette = RainbowColors_p; currentBlending = LINEARBLEND;
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
  FastLED.show();
    displayPatternChase(convKeyP,  "Rainbow Color");
  }
  else if (  convKeyP == 47) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
       currentPalette = myRedBluePalette_p; currentBlending = NOBLEND;    //Police
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
    displayPatternChase(convKeyP,  "Red and Blue");
       FastLED.show();
  }
  else if (  convKeyP == 48) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
      currentPalette = RainbowColors_p; currentBlending = LINEARBLEND;
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
  FastLED.show();
    displayPatternChase(convKeyP,  "Rainbow Color");
  }
  else if (  convKeyP == 49) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
       currentPalette = myRedBluePalette_p; currentBlending = NOBLEND;    //Police
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
    displayPatternChase(convKeyP,  "Red and Blue");
       FastLED.show();
  }

//  Keys 50 to 59
  else if (  convKeyP == 50) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
      currentPalette = RainbowColors_p; currentBlending = LINEARBLEND;
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
  FastLED.show();
    displayPatternChase(convKeyP,  "Rainbow Color");
  }
  else if (  convKeyP == 51) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
       currentPalette = myRedBluePalette_p; currentBlending = NOBLEND;    //Police
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
    displayPatternChase(convKeyP,  "Red and Blue");
       FastLED.show();
  }
  else if (  convKeyP == 52) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
      currentPalette = RainbowColors_p; currentBlending = LINEARBLEND;
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
  FastLED.show();
    displayPatternChase(convKeyP,  "Rainbow Color");
  }
  else if (  convKeyP == 53) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
       currentPalette = myRedBluePalette_p; currentBlending = NOBLEND;    //Police
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
    displayPatternChase(convKeyP,  "Red and Blue");
       FastLED.show();
  }
  else if (  convKeyP == 54) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
      currentPalette = RainbowColors_p; currentBlending = LINEARBLEND;
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
  FastLED.show();
    displayPatternChase(convKeyP,  "Rainbow Color");
  }
  else if (  convKeyP == 55) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
       currentPalette = myRedBluePalette_p; currentBlending = NOBLEND;    //Police
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
    displayPatternChase(convKeyP,  "Red and Blue");
       FastLED.show();
  }
  else if (  convKeyP == 56) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
      currentPalette = RainbowColors_p; currentBlending = LINEARBLEND;
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
  FastLED.show();
    displayPatternChase(convKeyP,  "Rainbow Color");
  }
  else if (  convKeyP == 57) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
       currentPalette = myRedBluePalette_p; currentBlending = NOBLEND;    //Police
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
    displayPatternChase(convKeyP,  "Red and Blue");
       FastLED.show();
  }
  else if (  convKeyP == 58) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
      currentPalette = RainbowColors_p; currentBlending = LINEARBLEND;
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
  FastLED.show();
    displayPatternChase(convKeyP,  "Rainbow Color");
  }
  else if (  convKeyP == 59) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
       currentPalette = myRedBluePalette_p; currentBlending = NOBLEND;    //Police
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
    displayPatternChase(convKeyP,  "Red and Blue");
       FastLED.show();
  }

//  Keys 60 to 69
  else if (  convKeyP == 60) //L
  {
    key = keypad.getKey(); speedAndBrightnessControl();
      if ((key) && (key == '*')) {
        lcd.clear(); loop();
      }
      currentPalette = RainbowColors_p; currentBlending = LINEARBLEND;
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
  FastLED.show();
    displayPatternChase(convKeyP,  "Rainbow Color");
  }
//  else if (  convKeyP == 61) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 62) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 63) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 64) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 65) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 66) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 67) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 68) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 69) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 70) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 71) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 72) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 73) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 74) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 75) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 76) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 77) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 78) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 79) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 80) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 81) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 82) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 83) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 84) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 85) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 86) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 87) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 88) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 89) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 90) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 91) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 92) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 93) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 94) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 95) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 96) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 97) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 98) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
//  else if (  convKeyP == 99) //L
//  {
//    key = keypad.getKey(); speedAndBrightnessControl();
//      if ((key) && (key == '*')) {
//        lcd.clear(); loop();
//      }
//    //////////////****PASS THE CHASE STYLE AND PATTERN HERE******//////////////
//    displayPatternChase(convKeyP,  "description");
//  }
}
void welcomeMsg(){
  lcd.print("      WELCOME     "); delay(500);
  lcd.setCursor(0, 0);
  lcd.print("  FAST LED DISPLAY  ");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("      Designed      ");
  delay(100);
  lcd.setCursor(0, 2);
  lcd.print("         And        "); delay(100);
   lcd.setCursor(0, 3); 
  lcd.print("   Engineered by:   "); delay(500);
   lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("     PITTSBURGH     "); delay(500);
  lcd.setCursor(0, 2);
  lcd.print("        EVENT       "); delay(500);
  lcd.setCursor(0, 3);
  lcd.print("       LIGHTING     "); delay(550);
  Wire.begin(); // Initialize I2C communication
  delay(100);
  lcd.clear();
}


//  *****          Extrenal Paletts    ********
//  *****          Palette   16   *****
const TProgmemRGBPalette16 myRedBluePalette_p PROGMEM =
{
  CRGB::Red,
  CRGB::Blue,
  CRGB::Red,
  CRGB::Blue,

  CRGB::Red,
  CRGB::Blue,
  CRGB::Red,
  CRGB::Blue,

  CRGB::Red,
  CRGB::Blue,
  CRGB::Red,
  CRGB::Blue,

  CRGB::Red,
  CRGB::Blue,
  CRGB::Red,
  CRGB::Blue,
};

//  *****          Palette   16   *****
const TProgmemRGBPalette16 RWB_p  PROGMEM =
{
  CRGB::Blue,
  CRGB::Red, 
  CRGB::White,
  CRGB::Blue,

  CRGB::Red,
  CRGB::White,
  CRGB::Blue,
  CRGB::Red,

  CRGB::White,
  CRGB::Blue,
  CRGB::Red,
  CRGB::White,

  CRGB::Red,
  CRGB::Red,
  CRGB::White,
  CRGB::Blue,
};

//  *****          Palette   16   *****
const TProgmemRGBPalette16 Irish_p PROGMEM =
{
  CRGB::Green,
  CRGB::Green,
  CRGB::DarkOrange,
  CRGB::Green,

  CRGB::Green,
  CRGB::Green,
  CRGB::DarkOrange,
  CRGB::Green,

  CRGB::Green,
  CRGB::Green,
  CRGB::DarkOrange,
  CRGB::Green,

  CRGB::Green,
  CRGB::Green,
  CRGB::DarkOrange,
  CRGB::Green,
};

//  *****          Palette   32   *****
const TProgmemRGBPalette32 FireFG_p FL_PROGMEM =
{
 0xB22222, //FireBrick
 CRGB::Maroon,
 CRGB::Crimson,
 CRGB::OrangeRed,

 CRGB::DarkRed,
 0xFF0040, //  Carmine
 CRGB::DarkRed,
 CRGB::DarkOrange,

 CRGB::Tomato,
 CRGB::DarkRed,
 CRGB::Red,
 CRGB::Orange,

 CRGB::White,
 CRGB::Yellow,
 CRGB::Gold,
 CRGB::DarkRed,

 CRGB::OrangeRed,
 0xFF0040, //  Carmine
 CRGB::Black,
 CRGB::Red,

 CRGB::DarkRed,
 CRGB::Gold,
 0xB22222, //FireBrick
 CRGB::Red,

 CRGB::DarkRed,
 CRGB::DarkOrange,
 CRGB::OrangeRed,
 CRGB::Orange,

 CRGB::White,
 CRGB::Orange,
 CRGB::Red,
 CRGB::DarkRed,
};

//  *****          Palette   32   *****
const TProgmemRGBPalette32 Ocean_p PROGMEM =
{
  CRGB::MidnightBlue,
  CRGB::DarkBlue,
  CRGB::Teal,
  CRGB::Navy,

  CRGB::DarkBlue,
  CRGB::Blue,
  CRGB::SeaGreen,
  CRGB::DarkGreen,

  CRGB::CadetBlue,
  CRGB::Blue,
  CRGB::DarkCyan,
  CRGB::OliveDrab,

  CRGB::MediumSeaGreen,
  CRGB::Aqua, 
  CRGB::SeaGreen,
  CRGB::DarkSeaGreen,

  CRGB::LimeGreen,
  CRGB::DarkTurquoise,
  CRGB::Aqua,
  CRGB::Blue,

  CRGB::DarkBlue,
  CRGB::MediumBlue,
  CRGB::SeaGreen,
  CRGB::Teal,

  CRGB::CadetBlue,
  CRGB::Blue,
  CRGB::DarkCyan,
  CRGB::DarkSlateBlue,

  CRGB::Violet,
  CRGB::MediumPurple,
  CRGB::Indigo,
  CRGB::Purple,
};


const TProgmemPalette16 myRedGreenXmassPalette_p PROGMEM =
{
CRGB::Red,
CRGB::Green,
CRGB::Red,

CRGB::Green,
CRGB::Red,
CRGB::Green,
CRGB::Red,

CRGB::Red,
CRGB::Green,
CRGB::Red,
CRGB::Green,
CRGB::Red,
CRGB::Green,
CRGB::Red,
CRGB::Green,
};
