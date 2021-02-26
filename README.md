# IndioPanel
## _Button and Backlight Library for the Industruino_

Library to access the buttons and backlight on the Industruino D21G.
The library includes a timeout to bring the backlight on as a key is pressed and keep it on for a set time.

## Basic code

    #include "IndioPanel.h"
    IndioPanel panel;
    
    void setup()
    {
        SerialUSB.begin(9600);
        panel.begin();
        panel.setBacklightTimeout(10000); //10 Seconds
    }
    
    void loop()
    {
        if (panel.read())
        {
            if (panel.enterPressed()) SerialUSB.println("Enter pressed");
            if (panel.downPressed()) SerialUSB.println("Down pressed");
            if (panel.upPressed()) SerialUSB.println("Up pressed");
        }
    }

## Functions
    begin()
    bool = read()
    bool = enterPressed()
    bool = upPressed()
    bool = downPressed()
    bool = enterHeld()
    bool = upHeld()
    bool = downHeld()
    setDebounce(int)
    setBacklightTimeout(long)
    timeoutRestart()
    bool = timeoutExpired()
    setBacklightLevel(byte)    
    backlightOn()
    backlightOff()

## Notes

### read()
Processes the buttons and the backlight timeout.
This is where most of the work is done and generally it should be in **loop()** so that it's called regularly.
Returns true if any of the buttons have been pressed and only after the button has been released.

### enterPressed() - upPressed() - downPressed()
Returns true if the button was pressed in the **read()** function.

### enterHeld() - upHeld() - downHeld()
Returns true while the button is being held down.
No need to call **read()** first.

### setDebounce(int)
Debounce refers to how long a button needs to be held before it is considered to have been pressed.
The default is 150ms. The maximum is 2000ms (2 seconds)
The shorter the debounce, the more responsive the buttons.
The longer the debounce, the more sure you can be that the press was meant.

## backlightTimeout(long)
The backlight timeout brings on the backlight for a specified time after a button is pressed.
As long as a button is pressed within the timeout period, the backlight will stay on.
The parameter is the time in milliseconds. 1000 = 1 second
Maximum 3,600,000 ms or 1 hour. 
`backlightTimeout(15000);` Sets a timeout of 15 seconds.
`backlightTimeout(0);` Turns off the backlight timeout. Use backlightOn() - backlighOff() for manual control.

## backlightRestart()
Restarts the backlight timer to stop the timer expiring.

## timeoutExpired()
Returns true if the timeout has expired.

## backlightLevel(byte)
Sets the brightness for the backlight.
The default is 128. The maximum is 255.

### backlightOn() - backlightOff()
Turns the backlight on and off if you are not using the timeout facility.

## Contact
https://github.com/NeilSWells

## License

MIT
