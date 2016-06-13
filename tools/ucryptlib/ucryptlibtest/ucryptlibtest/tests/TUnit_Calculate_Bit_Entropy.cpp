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

void TUnit_Calculate_Bit_Entropy()
{
	std::string strCorrect = "cytosine stratigraphic megajoules relaxingly dourly timing contractions";
	std::string strIncorrect = "cytosine stratigraphic";

	double entropy_ar1 = uCrypt::uCryptLib::getBitEntropy("Die Wuerde des Menschen ist unantastbar.");
	double entropy_correct = uCrypt::uCryptLib::getBitEntropy("cytosine stratigraphic megajoules relaxingly dourly timing contractions");
	double entropy_incorrect = uCrypt::uCryptLib::getBitEntropy("cytosine stratigraphic");

	if(entropy_correct * strCorrect.size() < 258)
	{
		std::cout << "TUnit_Calculate_Bit_Entropy: Failure" << std::endl;
		std::cout << "Bit Entropy Calculated from \"" << strCorrect << "\" is " << entropy_correct * strCorrect.size() << std::endl;
	}
	else if(entropy_incorrect * strIncorrect.size() > 258)
	{
		std::cout << "TUnit_Calculate_Bit_Entropy: Failure" << std::endl;
		std::cout << "Bit Entropy Calculated from \"" << strIncorrect << "\" is " << entropy_incorrect * strIncorrect.size() << std::endl;
	}
	else
		std::cout << "TUnit_Calculate_Bit_Entropy: OK" << std::endl;
}
