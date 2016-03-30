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
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "uCryptLib.h"

using namespace std;

void TUnit_Base58_Decode()
{
	size_t DECODED_SIZE = uCrypt::uCryptLib::_BASE58_DECODED_SIZE;
	uint8_t expectedValue[] = {24,101,89,215,76,18,203,142,43,188,99,216,79,99,22,182,216,31,7,226,219,46,242,47,245,229,189,138,155,121,234,116,32};
	const char *identificationNumber = "8FLEXeQ9nBGNy2sSKqfe97C4QtATyosbhHLzyvfBDxkGP";
	const size_t identificationNumberLen = strlen(identificationNumber);
	size_t actPos;
	char *decodedBase58 = new char[DECODED_SIZE];
	actPos = DECODED_SIZE;

	uCrypt::uCryptLib::base58_Decode(decodedBase58, &actPos, identificationNumber, identificationNumberLen );
	
	if ( 0 == memcmp(expectedValue, decodedBase58, sizeof(expectedValue)/sizeof(uint8_t)) )
	{
		cout << "TUnit_Base58_Decode: OK" << endl;
	}
	else
	{
		cout << "TUnit_Base58_Decode: FAILED" << endl;

		cout << "Expected Buffer: " << endl;
		for(size_t i = 0; i < sizeof(expectedValue)/sizeof(uint8_t); i++)
		{
			cout << (static_cast<unsigned int>(expectedValue[i]) & 0xff)  << " ";
		}
		cout << endl;

		cout << "Decoded Buffer: " << endl;
		for(size_t i = 0; i < DECODED_SIZE; i++)
		{
			cout << (static_cast<unsigned int>(decodedBase58[i]) & 0xff)  << " ";
		}
		cout << endl;
	}

	delete[] decodedBase58;
}
