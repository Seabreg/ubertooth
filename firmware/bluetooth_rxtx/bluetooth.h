/*
 * Copyright 2012 Dominic Spill
 *
 * This file is part of Project Ubertooth.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include "ubertooth.h"

#define CHANNELS 79

u8 bdaddr[6];
u64 access_code;

static const uint8_t BARKER_DISTANCE[] = {
	3,2,3,3,2,1,3,2,2,1,3,2,1,0,2,1,3,3,2,3,3,2,3,3,3,2,3,3,2,1,3,2,
	3,3,2,3,3,2,3,3,3,2,3,3,2,1,3,2,2,3,1,2,3,3,2,3,3,3,2,3,3,2,3,3,
	3,3,2,3,3,2,3,3,3,2,3,3,2,1,3,2,2,3,1,2,3,3,2,3,3,3,2,3,3,2,3,3,
	2,3,1,2,3,3,2,3,3,3,2,3,3,2,3,3,1,2,0,1,2,3,1,2,2,3,1,2,3,3,2,3};

static const uint8_t barker_correct[] = {
	0x0d, 0x0d, 0x72, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d,
	0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x72, 0x0d, 0x72, 0x72, 0x0d, 0x0d,
	0x72, 0x0d, 0x0d, 0x0d, 0x72, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x72,
	0x0d, 0x72, 0x72, 0x0d, 0x0d, 0x72, 0x0d, 0x0d, 0x0d, 0x72, 0x0d,
	0x0d, 0x0d, 0x0d, 0x0d, 0x72, 0x72, 0x72, 0x72, 0x72, 0x0d, 0x72,
	0x72, 0x72, 0x0d, 0x72, 0x72, 0x0d, 0x0d, 0x72, 0x0d, 0x72, 0x0d,
	0x72, 0x72, 0x0d, 0x0d, 0x72, 0x0d, 0x0d, 0x0d, 0x72, 0x0d, 0x0d,
	0x0d, 0x0d, 0x0d, 0x72, 0x72, 0x72, 0x72, 0x72, 0x0d, 0x72, 0x72,
	0x72, 0x0d, 0x72, 0x72, 0x0d, 0x0d, 0x72, 0x0d, 0x72, 0x72, 0x72,
	0x72, 0x72, 0x0d, 0x72, 0x72, 0x72, 0x0d, 0x72, 0x72, 0x0d, 0x0d,
	0x72, 0x0d, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72,
	0x72, 0x72, 0x72, 0x72, 0x0d, 0x72, 0x72};


void precalc(u8 *bdaddr);
u16 next_hop(u32 clkn);
int find_access_code(u8 *idle_rxbuf);