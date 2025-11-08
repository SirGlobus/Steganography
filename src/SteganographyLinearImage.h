#ifndef STEGANOGRAPHY_LINEAR_IMAGE_H
#define STEGANOGRAPHY_LINEAR_IMAGE_H
#include "SteganographyImage.h"
class SteganographyLinearImage : public SteganographyImage
{
public:
    SteganographyLinearImage(std::string path) : SteganographyImage(path) {}

    void PushText(std::string s) override
    {
        int textsize = s.length();
        if(textsize*2 + 8 > pixels.size())
            throw std::runtime_error("Text to push is too big");
        for(int i = 0; i < 31; ++i)
            SetBit(i, ((textsize & (1 << i)) ? 1 : 0));
            
        for(int i = 0; i < textsize; ++i)
        {
            uint8_t c = s[i];
            for(int j = 0; j < 8; ++j)
                SetBit(i*8+32+j, ((c & (1 << j)) ? 1 : 0));
        }
    }
    std::string GetText() override
    {
        int textsize = 0;
        for(int i = 0; i < 31; ++i)
            textsize |= (GetBit(i) << i);
        std::string ret;
        for(int i = 0; i < textsize; ++i)
        {
            uint8_t c = 0;
            for(int j = 0; j < 8; ++j)
                c |= (GetBit(i*8+32+j) << j);
            ret.push_back(c);
        }
        return ret;
    }
private:
};

#endif //STEGANOGRAPHY_LINEAR_IMAGE_H