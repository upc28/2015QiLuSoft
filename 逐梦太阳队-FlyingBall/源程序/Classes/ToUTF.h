#ifndef _TOUTF_H_
#define _TOUTF_H_
#include "cocos2d.h"

class ToUTF
{
public:
	void WStrToUTF8(std::string& dest, const std::wstring& src){
		dest.clear();

		for (size_t i = 0; i < src.size(); i++){
			wchar_t w = src[i];
			if (w <= 0x7f)
				dest.push_back((char)w);
			else if (w <= 0x7ff)
			{
				dest.push_back(0xc0 | ((w >> 6) & 0x1f));
				dest.push_back(0x80 | (w & 0x3f));
			}
			else if (w <= 0xffff)
			{
				dest.push_back(0xe0 | ((w >> 12) & 0x0f));
				dest.push_back(0x80 | ((w >> 6) & 0x3f));
				dest.push_back(0x80 | (w & 0x3f));
			}
			else if (sizeof(wchar_t) > 2 && w <= 0x10ffff)
			{
				dest.push_back(0xf0 | ((w >> 18) & 0x07)); // wchar_t 4-bytes situation  
				dest.push_back(0x80 | ((w >> 12) & 0x3f));
				dest.push_back(0x80 | ((w >> 6) & 0x3f));
				dest.push_back(0x80 | (w & 0x3f));
			}
			else
				dest.push_back('?');
		}
	}
	std::string WStrToUTF8(const std::wstring& str)
	{
		std::string result;
		WStrToUTF8(result, str);
		return result;

	}
};


#endif 