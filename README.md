# URU Card Hardware Test

[![Build Status](https://travis-ci.com/uru-card/uru-card-hardware-test.svg?branch=main)](https://travis-ci.com/uru-card/uru-card-hardware-test)

[URU Card](https://github.com/uru-card/uru-card) is an Arduino based FIDO2 Authenticator. This repository contains source code for the timple utility to test hardware capabilities of URU Card device.

### Development Environment - PlatformIO

To build the firmware you will need [PlatformIO](https://platformio.org/). Follow [the instructions](https://platformio.org/platformio-ide) to install it for your platform.

## Building

First of all, get a copy of the source code using either `git` command or downloading a zip file.

Open the project in the PlatformIO IDE. Connect the dev board to your computer then build and upload the firmware from the PlatformIO. All the required libraries will be downloaded automatically.

I'm using the following command in terminal window:

```bash
$ pio run -t upload -t monitor
```

The program will start immediately and the serial console will start output of the debug information.

The built-in display will display status of the main parts (if connected properly) - Display Status, Keyboard Status, Cryptographic device status.

## Authors

* [**Andrey Ovcharov**](https://github.com/snakeye) - project owner

See also the list of [contributors](https://github.com/uru-card/uru-card/contributors) who participated in this project.


## References

* [Information about URU Card project](https://en.ovcharov.me/category/fido2/)
* [SSD1306 oled driver library for monochrome 128x64 and 128x32 displays](https://platformio.org/lib/show/135/Adafruit%20SSD1306)
* [Arduino library for the MPR121-based capacitive sensors](https://platformio.org/lib/show/839/Adafruit%20MPR121)
* [Library for the Microchip ATECCX08a Cryptographic Co-processors](https://platformio.org/lib/show/6789/SparkFun%20ATECCX08a%20Arduino%20Library)