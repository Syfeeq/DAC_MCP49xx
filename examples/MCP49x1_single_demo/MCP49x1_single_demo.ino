//
// Example for the MCP49x1 *single* DACs
// For the dual MCP49x2 series, see the other bundled example sketch.
//

#include <DAC_MCP49xx.h>

/*
 Since this is an implementation using a software SPI, it is possible that
 the pins defined below should not overlap with the pins used for hardware SPI.
 I have not tested that since my application was using other devices
 connected to hardware SPI, which, by the way, were unable to work along with
 the MCP4901 chip connected to the same bus. That was the reason why This
 modification was created.
*/

// The Arduino pins used for the Soft SPI communication
#define SDI_PIN 2
#define SDO_PIN 3
#define SCK_PIN 4
#define CS_PIN 5

// Set up the DAC.
// First argument: DAC model (MCP4901, MCP4911, MCP4921)
// Second argument: SDI pin
// Third argument: SDO pin
// Fourth argument: SCK pin
// Fifth argument: CS pin
// (The last argument, the LDAC pin, can be left out if not used)
DAC_MCP49xx dac(DAC_MCP49xx::MCP4901, SDI_PIN, SDO_PIN, SCK_PIN, CS_PIN);

void setup() {
  // Set the SPI frequency to 1 MHz (on 16 MHz Arduinos), to be safe.
  // DIV2 = 8 MHz works for me, though, even on a breadboard.
  // This is not strictly required, as there is a default setting.
  dac.setSPIDivider(SPI_CLOCK_DIV16);

  // Use "port writes", see the manual page. In short, if you use pin 10 for
  // SS (and pin 7 for LDAC, if used), this is much faster.
  // Also not strictly required (no setup() code is needed at all).
  dac.setPortWrite(true);
}

// Output something slow enough that a multimeter can pick it up.
// For MCP4901, use values below (but including) 255.
// For MCP4911, use values below (but including) 1023.
// For MCP4921, use values below (but including) 4095.
void loop() {
  dac.output(255);
  delay(2500);
  dac.output(0);
  delay(2500);
}
