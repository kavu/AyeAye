package processor

func SetLogProcessor(processor EventsProcessor) {
	loggerEventsProcessor = processor
}
