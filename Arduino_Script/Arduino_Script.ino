#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define BUTTON_PIN 4
int buttonPin = 4;
int initial = 0;
int oldstate = 0;
int buttonstate = 0;

int displaystate = 99;
int displaychange = 0;
int curdisplaypage = 0;

int offset = 20;// set the correction offset value


/* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other*/
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
//#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000
};


void setup()   {

  Serial.begin(9600);
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.

  delay(250); // wait for the OLED to power up
  display.begin(i2c_Address, true); // Address 0x3C default
 //display.setContrast (0); // dim display
 
  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();





  // text display tests
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.println("Loading..");
  display.display();
  //display.setTextColor(SH110X_BLACK, SH110X_WHITE); // 'inverted' text
  //display.println(3.141592);
  //display.setTextSize(2);
  //display.setTextColor(SH110X_WHITE);
  //display.print("0x"); display.println(0xDEADBEEF, HEX);

  delay(1000);
  display.clearDisplay();
  display.display();


}


void loop() {

  buttonstate = digitalRead(buttonPin);
  if (buttonstate == HIGH)
  {
      delay (50);
      buttonstate = digitalRead(buttonPin);
      if (buttonstate == LOW)
      initial = oldstate + 1;
    }
  else
  {
    delay(100);
    displaystate = 99;
  }


  switch (initial)
  {
    case 0:
    show_info(0);
      displaystate = 0;
    oldstate = initial;
    break;
    case 1:
      displaystate = 1;
    show_info(1);
    oldstate = initial;
    break;
    case 2:
      displaystate = 2;
    show_info(2);
    oldstate = initial;
    break;
    case 3:
      displaystate = 3;
    show_info(3);
    oldstate = initial;
    break;
    case 4:
    show_info(4);
      displaystate = 4;
    oldstate = initial;
    break;
    default:
      displaystate = 0;
    show_info(0);
    oldstate = 0;
    break;
  }  

  //Serial.println(displaystate);
  Serial.println(curdisplaypage);
  //Serial.println(initial);
}

void show_info(int displayPage) {
  //if (displaystate != curdisplaypage)
  //{
    if (displayPage == 0)
    {
      display.clearDisplay();
      //display.setTextColor(SH110X_WHITE);
      display.setTextSize(4);
      display.setCursor(0, 0);
      display.println("20:48");
      display.display();

    curdisplaypage = 0;
    }
    else if (displayPage == 1)
    {
      //displaystate = 0;
      int volt = analogRead(A0);// read the input
      double voltage = map(volt, 0, 1023, 0, 2500) ; // map 0-1023 to 0-2500 and add correction offset

      voltage /= 100; // divide by 100 to get the decimal values

      display.setCursor(0, 10);
      display.setTextSize(3);
      display.clearDisplay();
      display.print("Batt. ");
      display.setTextSize(2);
      display.setCursor(0, 35);
      display.print(voltage);
      display.print(" ");
      display.setTextSize(2);
      display.setCursor(60, 35);
      display.print("V");
      display.display();

      //delay(20);

      curdisplaypage = 1;
    }
    else if (displayPage == 2)
    {
      display.clearDisplay();
      //display.setTextColor(SH110X_WHITE);
      display.setTextSize(2);
      display.setCursor(0, 0);
      display.println("Oel");
      display.setTextSize(3);
      display.println("0");
      display.display();

      curdisplaypage = 2;
    }
    else if (displayPage == 3)
    {
      display.clearDisplay();
      //display.setTextColor(SH110X_WHITE);
      display.setTextSize(2);
      display.setCursor(0, 0);
      display.println("Kuehler");
      display.setTextSize(3);
      display.println("0");
      display.display();

      curdisplaypage = 3;
    }    
    else if (displayPage == 4)
    {
      display.clearDisplay();
      //display.setTextColor(SH110X_WHITE);
      display.setTextSize(2);
      display.setCursor(0, 0);
      display.println("Temp");
      display.setTextSize(3);
      display.println("0");
      display.display();

      curdisplaypage = 4;
    }   
  //}
  //else
  //{
    //nothing Todo
  //}
}
