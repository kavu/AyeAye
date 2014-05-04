#import <Cocoa/Cocoa.h>
#import <Carbon/Carbon.h>

#ifndef LOGGER_EVENT

#define LOGGER_EVENT
typedef struct {
  uint16_t keycode;
  double_t timestamp;
  bool isAlphaShift;
  bool isAlternate;
  bool isCommand;
  bool isControl;
  bool isHelp;
  bool isNumericPad;
  bool isSecondaryFn;
  bool isShift;
  char* key;
} LoggerEvent;

#endif
