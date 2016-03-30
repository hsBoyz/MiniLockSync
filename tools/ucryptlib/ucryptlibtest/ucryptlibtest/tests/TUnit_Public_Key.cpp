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
#include <iostream>
#include <vector>

#include "uCryptLib.h"
#include "sodium.h"


void TUnit_Public_Key()
{
	uint8_t expectedValue[] = {24, 101, 89, 215, 76, 18, 203, 142, 43, 188, 99, 216, 79, 99, 22, 182, 216, 31, 7, 226, 219, 46, 242, 47, 245, 229, 189, 138, 155, 121, 234, 116};
	uint64_t N = 131072; // 2^17
	uint32_t r = 8;
	uint32_t p = 1;

	char buf[] = "cytosine stratigraphic megajoules relaxingly dourly timing contractions";
	char eMail[] = "asdf@asdf.de";

	void *key = NULL;
	uint8_t hash[uCrypt::uCryptLib::_BLAKE2S_OUTBYTES];
	uint8_t prvtKey[uCrypt::uCryptLib::_SECRETKEYBYTES];

	const uint64_t inlen = sizeof(buf)/(sizeof(char));
	
	uCrypt::uCryptLib::blake2s_Hash(hash, buf, key, uCrypt::uCryptLib::_BLAKE2S_OUTBYTES, (inlen-1), 0);

	uint8_t *salt =  reinterpret_cast<uint8_t *>(eMail);
	size_t salt_len = sizeof(eMail)/(sizeof(char));

	uCrypt::uCryptLib::scrypt(hash, uCrypt::uCryptLib::_BLAKE2S_OUTBYTES, salt, (salt_len-1), N, r, p, prvtKey, uCrypt::uCryptLib::_SECRETKEYBYTES );
	
	uint8_t pubKey[uCrypt::uCryptLib::_PUBLICKEYBYTES];

	crypto_scalarmult_curve25519_base(pubKey,prvtKey);

	if(0 == memcmp(pubKey, expectedValue, sizeof(expectedValue)/sizeof(uint8_t)) )
	{
		printf("TUnit_Public_Key: OK\n");
	}
	else
	{
		printf("TUnit_Public_Key: FAILED\n");
		printf("Expected Values: ");
		for(size_t i = 0; i < sizeof(expectedValue)/sizeof(uint8_t); i++)
		{
			printf("%2x ", expectedValue[i]);
		}

		printf("\nCalculated Values: ");
		for(size_t i = 0; i < uCrypt::uCryptLib::_PUBLICKEYBYTES; i++)
		{
			printf("%2x ", pubKey[i]);
		}
		printf("\n");
	}
}

