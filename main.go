package main

import (
	ayeaye "github.com/kavu/ayeaye/processor"
	"github.com/streadway/amqp"
	"log"
	"os"
)

func main() {
	connection, err := amqp.Dial(os.Getenv("RMQ_URL"))
	if err != nil {
		log.Fatalf("connection.open: %s", err)
	}
	defer connection.Close()

	channel, err := connection.Channel()
	if err != nil {
		log.Fatalf("channel.open: %s", err)
	}

	queue, err := channel.QueueDeclare("info", true, false, false, false, nil)
	if err != nil {
		log.Fatalf("queue.declare: %v", err)
	}

	amqpProcessor := ayeaye.NewAMQPEventsProcessor(connection, channel, &queue)
	ayeaye.SetLogProcessor(amqpProcessor)

	ayeaye.StartLogger()
}
