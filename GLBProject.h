#pragma once

#include "CoreMinimal.h"

#ifdef GLBPROJECT_EXPORTS
#define GLBPROJECT_API __declspec(dllexport)
#else
#define GLBPROJECT_API __declspec(dllimport)
#endif