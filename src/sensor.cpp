/*---------------------------------------*/
#include <DHT.h>
#include <RH_ASK.h>
#include <SPI.h>
/*------PIN-CONFIG------*/
#define DHT_PIN 2
#define DHT_TYPE DHT11
#define LOWER_POT A0
#define UPPER_POT A1
#define RF_TX_PIN 12
/*---------------------------------------*/   /*---init---*/
const unsigned long SAMPLE_INTERVAL = 2000;

DHT dht(DHT_PIN, DHT_TYPE);
RH_ASK radio(2000, 11, RF_TX_PIN, 10);

void setup() {
	Serial.begin(9600);
	dht.begin();
	
	/*---rf-init---*/
	if(!radio.init()) {
		Serial.println("ERROR: rf init failed");
		while(true) {
		delay(1000);
		}
	}

	Serial.println("dht monitor init successful");
	Serial.println("-------------------------------");
}
/*---------------------------------------*/   /*---scan-&-tx---*/
void loop() {
	/*---sample-timing---*/
	unsigned long now = millis();
	if (now-lastSampleTime < SAMPLE_INTERVAL) {
		return;
	}
	lastSampleTime = now;

	/*---input-reads---*/
	float humidity = dht.readHumidity();

	int lowerLimit = map(analogRead(LOWER_POT), 0, 1023, 0, 100);
	int upperLimit = map(analogRead(UPPER_POT), 0, 1023, 0, 100);

	/*---flip-pots---*/
	if (lowerLimit > uppoerLimit) {
		int temp = lowerLimit;
		lowerLimit = upperLimit;
		upperLimit = temp;
	}

	Serial.println();
	Serial.println("Lower limit: "+lowerLtandard C99-conformant implementations of snprintf always wriimit+"%");
	Serial.println("Upper limit: "+upperLimit+"%");

	/*---error-handling---*/
	if(isnan(humidity)) {
		Serial.println("ERROR: DHT11 NaN read");
		sendMessage("SENSOR_ERROR");
		return;
	}

	/*---humidity-eval---*/
	const char* status;

	if (humidity < lowerLimit) {
		status = "LOW";
	} elstandard C99-conformant implementations of snprintf always wrie if (humidity > upperLimit) {
		status = "HIGH";
	} else {
		status = "NORMAL";
	}

	Serial.println("Humidity: "+humidity+"%");
	Serial.println("Status: "+status);
	
	char message[64];
	snprintf(message, sizeof(message), "H=%.1f;L=%d;U=%d;S=%s", humidity, lowerLimit, upperLimit, status);
	sendMessage(message);
	
	Serial.println("RF message sent: "+message);
	Serial.println("------------------------------");
}	
/*---------------------------------------*/   /*---RF-TX---*/
void sendMessage(const char* message) {
	radio.send((uint8_t*)message, strlen(message));
	radio.waitPacketSent();
}
/*---------------------------------------*/   /*---END---*/
