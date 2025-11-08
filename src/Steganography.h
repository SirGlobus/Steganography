#ifndef STEGANOGRAPHY
#define STEGANOGRAPHY
#include "SteganographyImage.h"
#include "SteganographyLinearImage.h"
#include <vector>
#include <string>
std::vector<std::string> EncodingsNames()
{
    return 
    {
        "Linear"
    };
}

#endif //STEGANOGRAPHY