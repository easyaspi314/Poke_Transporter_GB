#include "gameboy_colour.h"
#include "pokemon_party.h"
#include "pokemon.h"
#include "flash_mem.h"
#include "debug_mode.h"
#include "mystery_gift_injector.h"

byte debug_box_data[0x462] = {
	// Preamble
	//0x00, 0x00, 0xFD, 0xFD, 0xFD, 
	// num of Pokemon
	0x14,
	// Pokemon 1-20
	0x02, 0x70, 0x70, 0x70, 0x71, 0x71, 0x70, 0x71, 0x7B, 0x71, 0x71, 0x7C, 0x71, 0x71, 0x71, 0x71, 0x24, 0x24, 0xA5, 0x24, 0xFF, 
	// Pokemon list
	0x02, 0x00, 0x11, 0x04, 0x00, 0x07, 0x03, 0xFF, 0x28, 0x51, 0x00, 0x00, 0x6F, 0xC6, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE6, 0xDE, 0x23, 0x28, 0x00, 0x00, 
	0x70, 0x00, 0x12, 0x04, 0x00, 0x07, 0x03, 0xFF, 0x28, 0x51, 0x00, 0x00, 0x6F, 0xC6, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5D, 0xD8, 0x23, 0x28, 0x00, 0x00, 
	0x70, 0x00, 0x12, 0x04, 0x00, 0x07, 0x03, 0xFF, 0x28, 0x51, 0x00, 0x00, 0x6F, 0xC6, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x13, 0x23, 0x28, 0x00, 0x00, 
	0x70, 0x00, 0x0F, 0x03, 0x00, 0x07, 0x03, 0xFF, 0x28, 0x51, 0x00, 0x00, 0x6F, 0xC6, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0x81, 0x23, 0x28, 0x00, 0x00, 
	0x71, 0x00, 0x14, 0x05, 0x00, 0x07, 0x03, 0x78, 0x6A, 0x00, 0x00, 0x00, 0x6F, 0xC6, 0x00, 0x00, 0x7D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD6, 0x80, 0x1E, 0x00, 0x00, 0x00, 
	0x71, 0x00, 0x15, 0x05, 0x00, 0x07, 0x03, 0x78, 0x6A, 0x00, 0x00, 0x00, 0x6F, 0xC6, 0x00, 0x00, 0x7D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF7, 0x95, 0x1E, 0x00, 0x00, 0x00, 
	0x70, 0x00, 0x13, 0x05, 0x00, 0x07, 0x03, 0xFF, 0x28, 0x51, 0x00, 0x00, 0x6F, 0xC6, 0x00, 0x00, 0x7D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC9, 0xCC, 0x23, 0x28, 0x00, 0x00, 
	0x71, 0x00, 0x11, 0x04, 0x00, 0x07, 0x03, 0x78, 0x6A, 0x00, 0x00, 0x00, 0x6F, 0xC6, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCE, 0x7A, 0x1E, 0x00, 0x00, 0x00, 
	0x7B, 0x00, 0x10, 0x03, 0x00, 0x07, 0x07, 0xFF, 0x21, 0x51, 0x00, 0x00, 0x6F, 0xC6, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5C, 0x84, 0x23, 0x28, 0x00, 0x00, 
	0x71, 0x00, 0x15, 0x06, 0x00, 0x07, 0x03, 0x78, 0x6A, 0x00, 0x00, 0x00, 0x6F, 0xC6, 0x00, 0x00, 0xD8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAC, 0x64, 0x1E, 0x00, 0x00, 0x00, 
	0x71, 0x00, 0x13, 0x05, 0x00, 0x07, 0x03, 0x78, 0x6A, 0x00, 0x00, 0x00, 0x6F, 0xC6, 0x00, 0x00, 0x7D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC4, 0x1D, 0x1E, 0x00, 0x00, 0x00, 
	0x7C, 0x00, 0x12, 0x04, 0x00, 0x07, 0x07, 0x78, 0x6A, 0x00, 0x00, 0x00, 0x6F, 0xC6, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x31, 0x1E, 0x00, 0x00, 0x00, 
	0x71, 0x00, 0x12, 0x04, 0x00, 0x07, 0x03, 0x78, 0x6A, 0x00, 0x00, 0x00, 0x6F, 0xC6, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF6, 0x40, 0x1E, 0x00, 0x00, 0x00, 
	0x71, 0x00, 0x16, 0x06, 0x00, 0x07, 0x03, 0x78, 0x6A, 0x00, 0x00, 0x00, 0x6F, 0xC6, 0x00, 0x00, 0xD8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x97, 0xAA, 0x1E, 0x00, 0x00, 0x00, 
	0x71, 0x00, 0x12, 0x04, 0x00, 0x07, 0x03, 0x78, 0x6A, 0x00, 0x00, 0x00, 0x6F, 0xC6, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x72, 0xE9, 0x1E, 0x00, 0x00, 0x00, 
	0x71, 0x00, 0x14, 0x05, 0x00, 0x07, 0x03, 0x78, 0x6A, 0x00, 0x00, 0x00, 0x6F, 0xC6, 0x00, 0x00, 0x7D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFB, 0xEC, 0x1E, 0x00, 0x00, 0x00, 
	0x24, 0x00, 0x12, 0x04, 0x00, 0x00, 0x02, 0xFF, 0x10, 0x00, 0x00, 0x00, 0x6F, 0xC6, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x35, 0xC2, 0x23, 0x00, 0x00, 0x00, 
	0x24, 0x00, 0x11, 0x04, 0x00, 0x00, 0x02, 0xFF, 0x10, 0x00, 0x00, 0x00, 0x6F, 0xC6, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4D, 0x2A, 0x23, 0x00, 0x00, 0x00, 
	0xA5, 0x00, 0x0E, 0x03, 0x00, 0x00, 0x00, 0xFF, 0x21, 0x27, 0x00, 0x00, 0x6F, 0xC6, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2C, 0xBE, 0x23, 0x1E, 0x00, 0x00, 
	0x24, 0x00, 0x0F, 0x03, 0x00, 0x00, 0x02, 0xFF, 0x10, 0x00, 0x00, 0x00, 0x6F, 0xC6, 0x00, 0x00, 0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x67, 0xE6, 0x23, 0x00, 0x00, 0x00,
	// Trainer names 
	0x80, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	// Nicknames
	0x96, 0x84, 0x84, 0x83, 0x8B, 0x84, 0x50, 0x50, 0x50, 0x50, 0x50, 
	0x96, 0x84, 0x84, 0x83, 0x8B, 0x84, 0x50, 0x50, 0x50, 0x50, 0x50, 
	0x96, 0x84, 0x84, 0x83, 0x8B, 0x84, 0x50, 0x50, 0x50, 0x50, 0x50, 
	0x96, 0x84, 0x84, 0x83, 0x8B, 0x84, 0x50, 0x50, 0x50, 0x50, 0x50, 
	0x8A, 0x80, 0x8A, 0x94, 0x8D, 0x80, 0x50, 0x50, 0x50, 0x50, 0x50, 
	0x8A, 0x80, 0x8A, 0x94, 0x8D, 0x80, 0x50, 0x50, 0x50, 0x50, 0x50, 
	0x96, 0x84, 0x84, 0x83, 0x8B, 0x84, 0x50, 0x50, 0x50, 0x50, 0x50, 
	0x8A, 0x80, 0x8A, 0x94, 0x8D, 0x80, 0x50, 0x50, 0x50, 0x50, 0x50, 
	0x82, 0x80, 0x93, 0x84, 0x91, 0x8F, 0x88, 0x84, 0x50, 0x50, 0x50, 
	0x8A, 0x80, 0x8A, 0x94, 0x8D, 0x80, 0x50, 0x50, 0x50, 0x50, 0x50, 
	0x8A, 0x80, 0x8A, 0x94, 0x8D, 0x80, 0x50, 0x50, 0x50, 0x50, 0x50, 
	0x8C, 0x84, 0x93, 0x80, 0x8F, 0x8E, 0x83, 0x50, 0x50, 0x50, 0x50, 
	0x8A, 0x80, 0x8A, 0x94, 0x8D, 0x80, 0x50, 0x50, 0x50, 0x50, 0x50, 
	0x8A, 0x80, 0x8A, 0x94, 0x8D, 0x80, 0x50, 0x50, 0x50, 0x50, 0x50, 
	0x8A, 0x80, 0x8A, 0x94, 0x8D, 0x80, 0x50, 0x50, 0x50, 0x50, 0x50, 
	0x8A, 0x80, 0x8A, 0x94, 0x8D, 0x80, 0x50, 0x50, 0x50, 0x50, 0x50, 
	0x8F, 0x88, 0x83, 0x86, 0x84, 0x98, 0x50, 0x50, 0x50, 0x50, 0x50, 
	0x8F, 0x88, 0x83, 0x86, 0x84, 0x98, 0x50, 0x50, 0x50, 0x50, 0x50, 
	0x91, 0x80, 0x93, 0x93, 0x80, 0x93, 0x80, 0x50, 0x50, 0x50, 0x50, 
	0x8F, 0x88, 0x83, 0x86, 0x84, 0x98, 0x50, 0x50, 0x50, 0x50, 0x50,
	};
Pokemon_Party::Pokemon_Party(){};

void Pokemon_Party::start_link()
{
	if (IGNORE_LINK_CABLE)
	{
		for (int i = 0; i < BOX_DATA_ARRAY_SIZE; i++)
		{
			box_data_array[i] = debug_box_data[i];
		}
	}
	else
	{
		setup();
		last_error = loop(&box_data_array[0]);
	}
}

int Pokemon_Party::get_last_error()
{
	return last_error;
}

Pokemon Pokemon_Party::get_converted_pkmn(int index)
{
	Pokemon converted_mon;
	converted_mon.load_data(index, box_data_array, game, lang);
	converted_mon.convert_to_gen_three();
	has_new_pkmn = has_new_pkmn || converted_mon.get_is_new();
	return converted_mon;
}

bool Pokemon_Party::get_has_new_pkmn() // If Pokemon is not in the dex
{
	return has_new_pkmn;
}

void Pokemon_Party::set_game(int nGame)
{
	game = nGame;
}

void Pokemon_Party::set_lang(int nLang)
{
	lang = nLang;
}

int Pokemon_Party::get_lang(){
	return lang;
}