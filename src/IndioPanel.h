// IndioPanel - Buttons and backlight on the Industruino
// Copyright Neil Wells 2021  https://github.com/NeilSWells
// MIT License

#ifndef INDIO_PANEL_h
#define INDIO_PANEL_h

#include <Arduino.h>

struct button_t
{
    bool state;
    bool previous;
    bool pressed;
    unsigned long timeLast;
};

class IndioPanel
{
    public:
        void begin();
        bool read();
        void setDebounce(int debounce);
        bool enterPressed();
        bool upPressed();
        bool downPressed();
        bool enterHeld();
        bool upHeld();
        bool downHeld();
        void backlightOn();
        void backlightOff();
        void timeoutRestart();
        void setBacklightTimeout(long t);
        void setBacklightLevel(byte l);
    private:
        void processButton(button_t * b);
        unsigned int debounceTime;
        button_t buttonEnter;
        button_t buttonUp;
        button_t buttonDown;
        unsigned int timeout;
        byte level;
        unsigned long backlightMillis;
};

#endif
