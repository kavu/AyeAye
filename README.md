# AyeAye

AyeAye is a PoC OSX Keylogger written in Go + Objective-C with RabbitMQ Backend.

## Installation

Please, be sure that your `GOPATH` is set properly. Then clone the repo and run the `make`. Make should clone all the dependencies and build the `AyeAye` binary.

Run with `RMQ_URL=amqp://guest:guest@localhost:5672/ sudo ./AyeAye` (URL is just and example, don't forget to change acording your RabbitMQ setup).

