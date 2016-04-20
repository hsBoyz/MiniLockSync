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
#include <string.h>
#include <iostream>

#include "uCryptLib.h"

#define BUFFER_MAX 256

using namespace std;

void TUnit_Base58_Encode()
{
	uint8_t identificationNumber[] = {24,101,89,215,76,18,203,142,43,188,99,216,79,99,22,182,216,31,7,226,219,46,242,47,245,229,189,138,155,121,234,116,32};
	char *expectedValue = "8FLEXeQ9nBGNy2sSKqfe97C4QtATyosbhHLzyvfBDxkGP";
	char encodedBase58[BUFFER_MAX];

	size_t identificationNumberLen = sizeof(identificationNumber)/sizeof(uint8_t);
	size_t encB58Len = sizeof(encodedBase58)/sizeof(char);
	size_t *encB58sz = &encB58Len;

	uCrypt::uCryptLib::base58_Encode(encodedBase58, encB58sz, identificationNumber, identificationNumberLen);

	if(0 == memcmp(encodedBase58, expectedValue, strlen(expectedValue)) )
	{
		cout << "TUnit_Base58_Encode: OK" << endl;
	}
	else
	{
		cout << "TUnit_Base58_Encode: FAILED" << endl;
		cout << "encoded Value: " << encodedBase58 << endl;
		cout << "expected Value " << expectedValue << endl;
	}
}
