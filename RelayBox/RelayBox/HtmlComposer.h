#pragma once

#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)

#include "ServerData.h"


class HtmlComposer
{
public:
	HtmlComposer(ServerData& serverData);

	~HtmlComposer();

	void Compose(STRING& ptr);

private:
	ServerData& _serverData;
};

