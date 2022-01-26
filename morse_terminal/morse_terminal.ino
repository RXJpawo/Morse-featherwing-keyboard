// Based on terminal_mc which is my terminal for Z80 memory card computer

// Ideas for future development
// Save to SD
// Load from SD
// File browser
// Change macros

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <BBQ10Keyboard.h>
#include <strings.h>
#include <Morse.h>
#include "config.h"
#include <Adafruit_NeoPixel.h>

// ------------------ Variables ------------------
unsigned char         row = 0;
unsigned char         chr = 0;
uint16_t              scr_width; 
uint16_t              scr_height;
uint16_t              status_border;
uint16_t              menu_border;
char                  scr_buf[ROWS][CHARS + 1];
unsigned long         timeval;
int                   cw_spd = CW_SPEED;

// ------------------ Objects -------------------
Adafruit_ILI9341    tft(TFT_CS, TFT_DC);
BBQ10Keyboard       keyboard;
Morse               morse(CW_PIN, cw_spd, 0); // Pin 13, 12 WPM, Key output
Adafruit_NeoPixel   pixels(1, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);


void setup()
{
  Serial.begin(115200);

  // Display init
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextSize(SCALE);
  tft.setTextWrap(0);
  scr_width = tft.width(); 
  scr_height =  tft.height();

  // Calculate the header and footer
  status_border = HEIGHT + 2 + (1 * SCALE);
  menu_border = scr_height - HEIGHT - (1 * SCALE) - 2;

  // LED init
  pixels.begin();
  pixels.setBrightness(30);

  // Keyboard init
  keyboard.begin();
  keyboard.setBacklight(0.5f);

  // Draw initial header and footer
  tft.setCursor(0, HEAD);
  status_line();
  soft_menu();
}

void loop()
{
  char inkey = read_key();
  if (inkey > 0)
  {
    // Is it a non sendable character?
    control_characters(inkey);
    
    // Convert to upper case and send if it's a sendable character
    inkey = toupper(inkey);
    if (inkey >= 32)
    {
      send_char(inkey);
    }
  }
}

void send_char(char char_to_send)
{
      pixels.setPixelColor(0, pixels.Color(255, 0, 255));
      pixels.show(); 
      draw_char(char_to_send);
      pixels.clear();
      pixels.show();
      morse.send(char_to_send);
  
}


void control_characters(char ctrl_char)
{
  // Change 'Enter' to '=' which makes sense in CW
  if (ctrl_char == '\n')
  {
    send_char('=');
  }

  // Joy left, decrease speed
  else if (ctrl_char == 3)
  {
    cw_spd--;
    Morse morse(CW_PIN, cw_spd, 0);
    status_line();
  }

  // Joy right, increase speed
  else if (ctrl_char == 4)
  {
    cw_spd++;
    Morse morse(CW_PIN, cw_spd, 0);
    status_line();
  }

  // Button 1 (Macro)
  else if (ctrl_char == 6)
  {
    char msg[] = "CQ CQ CQ DE SM0RVV SM0RVV K";
    for (char c=0; c < (sizeof(msg)-1); c++)
    {
      send_char(msg[c]); 
    }
  }

  // Button 2 (Macro)
  else if (ctrl_char == 17)
  {
    char msg[] = "UR RST 599 5NN";
    for (char c=0; c < (sizeof(msg)-1); c++)
    {
      send_char(msg[c]); 
    }
  }
  
  // Button 3 (Macro)
  else if (ctrl_char == 7)
  {
    char msg[] = "NAME IS ERIK ERIK ES QTH JARFALLA JARFALLA";
    for (char c=0; c < (sizeof(msg)-1); c++)
    {
      send_char(msg[c]); 
    }
  }
  
  // Button 4 (Macro)
  else if (ctrl_char == 18)
  {
    char msg[] = "TU FER QSO 73 73 DE SM0RVV SK E E";
    for (char c=0; c < (sizeof(msg)-1); c++)
    {
      send_char(msg[c]); 
    }
  }
  
  // Backspace, which is correction in CW = ii
  else if (ctrl_char == 8)
  {
    // Just send it, don't display anything
    morse.sendmsg("II");
  }

  // Microphone button
  else if (ctrl_char == 126)
  {
    // Do nothing
    // Maybe use this later for tuning on/off
  }
}
