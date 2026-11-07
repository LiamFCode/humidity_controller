/*---------------------------------------*/
#include <RH_ASK.h>
#include <SPI.h>
#include <string.h>
/*------Pin-config------*/
#define RF_RX_PIN 11
#define RELAY_PIN 7
/*---------------------------------------*/   /*---init---*/
const uint8_t RELAY_ON = HIGH;
const uint8_t RELAY_OFF = LOW;

const unsigned long SIGNAL_TIMEOUT = 10000;

RH_ASK radio(2000, RF_RX_PIN, 12, 10);

unsigned long lastValidMessage = 0;
bool HaveValidMessage = false;
bool relayOn = false;

void setup() {
	Serial.begin(9600);

	digitalWrite(RELAY_PIN, RELAY_OFF);
	pinMode(RELAY_PIN, OUTPUT);
	setRelay(false);
	
	if(!radio.init()) {
		Serial.println("ERROR: rf init failed");
		while(true) {
			digitalWrite(RELAY_PIN, RELAY_OFF);
			delay(1000);
		}
	}

	Serial.println("relay init successful");
}
/*---------------------------------------*/   /*---rf-rx-&-relay-action---*/
void loop() {
	uint8_t buffer[80];
	uint8_t length = sizeof(buffer) - 1;
	
	/*---RX-RF-packet---*/
	if(radio.recv(buffer, &length)) {
		buffer[length] = '\0';
		
		Serial.println("RX: "+(char*)buffer);
		char* status = strstr((char*)buffer, ";S=";
		
		/*---msg-parse-&-rxn--*/
		if(status != NULL) {
			status+=3;
			if(strcmp(status, "LOW")==0||strcmp(status, "NORMAL")==0||strcmp(status, "HIGH")==0||strcmp(status, "SENSOR_ERROR")==0) {
				haveValidMessage = true;
				lastValidMessage = millis();
				if (strcmp(status, "LOW")==0) {
					setRelay(true); //humidifier on; humidity too low
				} else {
					setRelay(false); //humidifier off; too humid, at humidity, or error
				}

				Serial.println("Humidity status: "+status);
			} else {
				Serial.println("Invalid msg format");
			}
		}
		
		/*---deadman-switch---*/
		if (haveValidMessage && millis() - lastValidMessage >= SIGNAL_TIMEOUT) {
			Serial.println("RF timeout; switching relay off");
			setRelay(false);
		}
	}				
/*---------------------------------------*/   /*---relay-flip---*/
void setRelay(bool turnedOn) {
	relayOn = turnedOn;
	digitalWrite(RELAY_PIN, turnedOn ? RELAY_ON : RELAY_OFF);
	Serial.println("Relay state: "+turnedOn ? "ON" : "OFF");
}
