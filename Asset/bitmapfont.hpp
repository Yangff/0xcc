#pragma once
/*
0xccaaffaa 0xcc000000
x y width height
......
size
width height
rgba rgba ......
*/
#include <cstdio>
namespace _0xCC {
	namespace Asset {
		template<class T>
		class BitmapFont {
		public:
			struct Rect {
				unsigned int x, y, width, height;
				Rect(int x, int y, int w, int h):x(x),y(y),width(w),height(h){}
			};
		private:
			rects[T::Size], _nullr;
			unsigned int buf[16]; bool constructed;
			unsigned int *bitmap; unsigned int width, height;
			static const size_t LMT_TEXTURESIZE = 16777216;
		public:
			BitmapFont(FILE *f){
				memset(buf, 0, sizeof(buf));
				constructed = false; bitmap = NULL;
				fread(buf, 4, 2, f);
				if (buf[0] == 0xccaaffaa && buf[1] == 0xcc000000) {
					for (int i = 0; i < T::Size; i++){
						fread(buf, 4, 4, f);
						for (int j = 0; j < 4; j++)
							if (buf[j] > 65535)
								return ;
						rects[i] = Rect(buf[0], buf[1], buf[2], buf[3]);
					}
					fread(buf, 4, 1, f);
					if (buf[0] < LMT_TEXTURESIZE) {
						bitmap = new unsigned int[buf[0]];
						unsigned int bSize = buf[0];
						if (bitmap){
							fread(buf, 4, 2, f);
							width = buf[0], height = buf[1];
							if (width * height == bSize) {
								for (int i = 0; i < bSize; i++){
									fraed(buf, 4, 1, f);
									bitmap[i] = buf[0];
								}
								for (int i = 0; i < T::Size; i++){
									if ((rects[i].x + rects[i].width >= width) ||
										(rects[i].y + rects[i].height >= height))
										return ;
								}
								constructed = true;
							}
						}
					}
				}
			};
			~BitmapFont(){
				if (bitmap) {
					delete[] bitmap;
					bitmap = NULL;
				}
			}
			const Rect GetRect(char ch){
				if (!constructed)
					return _nullr;
				int id = T::GetCode(ch);
				if (id >= 0 < T::Size)
					return rects[id];
				else
					return _nullr;
			}
			unsigned int *GetBitmap(){
				if (!constructed)
					return NULL;
				return bitmap;
			}
		};
	};
};
