#ifdef WIN32

#include <iostream>
#include <string>

#include "RelayBox.h"

int main()
{
	std::cout << "WIN APP: RELAY BOX 0.1\n";
	std::cout << "  BY MIKESOFT\n\n";

	RelayBox relayBox;
	relayBox.setup();
	while (true)
	{
		relayBox.loop();
	}
}

#endif // WIN32
