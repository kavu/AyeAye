# AyeAye

AyeAye is a PoC OSX Keylogger written in Go + Objective-C with RabbitMQ Backend.

## History

Few days ago [@ifesdjeen](https://github.com/ifesdjeen) asked me about Go + Objective-C possibilites. He wanted to make a simple OSX keylogger. Well, I found that's interesting, because I've already done [Go + Objective-C PoC project](https://github.com/kavu/cocoa-go) and AyeAye is how I've solved it. I am not sure that many of you will find it useful, but for learning purposes - why not? "Please, in the name of the Science — question everything."

## Installation

Please, be sure that your `GOPATH` is set properly. Then clone the repo and run the `make`. Make should clone all the dependencies and build the `AyeAye` binary.

Run with `RMQ_URL=amqp://guest:guest@localhost:5672/ sudo ./AyeAye` (URL is just and example, don't forget to change acording your RabbitMQ setup).

