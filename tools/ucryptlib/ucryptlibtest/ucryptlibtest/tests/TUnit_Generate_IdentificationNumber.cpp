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

void TUnit_Generate_IdentificationNumber()
{
	std::string expectedValue = "8FLEXeQ9nBGNy2sSKqfe97C4QtATyosbhHLzyvfBDxkGP";
	std::string password = "cytosine stratigraphic megajoules relaxingly dourly timing contractions";
	std::string eMail = "asdf@asdf.de";

	uCrypt::uCryptLib session(eMail, password);
	std::string calculatedValue = session.getIdentificationNumber();

	if(calculatedValue == expectedValue)
	{
		printf("TUnit_Generate_IdentificationNumber: OK\n");
	}
	else
	{
		printf("TUnit_Generate_IdentificationNumber: FAILED\n");
		printf("Expected IdentificationNumber: %s\n", expectedValue);
		printf("Calculated IdentificationNumber: %s\n", calculatedValue);
	}
}

