//https://github.com/NeilSWells/IndioPanel
#include <IndioPanel.h>
IndioPanel panel;


void setup()
{
    SerialUSB.begin(9600);
    panel.begin();
    panel.setBacklightTimeout(10000); //Keep the backlight on for 10 seconds after the last keypress. Max 1 hour = 3600000
    panel.setBacklightLevel(200); //Set the backlight brightness to 200 - the default is 128. Max 255
    panel.setDebounce(500); //Set the debounce to 500ms (0.5 seconds) - the default is 150ms. Max 2000
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
