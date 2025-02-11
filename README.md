# IR-RF Receiver

This project provides an ESP32-based solution for reading and recording both Infrared (IR) and Radio Frequency (RF) signals. It enables the decoding of signals from various remote controls and wireless devices, facilitating their integration into home automation by replaying recorded signals.

## Features

- **Dual Signal Reception**: Handles both IR and RF signals, allowing for versatile remote control integration.
- **Signal Recording and Replay**: Captures remote control signals for later use in automating home devices.
- **Decoding Capabilities**: Processes signals from multiple protocols, enabling compatibility with a wide range of devices.
- **Modular Code Structure**: Organized for easy understanding and modification, supporting customization and expansion.

## Hardware Requirements

- **ESP32 Board**: Compatible with various models such as ESP32 DevKit.
- **IR Receiver Module**: For capturing infrared signals.
- **RF Receiver Module**: For capturing radio frequency signals (typically at 433 MHz).

![4032-3024-max](https://github.com/user-attachments/assets/b0709b64-ec8e-49ce-901a-5322865a72ee)


## Software Requirements

- **Arduino IDE**: Ensure you have the latest version installed.
- **IRremote Library**: Facilitates sending and receiving infrared signals. [Arduino-IRremote/Arduino-IRremote](https://github.com/Arduino-IRremote/Arduino-IRremote)
- **RFCodes Library**: Assists in encoding and decoding RF signal patterns. [mathertel/rfcodes](https://github.com/mathertel/rfcodes)

## Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/kirillsimin/ir-rf-receiver.git
   cd ir-rf-receiver
   ```

2. **Install Required Libraries**:
   - Open the Arduino IDE.
   - Navigate to `Sketch` > `Include Library` > `Manage Libraries`.
   - Search for and install the following libraries:
     - **IRremote**: [Arduino-IRremote/Arduino-IRremote](https://github.com/Arduino-IRremote/Arduino-IRremote)
     - **RFCodes**: [mathertel/rfcodes](https://github.com/mathertel/rfcodes)

3. **Upload the Sketch**:
   - Connect your ESP32 board to your computer.
   - Open the `IR-RF-receiver.ino` file in the Arduino IDE.
   - Select the appropriate board and port from the `Tools` menu.
   - Click the upload button to program your ESP32.

## Usage

Once the sketch is uploaded:

- **Recording IR and RF Signals**:
  - Point an IR or RF remote at the respective receiver module.
  - Press a button on the remote to record the signal.
  - The ESP32 will display it in the serial monitor (115200 baud).

## Examples

IR example:

```
Timestamp : 000066.305
Library   : v2.7.8

Protocol  : NEC
Code      : 0x4B36D32C (32 Bits)
Raw Timing[67]:
   +  9028, -  4544,    +   574, -   560,    +   548, -  1712,    +   546, -   584, 
   +   574, -   560,    +   548, -  1712,    +   548, -   586,    +   574, -  1688, 
   +   574, -  1692,    +   572, -   558,    +   548, -   584,    +   550, -  1710, 
   +   558, -  1704,    +   570, -   560,    +   574, -  1686,    +   572, -  1686, 
   +   574, -   568,    +   548, -  1712,    +   552, -  1708,    +   572, -   558, 
   +   570, -  1692,    +   574, -   558,    +   548, -   584,    +   548, -  1712, 
   +   548, -  1720,    +   572, -   560,    +   548, -   584,    +   574, -  1688, 
   +   572, -   560,    +   574, -  1688,    +   552, -  1708,    +   572, -   558, 
   +   574, -   558,    +   574

uint16_t rawData[67] = {9028, 4544,  574, 560,  548, 1712,  546, 584,  574, 560,  548, 1712,  548, 586,  574, 1688,  574, 1692,  572, 558,  548, 584,  550, 1710,  558, 1704,  570, 560,  574, 1686,  572, 1686,  574, 568,  548, 1712,  552, 1708,  572, 558,  570, 1692,  574, 558,  548, 584,  548, 1712,  548, 1720,  572, 560,  548, 584,  574, 1688,  572, 560,  574, 1688,  552, 1708,  572, 558,  574, 558,  574};  // NEC 4B36D32C
uint32_t address = 0x6CD2;
uint32_t command = 0xCB;
uint64_t data = 0x4B36D32C;
```

RF example:

```
Decimal: 16776964 (24Bit) Binary: 111111111111111100000100 Tri-State: 1111111100F0 PulseLength: 381 microseconds Protocol: 1
Raw data: 11819,1250,352,1241,348,1242,352,1239,358,1232,358,1232,362,1228,365,1229,374,1227,368,1234,370,1234,372,1234,376,1230,374,1234,375,1232,380,1224,385,420,1165,425,1164,425,1165,427,1163,427,1164,1236,375,427,1166,425,1168,
```
