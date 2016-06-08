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
#include "sodium.h"


void TUnit_Private_Key()
{
	uint64_t N = 131072; // 2^17
	uint32_t r = 8;
	uint32_t p = 1;

	char buf[] = "cytosine stratigraphic megajoules relaxingly dourly timing contractions";
	char eMail[] = "asdf@asdf.de";
	uint8_t expectedValue[] = {162 ,17 ,61 ,177 ,41 ,119 ,251 ,89 ,162 ,223 ,248 ,115 ,192 ,231 ,220 ,25 ,83, 34 ,32 ,84 ,252 ,34 ,240 ,43 ,141 ,56 ,169 ,154 ,215 ,180 ,33 ,240};
	void *key = NULL;
	uint8_t hash[uCrypt::uCryptLib::_BLAKE2S_OUTBYTES];
	uint8_t prvtKey[uCrypt::uCryptLib::_SECRETKEYBYTES];

	const uint64_t inlen = sizeof(buf)/(sizeof(char));
	
	uCrypt::uCryptLib::blake2s_Hash(hash, buf, key, uCrypt::uCryptLib::_BLAKE2S_OUTBYTES, (inlen-1), 0);

	uint8_t *salt =  reinterpret_cast<uint8_t *>(eMail);
	size_t salt_len = sizeof(eMail)/(sizeof(char));

	uCrypt::uCryptLib::scrypt(hash, uCrypt::uCryptLib::_BLAKE2S_OUTBYTES, salt, (salt_len-1), N, r, p, prvtKey, uCrypt::uCryptLib::_SECRETKEYBYTES );

	if(0 == memcmp(prvtKey, expectedValue, sizeof(expectedValue)/sizeof(uint8_t)) )
	{
		printf("TUnit_Private_Key: OK\n");
	}
	else
	{
		printf("TUnit_Private_Key: FAILED\n");
		printf("Expected Values: ");
		for(size_t i = 0; i < sizeof(expectedValue)/sizeof(uint8_t); i++)
		{
			printf("%2x ", expectedValue[i]);
		}

		printf("\nCalculated Values: ");
		for(size_t i = 0; i < uCrypt::uCryptLib::_SECRETKEYBYTES; i++)
		{
			printf("%2x ", prvtKey[i]);
		}
		printf("\n");
	}

}

