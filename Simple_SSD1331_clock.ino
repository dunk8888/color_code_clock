/*************************************************** 
  This is a example sketch demonstrating the graphics
  capabilities of the SSD1331 library  for the 0.96" 
  16-bit Color OLED with SSD1331 driver chip

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/684

  These displays use SPI to communicate, 4 or 5 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "Wire.h"
#define PCF2129address 0xA2>>1
  unsigned int old_sec,old_min,old_hour;
  unsigned int old_sec1,old_sec2,sec1,sec2;
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
String days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

byte bcdToDec(byte value)
{
  return ((value / 16) * 10 + value % 16);
}

byte decToBcd(byte value){
  return (value / 10 * 16 + value % 10);
}

///////OLED display////
// You can use any (4 or) 5 pins 
#define sclk 13
#define mosi 11
#define cs   10
#define rst  9
#define dc   8


// Color definitions
/* some RGB color definitions                                                 */
#define BLACK           0x0000      /*   0,   0,   0 */
#define WHITE           0xFFFF      /* 255, 255, 255 */

#define c0           0x0000      /*   0,   0,   0 */
#define NAVY            0x000F      /*   0,   0, 128 */
#define DARKGREEN       0x03E0      /*   0, 128,   0 */
#define DARKCYAN        0x03EF      /*   0, 128, 128 */
#define c1          0x7800      /* 128,   0,   0 */
#define c7          0x780F      /* 128,   0, 128 */
#define OLIVE           0x7BE0      /* 128, 128,   0 */
#define LIGHTGREY       0xC618      /* 192, 192, 192 */
#define c8        0x7BEF      /* 128, 128, 128 */
#define c6            0x001F      /*   0,   0, 255 */
#define c5           0x07E0      /*   0, 255,   0 */
#define CYAN            0x07FF      /*   0, 255, 255 */
#define c2             0xF800      /* 255,   0,   0 */
#define MAGENTA         0xF81F      /* 255,   0, 255 */
#define c4          0xFFE0      /* 255, 255,   0 */
#define c9           0xFFFF      /* 255, 255, 255 */
#define c3          0xFD20      /* 255, 165,   0 */
#define GREENYELLOW     0xAFE5      /* 173, 255,  47 */
#define PINK                        0xF81F


#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>

// Option 1: use any pins but a little slower
//Adafruit_SSD1331 display = Adafruit_SSD1331(cs, dc, mosi, sclk, rst);  

// Option 2: must use the hardware SPI pins 
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be 
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
Adafruit_SSD1331 display = Adafruit_SSD1331(cs, dc, rst);

void setup(void) {

  display.begin();
  display.fillScreen(WHITE);

///// time setting////
  // change the following to set your initial time
  second = 0;
  minute = 29;
  hour = 15;
  dayOfWeek = 6;
  dayOfMonth = 24;
  month = 10;
  year = 15;
  // comment out the next line and upload again to set and keep the time from resetting every reset
  //setPCF2129();
//display.fillRect(0,20,16,64,c7);


  
}

void loop() {

    readPCF2129();
 
    if(old_min!=minute){
    display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(36,3);
   if(old_min<10){
    display.print(" ");
  }  
  display.print(old_min);
  display.setTextColor(BLACK);
  display.setCursor(36,3);
   if(minute<10){
    display.print(" ");
  }    
  display.print(minute);
    tilecolor(32,minute);
    old_min=minute;  
  }

    if(old_hour!=hour){
    display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(5,3); 
       if(old_hour<10){
    display.print(" ");
  }   
  display.print(old_hour);
  display.setTextColor(BLACK);
  display.setCursor(5,3);
     if(hour<10){
    display.print(" ");
  }    
  display.print(hour);
    old_hour=hour;  
        tilecolor(0,hour);
  }

  if(old_sec!=second){
    sec2=second/10;
    sec1=second-sec2*10;
    old_sec2=old_sec/10;
    old_sec1=old_sec-old_sec2*10;
    if(old_sec2 != sec2){
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(67,3);
  if(old_sec<10){
    display.print(" ");
  }
  display.print(old_sec);
  display.setTextColor(BLACK);
  display.setCursor(67,3);
    if(second<10){
    display.print(" ");
  }
  display.print(second);
  tilecolor(64,second);
    old_sec=second;
    }else{
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(79,3);
  display.print(old_sec1);
  display.setTextColor(BLACK);
  display.setCursor(79,3);
  display.print(sec1);
  tilecolor(80,sec1*10);
    }
    old_sec=second;
    }
    


      
}



void tilecolor(int xpos,int num){
//  two digit number are passed from main program
unsigned int num1, num2;
  num2=num/10;
  num1=num-num2*10;
    switch(num2){
    case 1:
    display.fillRect(xpos,20,xpos+16,64,c1);
    break;
    case 2:
    display.fillRect(xpos,20,xpos+16,64,c2);
    break;
    case 3:
    display.fillRect(xpos,20,xpos+16,64,c3);
    break;
    case 4:
    display.fillRect(xpos,20,xpos+16,64,c4);
    break;
    case 5:
    display.fillRect(xpos,20,xpos+16,64,c5);
    break;
    case 6:
    display.fillRect(xpos,20,xpos+16,64,c6);
    break;
    case 7:
    display.fillRect(xpos,20,xpos+16,64,c7);
    break; 
    case 8:
    display.fillRect(xpos,20,xpos+16,64,c8);
    break;    
    case 9:
    display.fillRect(xpos,20,xpos+16,64,c9);
    break;
    case 0:
    display.fillRect(xpos,20,xpos+16,64,c0);
    break; 
    default:;               
  }
  switch(num1){
    case 1:
    display.fillRect(xpos+16,20,xpos+32,64,c1);
    break;
    case 2:
    display.fillRect(xpos+16,20,xpos+32,64,c2);
    break;
    case 3:
    display.fillRect(xpos+16,20,xpos+32,64,c3);
    break;
    case 4:
    display.fillRect(xpos+16,20,xpos+32,64,c4);
    break;
    case 5:
    display.fillRect(xpos+16,20,xpos+32,64,c5);
    break;
    case 6:
    display.fillRect(xpos+16,20,xpos+32,64,c6);
    break;
    case 7:
    display.fillRect(xpos+16,20,xpos+32,64,c7);
    break; 
    case 8:
    display.fillRect(xpos+16,20,xpos+32,64,c8);
    break;    
    case 9:
    display.fillRect(xpos+16,20,xpos+32,64,c9);
    break;
    case 0:
    display.fillRect(xpos+16,20,xpos+32,64,c0);
    break; 
    default:;               
  }

  
}

void singletilecolor(int xpos,int num){
//  one digit number are passed from main program
unsigned int num1, num2;
  num2=num/10;
  num1=num-num2*10;
    switch(num2){
    case 1:
    display.fillRect(xpos,20,xpos+16,64,c1);
    break;
    case 2:
    display.fillRect(xpos,20,xpos+16,64,c2);
    break;
    case 3:
    display.fillRect(xpos,20,xpos+16,64,c3);
    break;
    case 4:
    display.fillRect(xpos,20,xpos+16,64,c4);
    break;
    case 5:
    display.fillRect(xpos,20,xpos+16,64,c5);
    break;
    case 6:
    display.fillRect(xpos,20,xpos+16,64,c6);
    break;
    case 7:
    display.fillRect(xpos,20,xpos+16,64,c7);
    break; 
    case 8:
    display.fillRect(xpos,20,xpos+16,64,c8);
    break;    
    case 9:
    display.fillRect(xpos,20,xpos+16,64,c9);
    break;
    case 0:
    display.fillRect(xpos,20,xpos+16,64,c0);
    break; 
    default:;               
  }
  switch(num1){
    case 1:
    display.fillRect(xpos+16,20,xpos+32,64,c1);
    break;
    case 2:
    display.fillRect(xpos+16,20,xpos+32,64,c2);
    break;
    case 3:
    display.fillRect(xpos+16,20,xpos+32,64,c3);
    break;
    case 4:
    display.fillRect(xpos+16,20,xpos+32,64,c4);
    break;
    case 5:
    display.fillRect(xpos+16,20,xpos+32,64,c5);
    break;
    case 6:
    display.fillRect(xpos+16,20,xpos+32,64,c6);
    break;
    case 7:
    display.fillRect(xpos+16,20,xpos+32,64,c7);
    break; 
    case 8:
    display.fillRect(xpos+16,20,xpos+32,64,c8);
    break;    
    case 9:
    display.fillRect(xpos+16,20,xpos+32,64,c9);
    break;
    case 0:
    display.fillRect(xpos+16,20,xpos+32,64,c0);
    break; 
    default:;               
  }

  
}




void setPCF2129()
// this sets the time and date to the PCF2129
{
  Wire.beginTransmission(PCF2129address);
  Wire.write(0x03);
  Wire.write(decToBcd(second));  
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));     
  Wire.write(decToBcd(dayOfMonth));
  Wire.write(decToBcd(dayOfWeek));  
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.endTransmission();
}

void readPCF2129()
// this gets the time and date from the PCF2129
{
  Wire.beginTransmission(PCF2129address);
  Wire.write(0x03);
  Wire.endTransmission();
  Wire.requestFrom(PCF2129address, 7);
  second     = bcdToDec(Wire.read() & B01111111); // remove VL error bit
  minute     = bcdToDec(Wire.read() & B01111111); // remove unwanted bits from MSB
  hour       = bcdToDec(Wire.read() & B00111111); 
  dayOfMonth = bcdToDec(Wire.read() & B00111111);
  dayOfWeek  = bcdToDec(Wire.read() & B00000111);  
  month      = bcdToDec(Wire.read() & B00011111);  // remove century bit, 1999 is over
  year       = bcdToDec(Wire.read());
}


