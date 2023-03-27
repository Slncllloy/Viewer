#pragma once

#include <vector>
#include <iostream>

#define SUCCESS_ALGR -2
#define SLEEP_ALGR -3

struct StructuringDataElements
{
	int iterator = 0;				// Iteration to elements
	int Cells_into_full_Packet = 0;			// Size rBuffer
	int Recv_count_cells = 0;			// Getting elements

	std::vector<char> rBuffer;			// Buffer to be structuring
	std::vector<char> cBuffer;			// Buffer to continue when rBuffer is filled 
};
int _Queue_(struct StructuringDataElements& alg_Data, std::vector<char>& draw_buffer, std::vector<char>& cycle_buf)
{
	//	Structuring the data to the draw buffer
	//
	//
	//

	// Some elements getting
	if (alg_Data.Recv_count_cells > 0)
	{
		//offset iterator after getting elements
		alg_Data.iterator = alg_Data.iterator + alg_Data.Recv_count_cells;

		// the ellements in buffer more then buffer
		if (alg_Data.iterator > alg_Data.Cells_into_full_Packet)
		{	
			// Erases a vector and copies the elements to the empty vector
			draw_buffer.assign(cycle_buf.begin(), cycle_buf.begin() + alg_Data.Cells_into_full_Packet);

			// Set iterator to start between difference (full buffer - full buffer + getting element)
			alg_Data.iterator = alg_Data.iterator - alg_Data.Cells_into_full_Packet;

			// offset to the received elements
			// getting elements -- in the end of buffer

			cycle_buf.resize(alg_Data.Cells_into_full_Packet + alg_Data.iterator);  
			// offset to the start receved elements
			// getting elements -- in the start of buffer

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

