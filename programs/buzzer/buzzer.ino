int SPEAKER = 10;    // The speaker is on pin 8

int freq = 50;      // Starting frequency

void setup()
{
    pinMode(SPEAKER, OUTPUT);
}

void loop()
{
    freq += 100;      // add 100 to freq

    if (freq > 8000)
    {
        noTone(SPEAKER);
        freq = 50;
    }

    tone(SPEAKER, freq);

    delay(100);
}
