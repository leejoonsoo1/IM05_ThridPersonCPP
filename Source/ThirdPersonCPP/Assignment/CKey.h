#pragma once

#include "CoreMinimal.h"
#include "Containers/Map.h"

enum class KeyColorEnum
{
	Red,
	Green,
	Blue
};

class THIRDPERSONCPP_API CKey
{
public:
	CKey();
	~CKey();

	int GetKey(KeyColorEnum Color) { return Map[Color]; }
	void SetKey(KeyColorEnum Color) { if (Map[Color] < 1) Map[Color]++; }
	
private:
	TMap<KeyColorEnum, int> Map;
};
