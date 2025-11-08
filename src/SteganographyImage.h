#ifndef STEGANOGRAPHY_IMAGE_H
#define STEGANOGRAPHY_IMAGE_H
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include <iostream>
#include <vector>

class SteganographyImage
{
public:
    SteganographyImage(std::string path)
    {
        this->path = path;
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        if(!data)
            throw std::runtime_error("Failed to load file");
        
        for(int i = 0; i < height; ++i)
            for(int j = 0; j < width; ++j)
            {
                int idx = (i * width + j) * channels;
                pixels.push_back({data[idx], data[idx+1], data[idx+2], channels == 4 ? data[idx+3] : (uint8_t)254});
            }
        stbi_image_free(data);
    }

    virtual std::string GetText() = 0;
    virtual void PushText(std::string s) = 0;

    bool SaveTo(std::string path)
    {
        return stbi_write_png(path.c_str(), width, height, 4, pixels.data(), width * 4);
    }

    inline bool Save()
    {
        return SaveTo(this->path);
    }
protected:
    struct Pixel
    {
        uint8_t r, g, b, a;
    };
    std::vector<Pixel> pixels;
    std::string path;
    int width, height, channels;

    virtual void SetBit(int bit, int v)
    {
        uint8_t* pos;
        int pixel = bit / 4;
        switch(bit % 4)
        {
        default:
        case 0:
            pos = &pixels[pixel].r;
            break;
        case 1:
            pos = &pixels[pixel].g;
            break;
        case 2:
            pos = &pixels[pixel].b;
            break;
        case 3:
            pos = &pixels[pixel].a;
        }
        if(v)
            *pos |= 1;
        else
            *pos &= 254;
    }
    virtual int GetBit(int bit)
    {
        uint8_t* pos;
        int pixel = bit / 4;
        switch(bit % 4)
        {
        default:
        case 0:
            pos = &pixels[pixel].r;
            break;
        case 1:
            pos = &pixels[pixel].g;
            break;
        case 2:
            pos = &pixels[pixel].b;
            break;
        case 3:
            pos = &pixels[pixel].a;
        }
        return *pos & 1;
    }
};

#endif //STEGANOGRAPHY_IMAGE_H