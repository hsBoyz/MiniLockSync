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

void TUnit_Uninitialized_State()
{
	uCrypt::uCryptLib session;

	uint8_t resultDecrypt = session.DecryptFile("", "");

	uint8_t resultEncrypt = session.EncryptFile("", "", NULL, 0);

	if(resultDecrypt != 0xff)
		std::cout << "Error: Function DecryptFile() did not detect the uninitialized state" << std::endl;

	else if(resultEncrypt != 0xff)
		std::cout << "Error: Function EncryptFile() did not detect the uninitialized state" << std::endl;

	else
		std::cout << "TUnit_Uninitialized_State: OK" << std::endl;

}
