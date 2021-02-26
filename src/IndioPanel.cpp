#include "IndioPanel.h"

#define BUTTON_ENTER_PIN 24
#define BUTTON_UP_PIN 25
#define BUTTON_DOWN_PIN 23
#define BACKLIGHT_PIN 26
#define BACKLIGHT_DEFAULT_LEVEL 128
#define BACKLIGHT_MAX_TIMEOUT 3600000
#define DEBOUNCE_DEFAULT 150
#define DEBOUNCE_MAX 2000


//Public

void IndioPanel::begin()
{
    pinMode(BUTTON_ENTER_PIN, INPUT);
    pinMode(BUTTON_UP_PIN, INPUT);
    pinMode(BUTTON_DOWN_PIN, INPUT);
    pinMode(BACKLIGHT_PIN, OUTPUT);
    debounceTime = DEBOUNCE_DEFAULT;
    timeout = 0;
    level = BACKLIGHT_DEFAULT_LEVEL;
}


bool IndioPanel::read ()
{
    buttonEnter.state = !digitalRead(BUTTON_ENTER_PIN); // Results are inverted so that Pressed == HIGH
    buttonUp.state = !digitalRead(BUTTON_UP_PIN);
    buttonDown.state = !digitalRead(BUTTON_DOWN_PIN);
    if (timeout > 0)
    {
        if (buttonEnter.state || buttonUp.state || buttonDown.state) backlightMillis = millis();
        if (millis() - backlightMillis < timeout) backlightOn();
        else backlightOff();
    }
    processButton(&buttonEnter);
    processButton(&buttonUp);
    processButton(&buttonDown);
    return (buttonEnter.pressed || buttonUp.pressed || buttonDown.pressed);
}


void IndioPanel::setDebounce(int debounce)
{
    if (debounce < DEBOUNCE_MAX && debounce > 0) debounceTime = debounce;
}


bool IndioPanel::enterPressed ()
{
    return buttonEnter.pressed;
}


bool IndioPanel::upPressed ()
{
    return buttonUp.pressed;
}


bool IndioPanel::downPressed ()
{
    return buttonDown.pressed;
}


bool IndioPanel::enterHeld ()
{
    return !digitalRead(BUTTON_ENTER_PIN);
}


bool IndioPanel::upHeld ()
{
    return !digitalRead(BUTTON_UP_PIN);
}


bool IndioPanel::downHeld ()
{
    return !digitalRead(BUTTON_DOWN_PIN);
}


void IndioPanel::backlightOn()
{
    analogWrite(BACKLIGHT_PIN, level);
}


void IndioPanel::backlightOff()
{
    analogWrite(BACKLIGHT_PIN, 0);
}


void IndioPanel::timeoutRestart()
{
    backlightMillis = millis();
}


bool IndioPanel::timeoutExpired()
{
    return millis() - backlightMillis > timeout;
}


void IndioPanel::setBacklightTimeout(long t)
{
    if (t >= 0 && t <= BACKLIGHT_MAX_TIMEOUT) timeout = t;
}


void IndioPanel::setBacklightLevel (byte l)
{
    level = l;
}


//Private

void IndioPanel::processButton(button_t * b)
{
    b->pressed = false;
    if (b->state == LOW && b->previous == HIGH)
    {
        b->pressed = (millis() - b->timeLast) > debounceTime;
        b->timeLast = millis();
    }
    b->previous = b->state;
}
