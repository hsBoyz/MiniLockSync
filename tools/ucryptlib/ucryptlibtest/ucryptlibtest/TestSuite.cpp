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

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <BaseTsd.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <ctime>

#include "uCryptLib.h"

#include "TUnit_BLAKE2.h"
#include "TUnit_Base58_Decode.h"
#include "TUnit_Base58_Encode.h"
#include "TUnit_Base64.h"
#include "TUnit_Calculate_Bit_Entropy.h"
#include "TUnit_Uninitialized_State.h"
#include "TUnit_Generate_IdentificationNumber.h"
#include "TUnit_Public_Key.h"
#include "TUnit_Private_Key.h"
#include "TUnit_DecryptFile_Tux.h"
#include "TUnit_DecryptFile_Two_Recipients.h"
#include "TUnit_DecryptFile_random_31415KB.h"
#include "TUnit_DecryptFile_random_10MB.h"
#include "TUnit_EncryptFile_random_10MB.h"
#include "TUnit_EncryptFile_random_31415KB.h"
#include "TUnit_EncryptFile_Two_Recipients.h"

#include "TUnit_EncryptFile_Benchmark.h"

#pragma comment (lib, "libsodium.lib")


void TUnit_Start_Test_Case(void (*f)(void), std::string TestCaseName)
{
	std::cout << "---------------------------------------------------------" << std::endl;
	std::cout << "Starting Test Case " << TestCaseName << "..." << std::endl;
	
	clock_t t = clock();
	f();
	t = clock() - t;

	std::cout << "Ending Test Case. Time to execute: ";
	std::cout << std::fixed << std::setprecision(3) << ((float)t)/CLOCKS_PER_SEC;
	std::cout << " (seconds)\n";
	std::cout << "---------------------------------------------------------\n\n" << std::endl;
}

int main()
{
	//Modular Tests
	TUnit_Start_Test_Case(TUnit_Blake2, "TUnit_Blake2");
	TUnit_Start_Test_Case(TUnit_Base58_Decode, "TUnit_Base58_Decode");
	TUnit_Start_Test_Case(TUnit_Base58_Encode, "TUnit_Base58_Encode");
	TUnit_Start_Test_Case(TUnit_Base64, "TUnit_Base64");
	TUnit_Start_Test_Case(TUnit_Uninitialized_State, "TUnit_Uninitialized_State");
	TUnit_Start_Test_Case(TUnit_Calculate_Bit_Entropy, "TUnit_Calculate_Bit_Entropy");
	TUnit_Start_Test_Case(TUnit_Private_Key, "TUnit_Private_Key");
	TUnit_Start_Test_Case(TUnit_Public_Key, "TUnit_Public_Key");
	TUnit_Start_Test_Case(TUnit_Generate_IdentificationNumber, "TUnit_Generate_IdentificationNumber");

	//Decryption Tests
	TUnit_Start_Test_Case(TUnit_DecryptFile_Tux, "TUnit_DecryptFile_Tux");
	TUnit_Start_Test_Case(TUnit_DecryptFile_Two_Recipients, "TUnit_DecryptFile_Two_Recipients");
	TUnit_Start_Test_Case(TUnit_DecryptFile_random_10MB, "TUnit_DecryptFile_random_10MB");
	TUnit_Start_Test_Case(TUnit_DecryptFile_random_31415KB, "TUnit_DecryptFile_random_31415KB");

	//Encryption Tests
	TUnit_Start_Test_Case(TUnit_EncryptFile_random_10MB, "TUnit_EncryptFile_random_10MB");
	TUnit_Start_Test_Case(TUnit_EncryptFile_random_31415KB, "TUnit_EncryptFile_random_31415KB");
	TUnit_Start_Test_Case(TUnit_EncryptFile_Two_Recipients, "TUnit_EncryptFile_Two_Recipients");

	// Benchmark
	TUnit_Start_Test_Case(TUnit_EncryptFile_Benchmark, "TUnit_EncryptFile_Benchmark");

	return 0;
}