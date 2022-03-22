
//Define for oled siaply

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. `
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000
};


int recived_state = -1;
int current_state = -1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
  delay(500);
  digitalWrite(8, HIGH);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  //display.drawPixel(10, 10, SSD1306_WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  //display.display();

  //delay(2000);
  testdrawstyles(-1);    // Draw 'stylized' characters
  testscrolltext(-1);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(8, HIGH);
  while (Serial.available() > 0)
  {
    recived_state = Serial.read();
    Serial.println(recived_state);
    if (recived_state != current_state)
    {
      current_state = recived_state;
      digitalWrite(8, LOW);
      delay(1000);
      digitalWrite(8, HIGH);
      delay(1000);
      digitalWrite(8, LOW);
      delay(1000);
      digitalWrite(8, HIGH);
      switch (current_state)
      {
        case 1:
          Serial.println("User Moving toward right");
                    testdrawstyles(1);
          testscrolltext(1);
          break;
        case 2:
          Serial.println("USerMoving towwards left");
                    testdrawstyles(2);
          testscrolltext(2);
          break;
        case 3:
          Serial.println("USerMoving towwards up");
          testdrawstyles(3);
          testscrolltext(3);
          break;
        case 4:
          Serial.println("USerMoving towwards down");
          testdrawstyles(4);
          testscrolltext(4);
          break;
      }
    }
  }
}



void testdrawstyles(int num) {
  display.clearDisplay();

  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0, 0);            // Start at top-left corner
  if (num == 1)
  {
    //Right
    display.println(F("Need water"));
  }
  else if (num == 2)
  {
    //LEFT
    display.println(F("Need Food"));
  }
  else if (num == 3)
  {
    //UP
    display.println(F("Need to use Washroom"));
  }
  else if (num == 4)
  {
    //Down
    
    display.println(F("Some Emergency"));
  }
  else
  {
    display.println(F("Welcome to System"));
  }
  display.display();
  delay(2000);
}

void testscrolltext(int num) {
  display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  //  display.println(F("scroll"));
  if (num == 1)
  {
    //Right
    display.println(F("Water"));
  }
  else if (num == 2)
  {
    //LEft
    display.println(F("Food"));
  }
  else if (num == 3)
  {
    //Up
    display.println(F("Washroom"));
  }
  else if (num == 4)
  {
    display.println(F("Emergency"));
  }
  else
  {
    display.println(F("Tracking.."));
  }

  display.display();      // Show initial text
  delay(100);

  // Scroll in various directions, pausing in-between:
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
  delay(1000);
}
