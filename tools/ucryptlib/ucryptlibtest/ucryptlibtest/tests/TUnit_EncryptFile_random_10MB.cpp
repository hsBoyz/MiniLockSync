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
#include <vector>
#include <ctime>
#include <iomanip>

#include "sodium.h"
#include "uCryptLib.h"


void TUnit_EncryptFile_random_10MB()
{
	std::string path = "tests/encryption_tests/";
	std::string fileName = "random_10MB";
	std::string fileExtensionEncrypted = ".encrypted";

	size_t szOutBytes = uCrypt::uCryptLib::_BLAKE2S_OUTBYTES;
	uint8_t *hashOriginalFile = new uint8_t[szOutBytes];
	uint8_t *hashDecryptedFile = new uint8_t[szOutBytes];

	size_t fileContentRandomSize = 10000000; // 10*10^6 Bytes
	uint8_t *fileContentRandom = new uint8_t[fileContentRandomSize];
	randombytes_buf(fileContentRandom, fileContentRandomSize);

	uCrypt::uCryptLib::blake2s_Hash(hashOriginalFile, fileContentRandom, NULL, szOutBytes, fileContentRandomSize, 0);

	remove((path + fileName).c_str());
	std::ofstream originalFileStream;
	originalFileStream.open(path + fileName, std::ios::binary | std::ios::out | std::ios_base::app);
	if(originalFileStream.is_open())
		originalFileStream.write((char*)fileContentRandom, fileContentRandomSize);
	else
		std::cerr << "\nError on Opening File: " << (path + fileName) << std::endl;
	originalFileStream.close();

	std::string recipients[] = {"8FLEXeQ9nBGNy2sSKqfe97C4QtATyosbhHLzyvfBDxkGP"};
	uint8_t numberOfRecipients = sizeof(recipients)/sizeof(recipients[0]);
	uCrypt::uCryptLib session("asdf@asdf.de","cytosine stratigraphic megajoules relaxingly dourly timing contractions");
	
	clock_t t = clock();
	uint8_t res = session.EncryptFile(fileName,path,recipients,numberOfRecipients);
	t = clock() - t;
	std::cout << "Time to encrypt file " << fileName << ": ";
	std::cout << std::fixed << std::setprecision(3) << ((float)t)/CLOCKS_PER_SEC << " (seconds) " << std::endl;

	if(res == 1)
		std::cout << "ERROR: General Encryption Failure" << std::endl;
	else if(res == 2)
		std::cout << "ERROR: General Decryption Failure" << std::endl;
	else if(res == 3)
		std::cout << "ERROR: General JSON Parsing Failure" << std::endl;
	else if(res == 4)
		std::cout << "ERROR: Invalid Header Version" << std::endl;
	else if(res == 5)
		std::cout << "ERROR: Invalid Sender ID" << std::endl;
	else if(res == 6)
		std::cout << "ERROR: Invalid Recipient ID" << std::endl;
	else if(res == 7)
		std::cout << "ERROR: Hash of File is corrupt" << std::endl;
	else if(res == 0xff)
		std::cout << "ERROR: General Encryption Failure" << std::endl;

	remove((path + fileName).c_str());			// delete file if it exists already
	uint8_t result = session.DecryptFile(fileName + fileExtensionEncrypted, path);
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

	std::ifstream decryptedFile(path + fileName, std::ios::in | std::ios::binary | std::ios::ate);
	if(decryptedFile.is_open() == true)
	{
		decryptedFile.seekg(0, std::ios::end);
		std::streampos streamPosDecryptedFileSize = decryptedFile.tellg();
		const size_t decryptedFileSize = streamPosDecryptedFileSize;
		decryptedFile.seekg(0, std::ios::beg);
		std::vector<uint8_t> vDecryptedFileContent(decryptedFileSize);
		decryptedFile.read((char*) &vDecryptedFileContent[0], decryptedFileSize);
		decryptedFile.close();

		uCrypt::uCryptLib::blake2s_Hash(hashDecryptedFile, &vDecryptedFileContent[0], NULL, szOutBytes, decryptedFileSize, 0);
	}
	else
		std::cerr << "\nError on Opening File: " << (path + fileName + fileExtensionEncrypted) << std::endl;


	if( 0 == memcmp(hashOriginalFile, hashDecryptedFile, sizeof(hashOriginalFile)/sizeof(uint8_t)) )
	{
		printf("TUnit_EncryptFile_random_10MB: OK\n");
	}
	else
	{
		printf("TUnit_EncryptFile_random_10MB: FAILED\n");
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
	delete[] fileContentRandom;
}

