#ifndef DISPLAY_H
#define DISPLAY_H

#define pinBacklight 13
#define pinRS 15
//#define pinRW 19
#define pinE 14
/*
#define pinD0 9
#define pinD1 8
#define pinD2 7
#define pinD3 6
*/
#define pinD4 9
#define pinD5 8
#define pinD6 7
#define pinD7 6

void writeDisplay();

void displayInit();

void displayBacklightToggle();

void clearDisplay();

#endif