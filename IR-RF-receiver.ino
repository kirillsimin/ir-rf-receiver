#include <Arduino.h>
#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRac.h>
#include <IRutils.h>

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
const uint16_t kRecvPin = 14;
const uint32_t kBaudRate = 115200;
const uint16_t kCaptureBufferSize = 1024;

#if DECODE_AC

const uint8_t kTimeout = 50;
#else   // DECODE_AC

const uint8_t kTimeout = 15;
#endif  // DECODE_AC
const uint16_t kMinUnknownSize = 12;

IRrecv irrecv(kRecvPin, kCaptureBufferSize, kTimeout, true);
decode_results results;  // Somewhere to store the results

void setup() {

  Serial.begin(115200);
  mySwitch.enableReceive(digitalPinToInterrupt(18));
  
#if defined(ESP8266)
  Serial.begin(kBaudRate, SERIAL_8N1, SERIAL_TX_ONLY);
#else  // ESP8266
  Serial.begin(kBaudRate, SERIAL_8N1);
#endif  // ESP8266
  while (!Serial)  // Wait for the serial connection to be establised.
    delay(50);
  Serial.printf("\nIRrecvDumpV2 is now running and waiting for IR input on Pin "
                "%d\n", kRecvPin);
#if DECODE_HASH
  // Ignore messages with less than minimum on or off pulses.
  irrecv.setUnknownThreshold(kMinUnknownSize);
#endif                  // DECODE_HASH
  irrecv.enableIRIn();  // Start the receiver
}

// The repeating section of the code
void loop() {

  if (mySwitch.available()) {
    output(mySwitch.getReceivedValue(), mySwitch.getReceivedBitlength(), mySwitch.getReceivedDelay(), mySwitch.getReceivedRawdata(),mySwitch.getReceivedProtocol());
    mySwitch.resetAvailable();
  }

  if (irrecv.decode(&results)) {
    uint32_t now = millis();
    Serial.printf("Timestamp : %06u.%03u\n", now / 1000, now % 1000);
    if (results.overflow)
      Serial.printf(
          "WARNING: IR code is too big for buffer (>= %d). "
          "This result shouldn't be trusted until this is resolved. "
          "Edit & increase kCaptureBufferSize.\n",
          kCaptureBufferSize);

    Serial.println("Library   : v" _IRREMOTEESP8266_VERSION_ "\n");

    Serial.print(resultToHumanReadableBasic(&results));

    String description = IRAcUtils::resultAcToString(&results);
    if (description.length()) Serial.println("Mesg Desc.: " + description);
    yield();  // Feed the WDT as the text output can take a while to print.
    Serial.println(resultToTimingInfo(&results));
    yield();  // Feed the WDT (again)
    Serial.println(resultToSourceCode(&results));
    Serial.println();    // Blank line between entries
    yield();             // Feed the WDT (again)
  }
}
