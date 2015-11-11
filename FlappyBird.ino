#include "U8glib.h"
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NO_ACK);	// Display which does not send ACK

int randomNumber;
int invert;
int flappyuppin = 15;
int up = 0;
int Shift = 0;
int Score = 0;
int bottomLimit = 27;
int vibratePin = 4;


#define Bird_width 15
#define  Bird_height 11


#define Cloud_width 30
#define Cloud_height 20

//static unsigned char u8g_logo_bits[] = {
static unsigned char Bird_bits[] U8G_PROGMEM = {
  0xe0, 0x03, 0x00, 0x01, 0x8c, 0x08, 0x9e, 0x14, 0x01, 0x11, 0x21, 0x3e,
  0x20, 0x41, 0x8c, 0x3e, 0x04, 0x21, 0x08, 0x1e, 0xf0, 0x01
};

static unsigned char Cloud_bits[] U8G_PROGMEM = {
  0x00, 0x00, 0x0f, 0x00, 0x00, 0xc0, 0x7f, 0x00, 0x00, 0xe0, 0xff, 0x00,
  0x00, 0xf0, 0xff, 0x01, 0x00, 0xf8, 0xff, 0x01, 0x00, 0xfd, 0xff, 0x03,
  0xc0, 0xff, 0xff, 0x03, 0xe0, 0xff, 0xff, 0x07, 0xf0, 0xff, 0xff, 0x0f,
  0xf0, 0xff, 0xff, 0x1f, 0xfc, 0xff, 0xff, 0x1f, 0xfe, 0xff, 0xff, 0x3f,
  0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0x1f,
  0xfe, 0xff, 0xff, 0x1f, 0xfc, 0xff, 0xff, 0x0f, 0xe0, 0xff, 0x3f, 0x00,
  0xc0, 0xbf, 0x1f, 0x00, 0x00, 0x0f, 0x00, 0x00
};




void draw(uint8_t a)
{
  // graphic commands to redraw the complete screen should be placed here
  u8g.drawXBMP( 20, 25 + a,  Bird_width,  Bird_height, Bird_bits);

  u8g.drawXBMP( 50, 0, Cloud_width, Cloud_height, Cloud_bits);

  u8g.drawXBMP( 90, 0, Cloud_width, Cloud_height, Cloud_bits);
}

void HardwareSetup()
{

  pinMode(flappyuppin, INPUT_PULLUP);
  digitalWrite(flappyuppin, HIGH);
  
  pinMode(vibratePin, OUTPUT);
  digitalWrite(vibratePin, LOW);
  
  randomSeed(analogRead(4));

}




void movement()
{
  if (digitalRead(flappyuppin) == LOW)
  {
    up = up - 12;
  } else if ( up < 20)
    up = up + 10;
  else
  {
    up = bottomLimit;
  }

}


void Structure(uint8_t a)
{
  //X,Y,Thickness,Length
  if (Shift > 128  )
  {
    randomNumber = random(30);
    invert = random(-20, 20);
    Shift = 0;

    if (up != bottomLimit)
      Score++;

  }
  u8g.drawBox(127 - a + invert, 70 - randomNumber, 17, 4);
  u8g.drawBox(127 - a - invert, randomNumber - 10, 17, 4);

  //Down
  u8g.drawFrame(128 - a + invert, 70 - randomNumber, 15, 30 + randomNumber);

  //up
  u8g.drawFrame(128 - a - invert, -10, 15, randomNumber);

  //Base
  u8g.drawBox(0, 63, 128, 2);

}

void GameStatus()
{
  u8g.setFont(u8g_font_helvR08);

  if (up == bottomLimit  )
  {
    u8g.setPrintPos(32, 34);
    u8g.print("Game Over");
    Shift = -30;
    Score = 0;

  }

  u8g.setPrintPos(0, 10);
  u8g.print(Score);

}

void Colision()
{
  if ((up > 32 - randomNumber || 20 + up < randomNumber - 10) && (Shift > 128 - randomNumber - invert || Shift > 128 - randomNumber + invert ) )
  {
    digitalWrite(vibratePin, HIGH);
    Score = 0;
  }
  else
    digitalWrite(vibratePin, LOW);
}


void FlappyBird()
{
  u8g.firstPage();
  do {
    draw(up);
    Structure(Shift);
    GameStatus();

  } while ( u8g.nextPage() );

  movement();
  Shift = Shift + 10;
  Colision();
}

void setup(void)
{
  HardwareSetup();
}

void loop(void)
{
  FlappyBird();
}
