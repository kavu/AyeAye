APP=AyeAye
CC=clang

all: $(APP)

.PHONY: $(APP)
$(APP):
	go get -u github.com/kavu/ayeaye/processor
	go get -u github.com/streadway/amqp
	CC=$(CC) go build -ldflags="-linkmode=external" -o $(APP)

clean:
	rm $(APP)
