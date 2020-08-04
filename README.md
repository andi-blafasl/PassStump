# PassStump

a digistump password autotype usb-stick

## Usage

* wire up to 4 Buttons to the GPIO Pins of the DigiStump (Beware of Clones with Reset at PIN5!)
* import JC_BUTTON library to your Arduino IDE
* for German keyboard-layout copy DigiKeyboardDE.h to your ``AppData\Local\Arduino15\packages\digistump\hardware\avr\1.6.7\libraries\DigisparkKeyboard``
* Load the Sketch and change the lines 7 to 25 for your PIN, Username and Password
* change lines 32 to 35 according to your button setup
* upload sketch and enjoy

### Library Credits

[GitHub - adnan-alhomssi/DigistumpArduinoDe: Digistump library with german keyboard layout support](https://github.com/adnan-alhomssi/DigistumpArduinoDe)

[GitHub - JChristensen/JC_Button: Arduino library to debounce button switches, detect presses, releases, and long presses](https://github.com/JChristensen/JC_Button)