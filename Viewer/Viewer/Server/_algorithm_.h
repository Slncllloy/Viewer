#pragma once

#include <vector>
#include <iostream>

#define SUCCESS_ALGR -2				//todo: (?)delete
#define SLEEP_ALGR -3				//todo: (?)delete

// todo: add .cpp, why compilig without inline void

struct StructuringDataElements
{
	int iterator = 0;				// Iteration to elements
	int Cells_into_full_Packet = 0;			// Size rBuffer
	int Recv_count_cells = 0;			// Getting elements

	std::vector<char> rBuffer;			// Buffer to be structuring (reade buf)
	std::vector<char> cBuffer;			// Buffer to continue when rBuffer is filled (cycle)
};
int _Queue_(struct StructuringDataElements& alg_Data, std::vector<char>& draw_buffer, std::vector<char>& cycle_buf)
{
	//	Structuring the data to the draw buffer (rBuffer)
	//
	//	When we get some ellements we fill it in to cBuffer to the moment of overflow
	//	Overflow elements filling to cBuffer
	//	Copy cBuffer to rBuffer

	// Some elements getting
	if (alg_Data.Recv_count_cells > 0)
	{
		//offset iterator after getting elements
		alg_Data.iterator = alg_Data.iterator + alg_Data.Recv_count_cells;

		// the ellements in buffer (rBuffer) more then buffer
		if (alg_Data.iterator > alg_Data.Cells_into_full_Packet)
		{
			// Erases a vector and copies the elements to the empty buffer (cBuffer >> rBuffer)
			draw_buffer.assign(cycle_buf.begin(), cycle_buf.begin() + alg_Data.Cells_into_full_Packet);

			// Set iterator to start between difference 
			// full buffer(rBuffer) - full buffer(rBuffer) + getting element
			alg_Data.iterator = alg_Data.iterator - alg_Data.Cells_into_full_Packet;

			// offset to the received elements
			// First getting elements -- in the end of buffer (cBuffer)
			cycle_buf.resize(alg_Data.Cells_into_full_Packet + alg_Data.iterator);

			// offset to the start receved elements
			// Last getting elements -- in the start of buffer (cBuffer)
			cycle_buf.resize(alg_Data.Cells_into_full_Packet * 2);

			return  SUCCESS_ALGR;
		}
		// the ellements in buffer == buffer
		if (alg_Data.iterator == alg_Data.Cells_into_full_Packet)
		{
			draw_buffer.assign(cycle_buf.begin(), cycle_buf.begin() + alg_Data.Cells_into_full_Packet);
			cycle_buf.resize(alg_Data.Cells_into_full_Packet);
			cycle_buf.resize(alg_Data.Cells_into_full_Packet * 2);

			alg_Data.iterator = 0;

			return SUCCESS_ALGR;
		}
	}
	return SLEEP_ALGR;
}