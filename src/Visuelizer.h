#pragma once
#include "Headers.h"

#ifndef OLC_PGE_APPLICATION
#define OLC_PGE_APPLICATION
#endif
#include "olcPixelGameEngine.h"


inline void pointPrint(olc::PixelGameEngine* pge, int classes, std::vector<std::pair<int, int>>* in, int r = 1, float scroll = 1.0f, olc::vf2d xyOff = {0 ,0}) {
	std::vector<olc::Pixel> colors = {olc::RED, olc::BLUE, olc::GREEN, olc::YELLOW, olc::WHITE, olc::MAGENTA, olc::CYAN};

	if (scroll == 0.0f)
		return;


	//if (scroll >= 0.25f)
	r = round((float)r * sqrtf(scroll));

	for (int _class = 0; _class < classes; _class++) {
		olc::Pixel currColor = colors[_class % colors.size()];

		for (int px = 0; px < in->size(); px++) {
			float x = (float)((*in)[px].first) + xyOff.x;
			float y = (float)((*in)[px].second) + xyOff.y;

			pge->FillCircle(round(x * scroll) + (pge->ScreenWidth() >> 1),
							round(y * scroll) + (pge->ScreenHeight() >> 1),
							r, currColor);
		}

		in++;
	}

}

inline void drawPoints(int screenSize, int pixelSize, int _classes, std::vector<std::pair<int, int>>* in) {


	class Visuelizer : public olc::PixelGameEngine {
	public:
		Visuelizer(int _c, std::vector<std::pair<int, int>>* _vec) {
			classes = _c;
			vec = _vec;
			sAppName = "Visuelizer";
		}
	protected:
		int classes;
		std::vector<std::pair<int, int>>* vec = new std::vector<std::pair<int, int>>[classes];

		olc::vf2d xyOff = { 0.0f, 0.0f };
		float scrollOffset = 1.0f;
		bool OnUserCreate() override {
			return true;
		}
		bool OnUserUpdate(float elapsedTime) override {
			Clear(0);


			if (GetKey(olc::W).bHeld) xyOff.y += 1000.0f * elapsedTime / scrollOffset;
			if (GetKey(olc::A).bHeld) xyOff.x += 1000.0f * elapsedTime / scrollOffset;
			if (GetKey(olc::S).bHeld) xyOff.y -= 1000.0f * elapsedTime / scrollOffset;
			if (GetKey(olc::D).bHeld) xyOff.x -= 1000.0f * elapsedTime / scrollOffset;

			if (GetKey(olc::Q).bPressed) scrollOffset *= 1.5f;
			if (GetKey(olc::E).bPressed) scrollOffset /= 1.5f;

			if (GetKey(olc::ESCAPE).bPressed) return false;

			pointPrint(this, classes, vec, 2, scrollOffset, xyOff);
			return true;
		}
	};

	Visuelizer vis(_classes, in);
	if (vis.Construct(screenSize, screenSize, pixelSize, pixelSize))
		vis.Start();

}