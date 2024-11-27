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

#define GLYPH_WIDTH 50    // ÿ���ַ��Ŀ�ȣ�����ͼƬ������
#define GLYPH_HEIGHT 55   // ÿ���ַ��ĸ߶ȣ�����ͼƬ������
#define CHAR_SPACING 14.2      // ÿ���ַ�֮��ļ��
#define CHARS_PER_ROW 36 // ÿ�е��ַ���
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
			x += GLYPH_WIDTH; // �������ƣ�ֱ���ƶ����
			continue;
		}

		// ӳ�� A-Z
		if (c >= 'A' && c <= 'Z')
		{
			index = c - 'A';
		}
		// ӳ�� 0-9
		else if (c >= '0' && c <= '9')
		{
			index = 26 + (c - '0'); // 0-9 �������� 26 ��ʼ
		}

		if (index != -1)
		{
			rect.x = index * (GLYPH_WIDTH + CHAR_SPACING); // x ����Ϊ�ַ����� * �ַ����

			blitRect(fontTexture, &rect, x, y); // �����ַ�
			x += GLYPH_WIDTH + CHAR_SPACING; // ������һ���ַ��Ļ���λ��
		}
	}
}
