#ifndef ENGINE_FONT_H
#define ENGINE_FONT_H

#include "resources/Resource.h"
#include "resources/image/Image.h"

namespace urchin
{
	
	struct FontParameters
	{
		int fontSize;
		Vector3<float> fontColor;
	};

	struct Glyph
	{ //glyph is a letter
		int width;
		int height;
		int shift;
		unsigned char *buf;
	};

	class Font : public Resource
	{
		public:
			Font(Image *, Glyph *, unsigned int, unsigned int, unsigned int);
			~Font();
		
			const Glyph &getGlyph(unsigned char i) const;
			unsigned int getTextureID() const;
			unsigned int getDimensionTexture() const;
			unsigned int getSpaceBetweenLetters() const;
			unsigned int getSpaceBetweenLines() const;
			unsigned int getHeight() const;
		
		private:
			Image *texAlphabet;
		
			Glyph *glyph;
			unsigned int spaceBetweenLetters, spaceBetweenLines, height;
	};

}

#endif
