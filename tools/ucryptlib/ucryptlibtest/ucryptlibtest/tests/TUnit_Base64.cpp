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

#include <iostream>
#include <cstdint>

#include "uCryptLib.h"

using namespace std;

void TUnit_Base64()
{
    string msg = "the quick brown fox jumps over the lazy dog";
	string expectedValue = "dGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZw==";
    unsigned int msgLen = msg.size();
    uint8_t *bytesToEncode = new uint8_t[msgLen];
    
    for(int i = 0; i < msgLen; i++) 
        bytesToEncode[i] = msg[i];

	string encMsg = uCrypt::uCryptLib::base64_Encode(bytesToEncode, msgLen);
    string decMsg = uCrypt::uCryptLib::base64_Decode(encMsg);

	if(encMsg == expectedValue && decMsg == msg)
	{
		cout << "TUnit_Base64: OK" << endl;
	}
	else
	{
		cout << "TUnit_Base64: FAILURE" << endl;
		cout << "Original Message: " << msg << endl;
		cout << "Expected Value: " << expectedValue << endl;
		cout << "Encoded Message: " << encMsg << endl;
		cout << "Decoded Message: " << decMsg << endl;
	}

	delete[] bytesToEncode;
}
    
