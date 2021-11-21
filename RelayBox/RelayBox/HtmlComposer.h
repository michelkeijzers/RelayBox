#pragma once

#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)

class RelayBox;

class HtmlComposer
{
public:
	HtmlComposer(RelayBox* relayBox);

	void Compose(STRING& ptr);

private:
	RelayBox& _relayBox;
};

