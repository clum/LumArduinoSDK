#include "LumHCSR04.h"

/// <summary>
/// Pulse the sensor and obtain the time of flight of the signal (outgoing, bounce, return).
/// </summary>
/// <param name="PinHCS04Trigger"></param>
/// <param name="PinHCS04Echo"></param>
/// <param name="timeout"></param>
/// <returns>Total time of round trip flight (microseconds)</returns>
int HCSR04GetTimeOfFlight_ms(int PinHCS04Trigger, int PinHCS04Echo, unsigned long timeout)
{
    //set HC-S04 trigger to low
    digitalWrite(PinHCS04Trigger, LOW);
    delayMicroseconds(2);

    //set HC-S04 trigger to high for 10 microseconds to initiate a pulse
    digitalWrite(PinHCS04Trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(PinHCS04Trigger, LOW);

    //obtain the response from the echo pin
    int timeOfFlight_microseconds = pulseIn(PinHCS04Echo, HIGH, timeout);

    return timeOfFlight_microseconds;
}

/// <summary>
/// Pulse the sensor and obtain the distance from sensor to object.
/// </summary>
/// <param name="PinHCS04Trigger"></param>
/// <param name="PinHCS04Echo"></param>
/// <param name="timeout"></param>
/// <returns>Distance from sensor to object (cm)</returns>
int HCSR04GetDistance_cm(int PinHCS04Trigger, int PinHCS04Echo, unsigned long timeout)
{
    int timeOfFlight_microseconds = HCSR04GetTimeOfFlight_ms(PinHCS04Trigger, PinHCS04Echo, timeout);

    //convert to distance
    int distance_cm = timeOfFlight_microseconds * 0.034 / 2;
    return distance_cm;
}
