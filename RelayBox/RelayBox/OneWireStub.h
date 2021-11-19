#ifdef WIN32

#pragma once

class OneWire
{
public:
	OneWire(int bus);

	~OneWire();
};

#endif // WIN32