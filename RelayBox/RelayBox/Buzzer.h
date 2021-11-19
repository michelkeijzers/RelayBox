// https://esp32io.com/tutorials/esp32-piezo-buzzer

#pragma once
class Buzzer
{
public:
	Buzzer();
	~Buzzer();

	void Setup(int pin);

	void Play(float frequency);
	void PlayWait(float frequency, int durationMs);
	void Stop();

private:
	const int FREQUENCY = 5000;
	const int LED_CHANNEL = 0;
	const int RESOLUTION = 8;

	uint8_t _pin;
};