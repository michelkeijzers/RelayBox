#ifdef WIN32

#pragma once

// Decimal
constexpr auto DEC = 1;
constexpr auto HEX = 2;

class SerialClass
{
public:
	void begin(int baudrate);

	void println();
	void println(const char* str);
	void println(char value);
	void println(unsigned int value);
	void println(int value);
	void println(int value, int mode);
	void println(float value);

	void print(const char* str);
	void print(char value);
	void print(unsigned int value);
	void print(int value);
	void print(int value, int mode);
	void print(float value);

	static void flush();

private:
	wchar_t _message[256];
	wchar_t _string[256];
};


class SerialPort
{
public:
	SerialPort() {};
};

extern SerialClass Serial;
extern SerialClass Serial1;
extern SerialClass Serial2;
//extern SerialClass Serial3;

extern SerialPort SoftwareSerial;
extern SerialPort HardwareSerial;

#endif // WINDOWS