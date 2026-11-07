# Humidity Controller
A sensor and smart outlet pair that automate floor humidifiers based on configurable ideal conditions.

This project is designed to optimize the efficiency of a humidifier while staying within a minimal budget. This is done by using a humidity sensor in juncture with a rf controlled relay to toggle power to the humidifier, allowing it to stay within a determined threshold automatically. This eliminates the common issue of humidifier overuse, making the room muggy and needing constant refills. Simply plug the humidifier cord into the female end of the relay housing and the relay assembly into the outlet, pair the relay assembly and sensor assembly, and mount the sensor in a convenient place in the room of the humidifier.

## Implementation
First clone the repository, then compile it and move it onto the respective Arduino Nanos through the Arduino IDE. From there simply follow the wiring instructions and turn the sensor on. <br>

Clone repo:<br>
```git clone https://github.com/LiamFCode/humidity_controller.git```<br>
### Sensor Wiring
Wire your lower limit potentiometer data pin to A0, upper limit potentiometer data pin to A1, DHT data pin to D2, and lastly the RF transmitter to pin D12.<br>
Remember to wire voltage and ground to everything with the proper voltages.

### Outlet Wiring
Wire your RF receiver to pin D11, and the electrical relay pin to D7. Then split the output and ground to a transformer that steps down to 5vDC to the Arduino. Finally wire the main relay positive and ground to outlet prongs and a plug, carefully housing everything before plugging anything in.

#### Disclaimer
Tinkering with this level of voltage is incredibly dangerous and if you plan to construct this, every precaution should be taken.

## License
MIT License

Copyright (c) 2025 Liam Fending

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
