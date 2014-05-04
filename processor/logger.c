#include "_cgo_export.h"

#include "header.h"

CFStringRef createStringForKeycode(CGKeyCode keyCode) {
  UInt32 keysDown = 0;
  UniChar chars[4];
  UniCharCount realLength;

  TISInputSourceRef currentKeyboard = TISCopyCurrentKeyboardInputSource();
  CFDataRef layoutData = TISGetInputSourceProperty(currentKeyboard, kTISPropertyUnicodeKeyLayoutData);
  const UCKeyboardLayout* keyboardLayout = (const UCKeyboardLayout*)CFDataGetBytePtr(layoutData);


  UCKeyTranslate(keyboardLayout,
                 keyCode,
                 kUCKeyActionDisplay,
                 0,
                 LMGetKbdType(),
                 kUCKeyTranslateNoDeadKeysBit,
                 &keysDown,
                 sizeof(chars) / sizeof(chars[0]),
                 &realLength,
                 chars);

  CFRelease(currentKeyboard);

  return CFStringCreateWithCharacters(kCFAllocatorDefault, chars, 1);
}

char* CFStringToUTF8String(CFStringRef aString) {
  if (aString == NULL) {
    return NULL;
  }

  CFIndex length = CFStringGetLength(aString);
  CFIndex maxSize = CFStringGetMaximumSizeForEncoding(length, kCFStringEncodingUTF8);
  char *buffer = (char *)malloc(maxSize);

  if (CFStringGetCString(aString, buffer, maxSize, kCFStringEncodingUTF8)) {
    return buffer;
  }

  return NULL;
}

NSTimeInterval getEventUnixtimestamp(CGEventTimestamp timestamp) {
  NSTimeInterval seconds = (NSTimeInterval)timestamp / 1000000000.0;
  EventTime currentTimeInSeconds = GetCurrentEventTime();
  NSDate* startTime = [NSDate dateWithTimeIntervalSinceNow:-currentTimeInSeconds];
  NSDate* eventTime = [startTime dateByAddingTimeInterval:seconds];
  return [eventTime timeIntervalSince1970];
}

CGEventRef logHandler(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void* refcon) {
  CGEventFlags flags = CGEventGetFlags(event);
  CGKeyCode keycode = (CGKeyCode)CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
  char* key = CFStringToUTF8String(createStringForKeycode(keycode));
  CGEventTimestamp timestamp = CGEventGetTimestamp(event);

  LoggerEvent loggerEvent = {
    .keycode = keycode,
    .timestamp = getEventUnixtimestamp(timestamp),
    .key = key,
    .isAlphaShift = (flags & kCGEventFlagMaskAlphaShift),
    .isAlternate = (flags & kCGEventFlagMaskAlternate),
    .isCommand = (flags & kCGEventFlagMaskCommand),
    .isControl = (flags & kCGEventFlagMaskControl),
    .isHelp = (flags & kCGEventFlagMaskHelp),
    .isNumericPad = (flags & kCGEventFlagMaskNumericPad),
    .isSecondaryFn = (flags & kCGEventFlagMaskSecondaryFn),
    .isShift = (flags & kCGEventFlagMaskShift)
  };

  go_ProcessEvent(loggerEvent);

  return event;
}

void startLogger() {
  @autoreleasepool {
    CGEventMask eventMask = 1 << kCGEventKeyUp;
    CFMachPortRef eventTap = CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, 1, eventMask, logHandler, "");
    CFRunLoopSourceRef runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);

    CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
    CGEventTapEnable(eventTap, true);
    CFRunLoopRun();
  }
}

