#pragma once

#include <vector>
#include <iostream>

#define SUCCESS_ALGR -2
#define SLEEP_ALGR -3

struct AlgorithmData
{
	int iterator = 0;
	int Cells_into_full_Packet = 0;
	int Recv_count_cells = 0;

};
int _Queue_(struct AlgorithmData& alg_Data, std::vector<char>& to_sort_buf, std::vector<char>& cycle_buf)
{
	if (alg_Data.Recv_count_cells > 0)
	{
		alg_Data.iterator = alg_Data.iterator + alg_Data.Recv_count_cells;

		if (alg_Data.iterator > alg_Data.Cells_into_full_Packet)
		{
			to_sort_buf.assign(cycle_buf.begin(), cycle_buf.begin() + alg_Data.Cells_into_full_Packet);

			alg_Data.iterator = alg_Data.iterator - alg_Data.Cells_into_full_Packet;

			cycle_buf.resize(alg_Data.Cells_into_full_Packet + alg_Data.iterator);
			cycle_buf.resize(alg_Data.Cells_into_full_Packet * 2);

			return  SUCCESS_ALGR;
		}
		if (alg_Data.iterator == alg_Data.Cells_into_full_Packet)
		{
			to_sort_buf.assign(cycle_buf.begin(), cycle_buf.begin() + alg_Data.Cells_into_full_Packet);
			cycle_buf.resize(alg_Data.Cells_into_full_Packet);
			cycle_buf.resize(alg_Data.Cells_into_full_Packet * 2);

			alg_Data.iterator = 0;

			return SUCCESS_ALGR;
		}
	}
	return SLEEP_ALGR;
}

