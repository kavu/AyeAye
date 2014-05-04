package processor

import "C"

import "log"

type DefaultEventsProcessor struct {
	EventsProcessor
}

func (logProcessor *DefaultEventsProcessor) Process(event LoggerEvent) error {
	log.Printf(
		"key: %#v, keycode: %d, timestamp: %f",
		C.GoString(event.key),
		event.keycode,
		event.timestamp)

	return nil
}
