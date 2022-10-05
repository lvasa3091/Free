#ifndef LCDBOARD_H
#define LCDBOARD_H

#pragma once

#include "lcd_ili9341.h"
#include "fonts.h"
#include <ctime>
#include <dirent.h>
#include <iterator>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <syslog.h>
#include <unistd.h>
#include <vector>
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <inttypes.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

using namespace std;

class Lcdboard {
private:
DisplayILI9341_240x320x16_SPI *display; //(73,{1, 0, 70, 0,-1,-1});

uint8_t canvasData[30000];
NanoCanvas16 *canvas; //(221, 41, canvasData);

time_t t;
tm* now;

char path_temp[64];
FILE *TEMPFile;
float temp;

int ADS_address = 0x48;       // Address of our device on the I2C bus
int I2CFile;
float vvv;
int doExit = 0;

public:
   Lcdboard()
{
        display = new DisplayILI9341_240x320x16_SPI(73,{1, 0, 70, 0,-1,-1});
        canvas = new NanoCanvas16(221, 41, canvasData);
        setup();
};
   void setupLcd();
   void setup() { setupLcd(); setupTemp(); setupVolt(); };
   void loop();
   void vidCircle();
   void setupTemp();
   void getTemp();
   void setupVolt();
   void getVolt();
   int center(int x, int w, int len) { return (x + (w - len * 16)/2); }
   int getExit() { return doExit; }
   void doEnd() { display->clear(); display->printFixedN(50, 60, "THE END !", STYLE_NORMAL,1); system("shutdown -n now"); }
   ~Lcdboard() { display->end(); delete canvas; fclose(TEMPFile); close(I2CFile); }
};

#endif
