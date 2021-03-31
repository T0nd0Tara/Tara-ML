#pragma once
#include "Headers.h"

#ifndef OLC_PGE_APPLICATION
#define OLC_PGE_APPLICATION
#endif
#include "olcPixelGameEngine.h"


inline void pointPrint(olc::PixelGameEngine* pge, int classes, std::vector<std::pair<int, int>>* in, int r = 1) {
	std::vector<olc::Pixel> colors = {olc::RED, olc::BLUE, olc::GREEN, olc::YELLOW, olc::WHITE};

	for (int _class = 0; _class < classes; _class++) {
		olc::Pixel currColor = colors[_class % colors.size()];

		for (int px = 0; px < in->size(); px++) {
			pge->FillCircle((*in)[px].first + (pge->ScreenWidth() >> 1), (*in)[px].second + (pge->ScreenHeight() >> 1), r, currColor);
		}

		in++;
	}

}