package processor

import "C"

import (
	"encoding/json"
	"fmt"
	"github.com/streadway/amqp"
	"time"
)

type AMQPEventsProcessor struct {
	Connection *amqp.Connection
	Channel    *amqp.Channel
	Queue      *amqp.Queue
	EventsProcessor
}

type amqpEventPayload struct {
	Keycode       uint   `json:"keycode"`
	Timestamp     string `json:"timestamp"`
	Key           string `json:"key"`
	IsAlphaShift  bool   `json:"is_alpha_shift"`
	IsAlternate   bool   `json:"is_alternate"`
	IsCommand     bool   `json:"is_command"`
	IsControl     bool   `json:"is_control"`
	IsHelp        bool   `json:"is_help"`
	IsNumericPad  bool   `json:"is_numeric_pad"`
	IsSecondaryFn bool   `json:"is_secondary_fn"`
	IsShift       bool   `json:"is_shift"`
}

func (amqpProcessor *AMQPEventsProcessor) Process(event LoggerEvent) error {
	payload := amqpEventPayload{
		Keycode:       uint(event.keycode),
		Timestamp:     fmt.Sprintf("%f", event.timestamp),
		Key:           C.GoString(event.key),
		IsAlphaShift:  bool(event.isAlphaShift),
		IsAlternate:   bool(event.isAlternate),
		IsCommand:     bool(event.isCommand),
		IsControl:     bool(event.isControl),
		IsHelp:        bool(event.isHelp),
		IsNumericPad:  bool(event.isNumericPad),
		IsSecondaryFn: bool(event.isSecondaryFn),
		IsShift:       bool(event.isShift),
	}

	jsonPayload, err := json.Marshal(payload)
	if err != nil {
		return err
	}

	msg := amqp.Publishing{
		DeliveryMode: amqp.Persistent,
		Timestamp:    time.Now(),
		ContentType:  "application/json",
		Body:         jsonPayload,
	}

	return amqpProcessor.Channel.Publish("", amqpProcessor.Queue.Name, true, false, msg)
}

func NewAMQPEventsProcessor(conn *amqp.Connection, ch *amqp.Channel, q *amqp.Queue) *AMQPEventsProcessor {
	return &AMQPEventsProcessor{
		Connection: conn,
		Channel:    ch,
		Queue:      q,
	}
}
