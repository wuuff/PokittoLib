#pragma once

//
// Copyright (C) 2018 Pharap (@Pharap)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

//
// Tiles created by Pharap (https://github.com/Pharap)
// Penguin tile created by Vampirics (https://github.com/vampirics)
//

namespace Images
{
	constexpr const static uint8_t TileFrameWidth = 8;
	constexpr const static uint8_t TileFrameHeight = 8;

	const unsigned char Tiles[] PROGMEM =
	{
		TileFrameWidth, TileFrameHeight,

		// Frame 0 - Number 0
		0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E,

		// Frame 1 - Number 1
		0x7E, 0xFF, 0xFF, 0xBB, 0x81, 0xBF, 0xFF, 0x7E,

		// Frame 2 - Number 2
		0x7E, 0xFF, 0xBB, 0x9D, 0xAD, 0xB3, 0xFF, 0x7E,

		// Frame 3 - Number 3
		0x7E, 0xFF, 0xDB, 0xBD, 0xB5, 0xB5, 0xCB, 0x7E,

		// Frame 4 - Number 4
		0x7E, 0xFF, 0xCF, 0xD7, 0xDB, 0x83, 0xDF, 0x7E,

		// Frame 5 - Number 5
		0x7E, 0xFF, 0xD1, 0xB5, 0xB5, 0xCD, 0xFF, 0x7E,

		// Frame 6 - Number 6
		0x7E, 0xFF, 0xC3, 0xAD, 0xAD, 0xDB, 0xFF, 0x7E,

		// Frame 7 - Number 7
		0x7E, 0xFF, 0xFD, 0x9D, 0xE5, 0xF9, 0xFF, 0x7E,

		// Frame 8 - Number 8
		0x7E, 0xFF, 0xCB, 0xB5, 0xB5, 0xCB, 0xFF, 0x7E,

		// Frame 9 - Number 9
		0x7E, 0xFF, 0xF3, 0xAD, 0xAD, 0xC3, 0xFF, 0x7E,

		// Frame 10 - Blank
		0x7E, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x7E,

		// Frame 11 - Marked
		0x7E, 0xFF, 0xE7, 0xC3, 0xC3, 0xE7, 0xFF, 0x7E,

		// Frame 12 - Classic Mine
		0x00, 0x5A, 0x34, 0x7A, 0x7E, 0x3C, 0x5A, 0x00,

		// Frame 13 - Modern Mine
		0x00, 0x3C, 0x42, 0x5A, 0x5A, 0x42, 0x3C, 0x00,

		// Frame 14 - Turtle Mine
		0x00, 0x04, 0x6C, 0x30, 0x38, 0x30, 0x60, 0x00,

		// Frame 15 - Cactus Mine
		0xFF, 0xF3, 0x13, 0x8F, 0x8F, 0x13, 0xF3, 0xFF,

		// Frame 16 - Penguin Mine
		0x00, 0x14, 0x6E, 0x91, 0x65, 0x82, 0x7C, 0x00		
	};
}