# Humidity Controller

I use my humidifier at night religiously in winter, but having to remember to turn it on and off every day is not only a little tedious, but also very ineffecient to have it constantly running. Now what better way to fix this than some good old fashioned home automation? In this project I am making an altoid tin contained device that monitors humidity and controls the humidifier accordingly.

The biggest part of this is in the aloid tin. Comprised of a DHT11 temperature and humidity sensor, an ESP32 WROOM for processing, 433mhz rf transmitter and reciever modules, an LM2596 step-down buck converter, a 9-volt battery, and of course, a tin of altoids. This all comes out to around $25, but most likely you will have a mint tin and a battery at a minimum.

The other part of this is the reciever module also requires an ESP32, the reciever module from earlier, and a 120vac relay with a 5vdc trigger.
