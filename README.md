# Nodemcu-esp8266-Automate-watering-plants
One small project that will make your life more easier.

Things needed to make Automate-watering-plants project:

Nodemcu esp8266
Relay 5v
Pump 5v
Soil moisture sensor
Breadboard
[Line notify token](https://notify-bot.line.me/th/)


# 1 Build it
    This is how Automate-watering-plants logic works
    1 Check connection on WIFI 
    2 Check with your Soil moisture sensor if Soil’s moisture is high or low
    3 If it’s low, the relay will turn on(Relay connected to water pump).
    If  it’s high, nothing would happend.
    4 sent out a signal to Nodemcu esp8266 and Line notify or Line bot will send a message.
    5 Node will back at stpe 2 again untill the Node lost power source.

    Connect pump to relay,moisture sensor, and power source to the Node.

# 2 Line Part
    You have to provite Line token from you line accouont Dev and change in in main code.

    You can check connection in serial monitor

# 3 Real world 
    Simply by put pump in water source, moisture sensor in soil, and power Node.
