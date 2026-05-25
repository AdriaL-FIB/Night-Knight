#include "AssetError.h"

#include <cstdlib>
#include <iostream>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#endif

using namespace std;

[[noreturn]] void fatalAssetError(const string& assetType, const string& path, const string& details)
{
	string message = "Could not load " + assetType + ":\n\n" + path;
	if(!details.empty())
		message += "\n\n" + details;

	cerr << message << endl;

#ifdef _WIN32
	MessageBoxA(NULL, message.c_str(), "Night-Knight asset error", MB_OK | MB_ICONERROR);
#endif

	exit(EXIT_FAILURE);
}
