#ifndef __SQUARE_BOARD_TRANSFORMER__H
#define __SQUARE_BOARD_TRANSFORMER__H

#include "BoardGeometry.h"

namespace game { namespace engine {

template <signed int SIZE>
class square_board_transformer
{
public:
	typedef board_cell_coordinates (*transfromation_function)(const board_cell_coordinates& coord);

	static transfromation_function get_function(unsigned int transformation_number)
	{
		switch(transformation_number)
		{
		case 0:
			return &transfromation_function0;
		case 1:
			return &transfromation_function1;
		case 2:
			return &transfromation_function2;
		case 3:
			return &transfromation_function3;
		case 4:
			return &transfromation_function4;
		case 5:
			return &transfromation_function5;
		case 6:
			return &transfromation_function6;
		case 7:
			return &transfromation_function7;
		}

		return (transfromation_function)NULL;
	}

	static board_cell_coordinates transfromation_function0(const board_cell_coordinates& coord)
	{
		return coord;
	}

	static board_cell_coordinates transfromation_function1(const board_cell_coordinates& coord)
	{
		return board_cell_coordinates(coord.m_y, SIZE - coord.m_x);
	}

	static board_cell_coordinates transfromation_function2(const board_cell_coordinates& coord)
	{
		return board_cell_coordinates(SIZE - coord.m_x, SIZE - coord.m_y);
	}

	static board_cell_coordinates transfromation_function3(const board_cell_coordinates& coord)
	{
		return board_cell_coordinates(SIZE - coord.m_y, coord.m_x);
	}

	static board_cell_coordinates transfromation_function4(const board_cell_coordinates& coord)
	{
		return board_cell_coordinates(coord.m_x, SIZE - coord.m_y);
	}

	static board_cell_coordinates transfromation_function5(const board_cell_coordinates& coord)
	{
		return board_cell_coordinates(SIZE - coord.m_y, SIZE - coord.m_x);
	}

	static board_cell_coordinates transfromation_function6(const board_cell_coordinates& coord)
	{
		return board_cell_coordinates(SIZE - coord.m_x, coord.m_y);
	}

	static board_cell_coordinates transfromation_function7(const board_cell_coordinates& coord)
	{
		return board_cell_coordinates(coord.m_y, coord.m_x);
	}
};

}} //engine, game

#endif