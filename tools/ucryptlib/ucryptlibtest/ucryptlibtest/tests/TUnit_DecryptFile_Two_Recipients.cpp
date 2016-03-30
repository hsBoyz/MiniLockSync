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
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <iomanip>

#include "uCryptLib.h"


void TUnit_DecryptFile_Two_Recipients()
{
	std::string path = "tests/decryption_tests/";
	std::string fileName = "two_recipients_file.encrypted";
	std::string fileNameDecrypted = path + "two_recipients_file";
	std::string fileNameOriginal = path + "two_recipients_file.original";

	size_t szOutBytes = uCrypt::uCryptLib::_BLAKE2S_OUTBYTES;
	uint8_t *hashOriginalFile = new uint8_t[szOutBytes];
	uint8_t *hashDecryptedFile = new uint8_t[szOutBytes];
	void *key = NULL;


	std::ifstream originalFileStream(fileNameOriginal, std::ios::in | std::ios::binary | std::ios::ate);
	if(originalFileStream.is_open())
	{
		std::streampos originalFileSize = originalFileStream.tellg();
		size_t szOriginalFileSize = originalFileSize;
		uint8_t* memblockOriginalFile = new uint8_t[szOriginalFileSize];
		originalFileStream.seekg(0, std::ios::beg);
		originalFileStream.read((char*)memblockOriginalFile, originalFileSize);
		originalFileStream.close();

		const uint64_t inlen = szOriginalFileSize;

		uCrypt::uCryptLib::blake2s_Hash(hashOriginalFile, memblockOriginalFile, key, szOutBytes, inlen, 0);
	}
	else
		std::cerr << "FileStreamError in TestCase: Could not open " << fileNameOriginal << std::endl;

	uCrypt::uCryptLib session("asdf@asdf.de","cytosine stratigraphic megajoules relaxingly dourly timing contractions");

	clock_t t = clock();
	uint8_t result = session.DecryptFile(fileName,path);
	t = clock() - t;
	std::cout << "Time to decrypt file " << fileName << ": ";
	std::cout << std::fixed << std::setprecision(3) << ((float)t)/CLOCKS_PER_SEC << " (seconds) " << std::endl;

	if(result == 1)
		std::cout << "ERROR: General Encryption Failure" << std::endl;
	else if(result == 2)
		std::cout << "ERROR: General Decryption Failure" << std::endl;
	else if(result == 3)
		std::cout << "ERROR: General JSON Parsing Failure" << std::endl;
	else if(result == 4)
		std::cout << "ERROR: Invalid Header Version" << std::endl;
	else if(result == 5)
		std::cout << "ERROR: Invalid Sender ID" << std::endl;
	else if(result == 6)
		std::cout << "ERROR: Invalid Recipient ID" << std::endl;
	else if(result == 7)
		std::cout << "ERROR: Hash of File is corrupt" << std::endl;
	else if(result == 0xff)
		std::cout << "ERROR: General Encryption Failure" << std::endl;

	std::ifstream decryptedFileStream(fileNameDecrypted, std::ios::in | std::ios::binary | std::ios::ate);
	if(decryptedFileStream.is_open())
	{
		std::streampos decryptedFileSize = decryptedFileStream.tellg();
		size_t szDecryptedFileSize = decryptedFileSize;
		uint8_t* memblockDecryptedFile = new uint8_t[szDecryptedFileSize];
		decryptedFileStream.seekg(0, std::ios::beg);
		decryptedFileStream.read((char*)memblockDecryptedFile, decryptedFileSize);
		decryptedFileStream.close();

		const uint64_t inlen = szDecryptedFileSize;

		uCrypt::uCryptLib::blake2s_Hash(hashDecryptedFile, memblockDecryptedFile, key, szOutBytes, inlen, 0);
	}
	else
		std::cerr << "FileStreamError in TestCase: Could not open " << fileNameOriginal << std::endl;


	if( 0 == memcmp(hashOriginalFile, hashDecryptedFile, sizeof(hashOriginalFile)/sizeof(uint8_t)) )
	{
		printf("TUnit_DecryptFile_Two_Recipients: OK\n");
	}
	else
	{
		printf("TUnit_DecryptFile_Two_Recipients: FAILED\n");
		printf("Expected Values: ");
		for(size_t i = 0; i < sizeof(hashOriginalFile)/sizeof(uint8_t); i++)
		{
			printf("%2x ", hashOriginalFile[i]);
		}

		printf("\nCalculated Values: ");
		for(size_t i = 0; i < sizeof(hashDecryptedFile)/sizeof(uint8_t); i++)
		{
			printf("%2x ", hashDecryptedFile[i]);
		}
		printf("\n");
	}

	delete[] hashOriginalFile;
	delete[] hashDecryptedFile;
}

