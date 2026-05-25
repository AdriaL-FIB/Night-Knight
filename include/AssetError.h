#ifndef _ASSET_ERROR_INCLUDE
#define _ASSET_ERROR_INCLUDE

#include <string>

[[noreturn]] void fatalAssetError(const std::string& assetType, const std::string& path, const std::string& details = "");

#endif // _ASSET_ERROR_INCLUDE
