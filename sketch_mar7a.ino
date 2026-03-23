#include "HomeSpan.h"

#define RELAY_PIN 5

struct RelaySwitch : Service::Switch {

  SpanCharacteristic *power;

  RelaySwitch() : Service::Switch() {

    power = new Characteristic::On();

    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW); // OFF initially
  }

  boolean update() {

    if (power->getNewVal()) {
      digitalWrite(RELAY_PIN, HIGH);  // ON
      Serial.println("Relay ON");
    } else {
      digitalWrite(RELAY_PIN, LOW);   // OFF
      Serial.println("Relay OFF");
    }

    return true;
  }
};

void setup() {

  Serial.begin(115200);

  homeSpan.begin(Category::Lighting, "ESP32 Relay");

  new SpanAccessory();

    new Service::AccessoryInformation();
      new Characteristic::Name("LED Strip Relay");
      new Characteristic::Manufacturer("ESP32");
      new Characteristic::SerialNumber("123-ABC");
      new Characteristic::Model("RelaySwitch");
      new Characteristic::FirmwareRevision("1.0");

    new RelaySwitch();
}

void loop() {
  homeSpan.poll();
}