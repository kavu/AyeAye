package processor

/*
#cgo CFLAGS: -x objective-c
#cgo LDFLAGS: -framework Cocoa -framework Carbon

#include "header.h"

extern void startLogger(void);
*/
import "C"

type LoggerEvent C.LoggerEvent

//export go_ProcessEvent
func go_ProcessEvent(event LoggerEvent) {
	loggerEventsProcessor.Process(event)
}

func StartLogger() {
	C.startLogger()
}
