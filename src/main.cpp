#include <Arduino.h>

//#define DEBUG

#define MOVE_SENSOR_PIN   5 // digital in
#define LIGHT_SENSOR_PIN  6 // analog
#define LED_PIN           3 // pwm digital out

#define FADE_IN_DELAY     1
#define FADE_OUT_DELAY    8


// light level below this level is considered as dark
const int LightThreshold = 45;

enum LedState
{
    Off,
    FadeIn,
    On,
    FadeOut
};

bool prevOn = false;
int ledLevel = 0;
LedState ledState = Off;


void setup()
{
#ifdef DEBUG
    Serial.begin(9600);
#endif
    pinMode(MOVE_SENSOR_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
}


void loop()
{
#ifdef DEBUG
    int lightLvl = analogRead(LIGHT_SENSOR_PIN);
    Serial.println(lightLvl);
#endif

    bool on = digitalRead(MOVE_SENSOR_PIN);
    bool savePrevOn = true;
    if (on && !prevOn)
    {
        if (ledState == Off)
        {
            // check for light level first
            int lightLvl = analogRead(LIGHT_SENSOR_PIN);
            if (lightLvl < LightThreshold)
                ledState = FadeIn;
            else
                savePrevOn = false;
        }
        else
            ledState = FadeIn;
    }
    if (!on && prevOn && ledState != Off)
    {
        ledState = FadeOut;
    }
    if (savePrevOn)
        prevOn = on;
    analogWrite(LED_PIN, ledLevel);

    if (ledState == FadeIn)
    {
        delay(FADE_IN_DELAY);
        if (ledLevel == 255)
            ledState = On;
        else
            ledLevel++;
    }
    else if (ledState == FadeOut)
    {
        delay(FADE_OUT_DELAY);
        if (ledLevel == 0)
            ledState = Off;
        else
            ledLevel--;
    }
}


