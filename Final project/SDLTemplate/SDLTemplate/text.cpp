/*
Copyright (C) 2015-2018 Parallel Realities

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#define GLYPH_WIDTH 50    // 每个字符的宽度（根据图片调整）
#define GLYPH_HEIGHT 55   // 每个字符的高度（根据图片调整）
#define CHAR_SPACING 14.2      // 每个字符之间的间距
#define CHARS_PER_ROW 36 // 每行的字符数
#include "text.h"

static SDL_Texture* fontTexture;
static char drawTextBuffer[MAX_LINE_LENGTH];

void initFonts(void)
{
	fontTexture = loadTexture("gfx/font.png");
}

void drawText(int x, int y, int r, int g, int b, int align, const  char* format, ...)
{
	int i, len, c;
	SDL_Rect rect;
	va_list args;

	memset(&drawTextBuffer, '\0', sizeof(drawTextBuffer));

	va_start(args, format);
	vsprintf(drawTextBuffer, format, args);
	va_end(args);

	len = strlen(drawTextBuffer);

	switch (align)
	{
	case TEXT_RIGHT:
		x -= (len * GLYPH_WIDTH);
		break;

	case TEXT_CENTER:
		x -= (len * GLYPH_WIDTH) / 2;
		break;

	case TEXT_LEFT:
	default:
		break;
	}

	rect.w = GLYPH_WIDTH;
	rect.h = GLYPH_HEIGHT;
	rect.y = 0;

	SDL_SetTextureColorMod(fontTexture, r, g, b);

	for (i = 0; i < len; i++)
	{
		c = drawTextBuffer[i];

		int index = -1;

		if (c == ' ')
		{
			x += GLYPH_WIDTH; // 跳过绘制，直接移动光标
			continue;
		}

		// 映射 A-Z
		if (c >= 'A' && c <= 'Z')
		{
			index = c - 'A';
		}
		// 映射 0-9
		else if (c >= '0' && c <= '9')
		{
			index = 26 + (c - '0'); // 0-9 的索引从 26 开始
		}

		if (index != -1)
		{
			rect.x = index * (GLYPH_WIDTH + CHAR_SPACING); // x 坐标为字符索引 * 字符宽度

			blitRect(fontTexture, &rect, x, y); // 绘制字符
			x += GLYPH_WIDTH + CHAR_SPACING; // 更新下一个字符的绘制位置
		}
	}
}
