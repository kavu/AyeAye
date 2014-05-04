package processor

type EventsProcessor interface {
	Process(event LoggerEvent) error
}

var loggerEventsProcessor EventsProcessor = &DefaultEventsProcessor{}
