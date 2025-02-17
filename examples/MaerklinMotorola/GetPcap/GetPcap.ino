#include <MaerklinMotorola.h>

#define INPUT_PIN 2

MaerklinMotorola mm(INPUT_PIN);

void setup() {
  attachInterrupt(digitalPinToInterrupt(INPUT_PIN), isr, CHANGE);

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  Serial.println("Timestamps;Trits;Address;SubAdres");
}

void loop() {
  mm.Parse();
  MaerklinMotorolaData* Data = mm.GetData();
  if(Data) {
    Serial.print(Data->TimeStamps[0]);
    Serial.print(";");
    for(int i=0;i<9;i++) {
      Serial.print(Data->Trits[i]);
    }
    Serial.print(";");
    Serial.print(Data->Address);
    Serial.print(";");
    Serial.print(Data->SubAddress);
    Serial.println();
  }
}

void isr() {
  mm.PinChange();
}
