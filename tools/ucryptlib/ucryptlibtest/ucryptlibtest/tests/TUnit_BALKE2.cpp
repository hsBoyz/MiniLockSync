/*-	This file is part of µCryptLib. A Cryptography Library that's
 *  built to make encryption and decryption as easy and fast as
 *  possible for third party tools.
 *
 *  Copyright (C) 2015  Michael Römer
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "uCryptLib.h"

void TUnit_Blake2()
{
	char buf[] = "cytosine stratigraphic megajoules relaxingly dourly timing contractions";
	uint8_t expectedValue[] = {231, 160, 194, 129, 121, 20, 165, 158, 53, 201, 60, 55, 255, 219, 98, 176, 44, 173, 11, 197, 221, 157, 244, 134, 245, 76, 30, 207, 179, 0, 60, 159 };
	
	size_t szOutBytes = uCrypt::uCryptLib::_BLAKE2S_OUTBYTES;
	void *key = NULL;
	uint8_t *hash = new uint8_t[szOutBytes];

	const uint64_t inlen = sizeof(buf)/(sizeof(char));

	uCrypt::uCryptLib::blake2s_Hash(hash, buf, key, szOutBytes, (inlen-1), 0);

	if( 0 == memcmp(hash, expectedValue, sizeof(expectedValue)/sizeof(uint8_t)) )
	{
		printf("TUnit_BLAKE2: OK\n");
	}
	else
	{
		printf("TUnit_BLAKE2: FAILED\n");
		printf("Expected Values: ");
		for(size_t i = 0; i < sizeof(expectedValue)/sizeof(uint8_t); i++)
		{
			printf("%2x ", expectedValue[i]);
		}

		printf("\nCalculated Values: ");
		for(size_t i = 0; i < szOutBytes; i++)
		{
			printf("%2x ", hash[i]);
		}
		printf("\n");
	}

	delete[] hash;
}
