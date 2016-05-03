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

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <BaseTsd.h>
#include <fstream>
#include <cstdint>
#include <vector>
#include <iterator>
#include <stdlib.h>
#include <string>
#include <map>
#include <iostream>
#include <algorithm>
#include <cmath>

#include "uCryptLib.h"
#include "crypto_scrypt.h"
#include "sodium.h"
#include "blake2.h"
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"

typedef SSIZE_T ssize_t;

namespace uCrypt 
{

	const std::string uCryptLib::base64_chars = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

	const int8_t uCryptLib::b58digits_map[] = {
		-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
		-1, 0, 1, 2, 3, 4, 5, 6,  7, 8,-1,-1,-1,-1,-1,-1,
		-1, 9,10,11,12,13,14,15, 16,-1,17,18,19,20,21,-1,
		22,23,24,25,26,27,28,29, 30,31,32,-1,-1,-1,-1,-1,
		-1,33,34,35,36,37,38,39, 40,41,42,43,-1,44,45,46,
		47,48,49,50,51,52,53,54, 55,56,57,-1,-1,-1,-1,-1,
	};

	const char uCryptLib::b58digits_ordered[] = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

	uCryptLib::uCryptLib()
	{
		isInitialized = false;
	}

	uCryptLib::uCryptLib(std::string eMail, std::string passwd)
	{
		const uint8_t* salt = reinterpret_cast<const uint8_t*>(eMail.c_str());
		const uint8_t* pPasswd = reinterpret_cast<const uint8_t*>(passwd.c_str());
		const size_t salt_len = eMail.length();

		uint8_t hash[BLAKE2S_OUTBYTES];
		uint8_t identificationNumberHash[_ID_CHECKSUM_LEN];
		uint8_t identificationNumber[_ID_CHECKSUM_LEN + crypto_box_PUBLICKEYBYTES];
		char encIdentificationNumber[256];

		const uint64_t inlen = passwd.length();

		blake2s_Hash(hash, passwd.c_str(), NULL, BLAKE2S_OUTBYTES, inlen, 0);
		scrypt(hash, BLAKE2S_OUTBYTES, salt, salt_len, _SCRYPT_N, _SCRYPT_r, _SCRYPT_p, _secretKey, crypto_box_PUBLICKEYBYTES );
		crypto_scalarmult_curve25519_base(_publicKey, _secretKey);

		blake2s_Hash(identificationNumberHash, _publicKey, NULL, _ID_CHECKSUM_LEN, crypto_box_PUBLICKEYBYTES, 0);

		for(size_t i = 0; i < crypto_box_PUBLICKEYBYTES; i++)
			identificationNumber[i] = _publicKey[i];	

		identificationNumber[(_ID_CHECKSUM_LEN + crypto_box_PUBLICKEYBYTES) - 1] = identificationNumberHash[0];

		size_t encB58Len = sizeof(encIdentificationNumber)/sizeof(char);
		size_t *encB58sz = &encB58Len;

		base58_Encode(encIdentificationNumber, encB58sz, identificationNumber, _ID_CHECKSUM_LEN + crypto_box_PUBLICKEYBYTES);

		_identificationNumber = (encIdentificationNumber);

		isInitialized = true;
	}
	
	void uCryptLib::uCryptInit(std::string eMail, std::string passwd)
	{
		const uint8_t* salt = reinterpret_cast<const uint8_t*>(eMail.c_str());
		const uint8_t* pPasswd = reinterpret_cast<const uint8_t*>(passwd.c_str());
		const size_t salt_len = eMail.length();

		uint8_t hash[BLAKE2S_OUTBYTES];
		uint8_t identificationNumberHash[_ID_CHECKSUM_LEN];
		uint8_t identificationNumber[_ID_CHECKSUM_LEN + crypto_box_PUBLICKEYBYTES];
		char encIdentificationNumber[256];

		const uint64_t inlen = passwd.length();
		blake2s_Hash(hash, passwd.c_str(), NULL, BLAKE2S_OUTBYTES, inlen, 0);
		scrypt(hash, BLAKE2S_OUTBYTES, salt, salt_len, _SCRYPT_N, _SCRYPT_r, _SCRYPT_p, _secretKey, crypto_box_PUBLICKEYBYTES );
		crypto_scalarmult_curve25519_base(_publicKey, _secretKey);

		blake2s_Hash(identificationNumberHash, _publicKey, NULL, _ID_CHECKSUM_LEN, crypto_box_PUBLICKEYBYTES, 0);

		for(size_t i = 0; i < crypto_box_PUBLICKEYBYTES; i++)
			identificationNumber[i] = _publicKey[i];	

		identificationNumber[(_ID_CHECKSUM_LEN + crypto_box_PUBLICKEYBYTES) - 1] = identificationNumberHash[0];

		size_t encB58Len = sizeof(encIdentificationNumber)/sizeof(char);
		size_t *encB58sz = &encB58Len;

		base58_Encode(encIdentificationNumber, encB58sz, identificationNumber, _ID_CHECKSUM_LEN + crypto_box_PUBLICKEYBYTES);

		_identificationNumber = (encIdentificationNumber);

		isInitialized = true;
	}

	void uCryptLib::incrementChunkCounter(uint8_t *fullNonce) {
		for (size_t i = _FILENONCE_LEN; i < _FULLNONCE_LEN; i++) {
			fullNonce[i]++;
			if (fullNonce[i]) break;
		}
	}

	uint32_t uCryptLib::readChunkLength(uint8_t *data, size_t szData, size_t offset) {
		uint32_t ret;
		offset |= 0;

		if (szData < offset + 4) return -1;

		ret = ( (data[offset+3] << 24 ) |
			(data[offset+2] << 16 ) |
			(data[offset+1] <<  8 ) |
			(data[offset]) );

		return ret;
	};

	uint8_t uCryptLib::writeChunkLength(uint8_t *data, size_t szData, size_t chunkLen) {
		
		if(szData != _CHUNK_LEN_ARR_LEN) return -1;
		else
		{
			data[0] = (chunkLen >>  0) & 0xff;
			data[1] = (chunkLen >>  8) & 0xff;
			data[2] = (chunkLen >> 16) & 0xff;
			data[3] = (chunkLen >> 24) & 0xff;
			return 0;
		}
	};

	void uCryptLib::setLastChunkFlag(uint8_t *fullNonce) {
		fullNonce[23] |= 0x80;
	}

	uint8_t uCryptLib::DecryptFile(std::string fileName, std::string path)
	{
		if (!isInitialized)
			return 0xff; // Uninitialized Error

		if ( path[path.size()-1] != '\\' 
		  || path[path.size()-1] != '/')
			path.append("/");

		bool decryptSuccess = false;
		fileName = path + fileName;
		std::string strDecryptedFileContent;

		std::ifstream originalFile(fileName, std::ios::in | std::ios::binary | std::ios::ate);
		if(originalFile.is_open() == false)
			return 0xfe; // General File Read Error
		else
		{
			originalFile.seekg(0, std::ios::end);
			std::streampos streamPosOriginalFileSize = originalFile.tellg();
			const size_t originalFileSize = streamPosOriginalFileSize;
			originalFile.seekg(0, std::ios::beg);
			std::vector<uint8_t> vOriginalFileContent(originalFileSize);
			originalFile.read((char*) &vOriginalFileContent[0], originalFileSize);
			originalFile.close();

			
			const uint32_t headerLength = readChunkLength(&vOriginalFileContent[0], vOriginalFileContent.size(), _MAGIC_BYTES_SIZE);
			const size_t startOfCiphertext = _MAGIC_BYTES_SIZE + _CHUNK_LEN_ARR_LEN + headerLength;
			std::string strOriginalFileContent(vOriginalFileContent.begin(), vOriginalFileContent.end());
			std::string strJsonHeader = strOriginalFileContent.substr(_MAGIC_BYTES_SIZE + _CHUNK_LEN_ARR_LEN, _MAGIC_BYTES_SIZE + _CHUNK_LEN_ARR_LEN + headerLength);
			std::vector<uint8_t> encryptedFileContent(vOriginalFileContent.begin() + startOfCiphertext, vOriginalFileContent.end());
			const size_t encryptedFileContentSize = encryptedFileContent.size();

			rapidjson::Document dJsonHeader;
			if( dJsonHeader.Parse(strJsonHeader.c_str()).HasParseError() == true)
				return 3; // General Error on Parsing JSON Header
			else
			{
				int versionInfo = dJsonHeader["version"].GetInt();
				
				if(versionInfo != 1)
					return 4; // Invalid Header Version

				std::string ephemeralPublicKey = base64_Decode(dJsonHeader["ephemeral"].GetString());
				std::vector<uint8_t> vEphemeralPublicKey(ephemeralPublicKey.begin(), ephemeralPublicKey.end());
				const rapidjson::Value& decryptInfoJsonObject = dJsonHeader["decryptInfo"];
				
				int decryptInfoCount = decryptInfoJsonObject.MemberCount();
				std::string *base64uniqueNonce = new std::string[decryptInfoCount];
				std::string *decryptObject = new std::string[decryptInfoCount];

				{
					size_t decryptObjectCounter = 0;
					for (rapidjson::Value::ConstMemberIterator itr = decryptInfoJsonObject.MemberBegin(); itr != decryptInfoJsonObject.MemberEnd(); ++itr)
					{
						base64uniqueNonce[decryptObjectCounter]  = itr->name.GetString();
						decryptObject[decryptObjectCounter] = itr->value.GetString();
						decryptObjectCounter++;
					}
				}

				std::vector<uint8_t> vUniqueNonce;
				std::string strJsonDecryptInfo;

				for(size_t i=0; i < decryptInfoCount; i++)
				{
					std::string strUniqueNonce = base64_Decode(base64uniqueNonce[i]);
					std::string strCipher = base64_Decode(decryptObject[i]);

					vUniqueNonce = std::vector<uint8_t>(strUniqueNonce.begin(), strUniqueNonce.end());
					std::vector<uint8_t> vCipher(strCipher.begin(), strCipher.end());

					uint8_t *decrypted_JsonDecryptInfo = new uint8_t[vCipher.size() - crypto_box_MACBYTES];
					if(0 == crypto_box_open_easy(decrypted_JsonDecryptInfo, &vCipher[0], vCipher.size(), &vUniqueNonce[0], &vEphemeralPublicKey[0], _secretKey))
					{
						strJsonDecryptInfo = std::string(reinterpret_cast<char const*>(decrypted_JsonDecryptInfo), vCipher.size());
						decryptSuccess = true;
						break;
					}
					delete[] decrypted_JsonDecryptInfo;
				}

				if(decryptSuccess == false)
					return 2; // General Decryption Failure

				strJsonDecryptInfo = strJsonDecryptInfo.substr( strJsonDecryptInfo.find("{", 0),
															   (strJsonDecryptInfo.find("}", 0) + 1) - strJsonDecryptInfo.find("{", 0));
				rapidjson::Document dJsonDecryptInfo;

				delete[] base64uniqueNonce;
				delete[] decryptObject;

				if( dJsonDecryptInfo.Parse(strJsonDecryptInfo.c_str()).HasParseError() == true)
					return 3; // General Error on Parsing JSON Header
				else
				{
					std::string b58encSenderId = dJsonDecryptInfo["senderID"].GetString();
					std::string b58encRecipientId = dJsonDecryptInfo["recipientID"].GetString();
					std::string b64encFileInfo = dJsonDecryptInfo["fileInfo"].GetString();

					if(b58encRecipientId != _identificationNumber)
						return 6; // Wrong Recipient

					std::string strEncryptedFileInfo = base64_Decode(b64encFileInfo);
					std::vector<uint8_t> vEncryptedFileInfo(strEncryptedFileInfo.begin(), strEncryptedFileInfo.end());

					uint8_t *decrypted_JsonFileInfo = new uint8_t[vEncryptedFileInfo.size() - crypto_box_MACBYTES];
					if(0 != crypto_box_open_easy(decrypted_JsonFileInfo, &vEncryptedFileInfo[0], vEncryptedFileInfo.size(), &vUniqueNonce[0], _publicKey, _secretKey))
						return 2; // General Decryption Failure

					std::string strJsonFileInfo(reinterpret_cast<char const*>(decrypted_JsonFileInfo), vEncryptedFileInfo.size());

					delete[] decrypted_JsonFileInfo;

					strJsonFileInfo = strJsonFileInfo.substr( strJsonFileInfo.find("{", 0),
															 (strJsonFileInfo.find("}", 0) + 1) - strJsonFileInfo.find("{", 0));
					rapidjson::Document dJsonFileInfo;
					if( dJsonFileInfo.Parse(strJsonFileInfo.c_str()).HasParseError() == true)
						return 3; // General Error on Parsing JSON Header
					else
					{
						std::string strFileKey = base64_Decode(dJsonFileInfo["fileKey"].GetString());
						std::string strFileNonce = base64_Decode(dJsonFileInfo["fileNonce"].GetString());
						std::string strFileHash = base64_Decode(dJsonFileInfo["fileHash"].GetString());

						std::vector<uint8_t> vFileHash(strFileHash.begin(), strFileHash.end());
						std::vector<uint8_t> vFileKey(strFileKey.begin(), strFileKey.end());
						std::vector<uint8_t> vFileNonce(strFileNonce.begin(), strFileNonce.end());
						std::vector<uint8_t> chunkNum(_CHUNK_NUM_LEN, 0);

						uint32_t chunkSizeDecrypted = _CHUNK_SIZE;		// chunk size to be encrypted
						uint32_t chunkSizeEncrypted = _CHUNK_SIZE;		// chunk size to be encrypted
						size_t cTotalChunks = (originalFileSize + (_CHUNK_SIZE - 1)) / (_CHUNK_SIZE);
						size_t itDataPosition = 0;

						uint8_t calculatedFileContentHash[BLAKE2S_OUTBYTES];
						blake2s_Hash(calculatedFileContentHash, &encryptedFileContent[0], NULL, BLAKE2S_OUTBYTES, encryptedFileContent.size(), 0);

						if(memcmp(calculatedFileContentHash, &vFileHash[0], BLAKE2S_OUTBYTES) != 0)
							return 7; // Error verifing fileHash

						// first chunk (0): filename
						chunkSizeDecrypted = readChunkLength(&encryptedFileContent[0], encryptedFileContentSize, 0 /*offset=0*/);
						chunkSizeEncrypted = chunkSizeDecrypted + _CHUNK_LEN_ARR_LEN + _PADDING_BYTES_LEN;
						std::vector<uint8_t> encryptedChunk(encryptedFileContent.begin() + _CHUNK_LEN_ARR_LEN, encryptedFileContent.begin() + chunkSizeEncrypted);
						std::vector<uint8_t> vFullNonce;
						vFullNonce.insert(vFullNonce.begin(), vFileNonce.begin(), vFileNonce.end());
						vFullNonce.insert(vFullNonce.end(), chunkNum.begin(), chunkNum.end());

						uint8_t *decryptedFileName = new uint8_t[chunkSizeDecrypted];
						if( 0 != crypto_secretbox_open_easy(decryptedFileName, &encryptedChunk[0], encryptedChunk.size(), &vFullNonce[0], &vFileKey[0]))
							return 2; // General Decrytion Error

						std::string strDecryptedFileName(reinterpret_cast<char const*>(decryptedFileName), chunkSizeDecrypted);
						std::string saveFileName = path + strDecryptedFileName;
						itDataPosition = chunkSizeEncrypted;
						bool isLast = false;

						delete[] decryptedFileName;

						for(size_t i = 1; i <= (cTotalChunks); i++)
						{
							if(isLast)
								break;

							chunkSizeDecrypted = readChunkLength(&encryptedFileContent[0], encryptedFileContentSize, itDataPosition);
							chunkSizeEncrypted = chunkSizeDecrypted + _CHUNK_LEN_ARR_LEN + _PADDING_BYTES_LEN; 

							if(itDataPosition >= ( encryptedFileContentSize - (chunkSizeEncrypted ) ) )
							{	// last chunk
								incrementChunkCounter(&vFullNonce[0]);
								setLastChunkFlag(&vFullNonce[0]);
								isLast = true;
							}
							else
							{
								incrementChunkCounter(&vFullNonce[0]);
							}

							std::vector<uint8_t> encryptedChunk(encryptedFileContent.begin() + itDataPosition + _CHUNK_LEN_ARR_LEN, 
																encryptedFileContent.begin() + itDataPosition + chunkSizeEncrypted);

							uint8_t *decryptedFileContent = new uint8_t[chunkSizeDecrypted];
							if( 0 != crypto_secretbox_open_easy(decryptedFileContent, &encryptedChunk[0], encryptedChunk.size(), &vFullNonce[0], &vFileKey[0]))
								return 2; // General Decrytion Error

							itDataPosition = itDataPosition + chunkSizeEncrypted;

							strDecryptedFileContent = strDecryptedFileContent + std::string(decryptedFileContent, decryptedFileContent + chunkSizeDecrypted);
							delete[] decryptedFileContent;
						}

						remove(saveFileName.c_str());			// delete file if it exists already
						std::ofstream decryptedFile;
						decryptedFile.open(saveFileName, std::ios::binary | std::ios::out | std::ios_base::app);

						if(decryptedFile.is_open() == false)
							return 0xfe;
						else
							decryptedFile << strDecryptedFileContent;

						decryptedFile.close();

					}
				}
			}
		}

		return 0;
	}

	uint8_t uCryptLib::EncryptFile(std::string fileName, std::string path, std::string recipientIDs[], uint8_t numberRecipients)
	{
		if (!isInitialized)
		  return 0xff; // Uninitialized Error

		if ( path[path.size()-1] != '\\' 
		  || path[path.size()-1] != '/')
			path.append("/");

		std::string saveFileName = path + fileName + ".encrypted";
		std::string fileNameInclPath = path + fileName;
		std::string encryptedFile;
		std::string encryptedFileContent;

		uint8_t senderEphemeralSecret[_SECRETKEYBYTES];
		uint8_t senderEphemeralPublic[_PUBLICKEYBYTES];
		crypto_box_keypair(senderEphemeralPublic, senderEphemeralSecret);
		
		uint8_t vMagicBytes[] = {0x6d, 0x69, 0x6e, 0x69, 0x4c, 0x6f, 0x63, 0x6b};
		std::vector<uint8_t> vChunkLenArray(_CHUNK_LEN_ARR_LEN,0);
		std::vector<uint8_t> vFileNonce(_FILENONCE_LEN, 0);
		std::vector<uint8_t> vFileKey(_FILEKEY_LEN, 0);
		std::vector<uint8_t> vFileHash(BLAKE2S_OUTBYTES, 0);
		std::vector<uint8_t> vChunkNum(_CHUNK_NUM_LEN, 0);
		std::vector<uint8_t> vFullNonce;

		randombytes_buf(&vFileNonce[0], _FILENONCE_LEN);
		randombytes_buf(&vFileKey[0], _FILEKEY_LEN);

		size_t offset = 0;
		uint32_t chunkSizeDecrypted = _CHUNK_SIZE;		// chunk size to be encrypted
		uint32_t chunkSizeEncrypted = _CHUNK_SIZE;		// chunk size to be encrypted

		std::vector<uint8_t> paddedFileName(_FILENAME_LEN_PADDED - fileName.size(),0);
		paddedFileName.insert(paddedFileName.begin(), fileName.begin(), fileName.end());
		
		chunkSizeDecrypted = paddedFileName.size();
		chunkSizeEncrypted = chunkSizeDecrypted + crypto_box_MACBYTES;

		vFullNonce.insert(vFullNonce.begin(), vFileNonce.begin(), vFileNonce.end());
		vFullNonce.insert(vFullNonce.end(), vChunkNum.begin(), vChunkNum.end());

		uint8_t *encryptedFileName = new uint8_t[chunkSizeEncrypted];
		if ( 0 != crypto_secretbox_easy(encryptedFileName, &paddedFileName[0], paddedFileName.size(), &vFullNonce[0], &vFileKey[0]) )
			return 1; // General Encrytion Failure

		writeChunkLength(&vChunkLenArray[0], vChunkLenArray.size(), chunkSizeDecrypted);

		encryptedFileContent = encryptedFileContent + std::string(vChunkLenArray.begin(), vChunkLenArray.end()) + std::string(encryptedFileName, encryptedFileName + chunkSizeEncrypted);

		std::ifstream originalFile(fileNameInclPath, std::ios::in | std::ios::binary | std::ios::ate);
		if(originalFile.is_open() == false)
			return 0xfe; // General File Read Error
		else
		{
			originalFile.seekg(0, std::ios::end);
			std::streampos streamPosOriginalFileSize = originalFile.tellg();
			const size_t originalFileSize = streamPosOriginalFileSize;
			originalFile.seekg(0, std::ios::beg);
			std::vector<uint8_t> vDecryptedFileContent(originalFileSize);
			originalFile.read((char*) &vDecryptedFileContent[0], originalFileSize);
			originalFile.close();

			const size_t cTotalChunks = (originalFileSize + (_CHUNK_SIZE - 1)) / (_CHUNK_SIZE);
			int32_t diffChunk = originalFileSize - _CHUNK_SIZE; // if result < 0 -> only chunk and smaller than chunk
			size_t itDataPosition = 0;
			bool isLast = false;

			for(size_t i = 0; i < cTotalChunks; i++)
			{
				if(isLast)
					break;

				if ( itDataPosition > ( originalFileSize - (_CHUNK_SIZE ) ) )
				{	// last chunk
					chunkSizeDecrypted = originalFileSize - itDataPosition;
					incrementChunkCounter(&vFullNonce[0]);
					setLastChunkFlag(&vFullNonce[0]);
					isLast = true;
				}
				else if(diffChunk < 0 )
				{	// first chunk is the last chunk
					chunkSizeDecrypted = originalFileSize;
					incrementChunkCounter(&vFullNonce[0]);
					setLastChunkFlag(&vFullNonce[0]);
					isLast = true;
				}
				else
				{
					chunkSizeDecrypted = _CHUNK_SIZE;
					incrementChunkCounter(&vFullNonce[0]);
				}

				chunkSizeEncrypted = chunkSizeDecrypted + crypto_box_MACBYTES;

				std::vector<uint8_t> decryptedChunk(vDecryptedFileContent.begin() + itDataPosition, 
													vDecryptedFileContent.begin() + itDataPosition + chunkSizeDecrypted);

				uint8_t *encryptedChunk = new uint8_t[chunkSizeEncrypted];

				if( 0 != crypto_secretbox_easy(encryptedChunk, &decryptedChunk[0], decryptedChunk.size(), &vFullNonce[0], &vFileKey[0]))
								return 1; //  General Encryption Error

				writeChunkLength(&vChunkLenArray[0], vChunkLenArray.size(), chunkSizeDecrypted);
				encryptedFileContent = encryptedFileContent 
									   + std::string(vChunkLenArray.begin(), vChunkLenArray.end()) 
									   + std::string(encryptedChunk, encryptedChunk + chunkSizeEncrypted);

				itDataPosition = itDataPosition + chunkSizeDecrypted;

				delete[] encryptedChunk;
			}
		}

		// Calculate Hash
		uint8_t calculatedFileContentHash[BLAKE2S_OUTBYTES];
		blake2s_Hash(calculatedFileContentHash, encryptedFileContent.c_str(), NULL, BLAKE2S_OUTBYTES, encryptedFileContent.size(), 0);

		// JSON-Header
		std::string strFileHash = base64_Encode(calculatedFileContentHash, BLAKE2S_OUTBYTES);;
		std::string base64_fileKey = base64_Encode(&vFileKey[0], _FILEKEY_LEN);
		std::string	base64_fileNonce = base64_Encode(&vFileNonce[0], _FILENONCE_LEN);

		std::string json_Object = "{\"version\":1,\"ephemeral\":\"" + base64_Encode(senderEphemeralPublic, _PUBLICKEYBYTES) + "\",";
		std::string json_decryptInfo = "\"decryptInfo\":{";
		std::string json_fileInfo = "\"fileInfo\":";
		std::string base64_decryptInfo;

		for(size_t i = 0; i < numberRecipients; i++)
		{
			std::string strJsonFileInfo = "{\"fileKey\":\"" + base64_fileKey + "\",\"fileNonce\":\"" + base64_fileNonce + "\",\"fileHash\":\"" + strFileHash + "\"}";
			
			size_t jsonFileInfo_Len = strJsonFileInfo.length();
			uint8_t *pJsonFileInfo = new uint8_t[jsonFileInfo_Len];
			pJsonFileInfo = reinterpret_cast<uint8_t*>(&strJsonFileInfo[0]);

			size_t encrypted_jsonFileInfo_Len = crypto_box_MACBYTES + jsonFileInfo_Len;
			uint8_t *encrypted_jsonFileInfo = new uint8_t[encrypted_jsonFileInfo_Len];

			uint8_t *uniqueNonce = new uint8_t[crypto_box_NONCEBYTES];
			randombytes_buf(uniqueNonce, crypto_box_NONCEBYTES);

			uint8_t *recipientPublic = new uint8_t[_PUBLICKEYBYTES];
			size_t actPos = _BASE58_DECODED_SIZE;
			char *decodedRecipientPublic = new char[_BASE58_DECODED_SIZE];

			base58_Decode(decodedRecipientPublic, &actPos, recipientIDs[i].c_str(), recipientIDs[i].length());

			for(size_t j = 0; j < _PUBLICKEYBYTES; j++)
				recipientPublic[j] = decodedRecipientPublic[j];

			if( 0 != crypto_box_easy(encrypted_jsonFileInfo, pJsonFileInfo, jsonFileInfo_Len, uniqueNonce, recipientPublic, _secretKey))
				return 1; // General Encrytion Failure 

			std::string base64_uniqueNonce = base64_Encode(uniqueNonce, _FULLNONCE_LEN);
			std::string base64_fileInfo = base64_Encode(encrypted_jsonFileInfo, encrypted_jsonFileInfo_Len);
			std::string strJsonDecryptInfo_N = "{\"senderID\":\"" + _identificationNumber + "\",\"recipientID\":\"" + recipientIDs[i] + "\"," + json_fileInfo + "\"" + base64_fileInfo + "\"}";

			size_t jsonDecryptInfo_N_Len = strJsonDecryptInfo_N.length();
			uint8_t *pJsonDecryptInfo_N = new uint8_t[jsonDecryptInfo_N_Len];
			pJsonDecryptInfo_N = reinterpret_cast<uint8_t*>(&strJsonDecryptInfo_N[0]);

			size_t encrypted_jsonDecryptInfo_N_Len = crypto_box_MACBYTES + jsonDecryptInfo_N_Len;
			uint8_t *encrypted_jsonDecryptInfo_N = new uint8_t[encrypted_jsonDecryptInfo_N_Len];

			if( 0 != crypto_box_easy(encrypted_jsonDecryptInfo_N, pJsonDecryptInfo_N, jsonDecryptInfo_N_Len, uniqueNonce, recipientPublic, senderEphemeralSecret))
				return 1; // General Encrytion Failure

			std::string base64_decryptInfo_N = base64_Encode(encrypted_jsonDecryptInfo_N, encrypted_jsonDecryptInfo_N_Len);
			base64_decryptInfo = base64_decryptInfo + "\"" + base64_uniqueNonce + "\":\"" + base64_decryptInfo_N + "\",";
		}

		base64_decryptInfo = base64_decryptInfo.substr(0, base64_decryptInfo.size() - 1) + "}}"; // remove last "," and add "}}" 

		json_Object = json_Object + json_decryptInfo + base64_decryptInfo; 
		writeChunkLength(&vChunkLenArray[0], vChunkLenArray.size(), json_Object.size());

		encryptedFile = std::string(vMagicBytes, vMagicBytes + (sizeof(vMagicBytes)/(sizeof(vMagicBytes[0]))))
			+ std::string(vChunkLenArray.begin(), vChunkLenArray.end())
			+ json_Object;

		encryptedFile = encryptedFile + encryptedFileContent;

		remove(saveFileName.c_str());			// delete file if it exists already
		std::ofstream encryptedFileStream;
		encryptedFileStream.open(saveFileName, std::ios::binary | std::ios::out | std::ios_base::app);
		if(encryptedFileStream.is_open())
			encryptedFileStream << encryptedFile;
		else
			return 0xfe; // General File Read Error

		encryptedFileStream.close();
		return 0;
	}

	std::string uCryptLib::getIdentificationNumber()
	{
		return _identificationNumber;
	}

	double uCryptLib::log2( double number )
	{
		return log(number) / log(2.0);
	}

	double uCryptLib::getBitEntropy(std::string s)
	{
		std::map<char , int> frequencies ;
		for each ( char c in s )
			frequencies[ c ] ++ ;

		int numlen = s.length( ) ;
		double infocontent = 0 ;
		for each ( std::pair<char , int> p in frequencies ) {
			double freq = static_cast<double>( p.second ) / numlen ;
			infocontent += freq * log2( freq ) ;
		}
		infocontent *= -1 ;
		
		return infocontent ;
	}

	std::string uCryptLib::base64_Encode(unsigned char const* bytes_to_encode, unsigned int in_len)
	{
		std::string ret;
		int i = 0;
		int j = 0;
		unsigned char char_array_3[3];
		unsigned char char_array_4[4];

		while (in_len--) {
			char_array_3[i++] = *(bytes_to_encode++);
			if (i == 3) {
				char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
				char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
				char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
				char_array_4[3] = char_array_3[2] & 0x3f;

				for(i = 0; (i <4) ; i++)
					ret += base64_chars[char_array_4[i]];
				i = 0;
			}
		}

		if (i)
		{
			for(j = i; j < 3; j++)
				char_array_3[j] = '\0';

			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (j = 0; (j < i + 1); j++)
				ret += base64_chars[char_array_4[j]];

			while((i++ < 3))
				ret += '=';

		}

		return ret;
	}

	std::string uCryptLib::base64_Decode(std::string const& encoded_string)
	{
		int in_len = encoded_string.size();
		int i = 0;
		int j = 0;
		int in_ = 0;
		unsigned char char_array_4[4], char_array_3[3];
		std::string ret;

		while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
			char_array_4[i++] = encoded_string[in_]; in_++;
			if (i ==4) {
				for (i = 0; i <4; i++)
					char_array_4[i] = base64_chars.find(char_array_4[i]);

				char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
				char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
				char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

				for (i = 0; (i < 3); i++)
					ret += char_array_3[i];
				i = 0;
			}
		}

		if (i) {
			for (j = i; j <4; j++)
				char_array_4[j] = 0;

			for (j = 0; j <4; j++)
				char_array_4[j] = base64_chars.find(char_array_4[j]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
		}

		return ret;
	}

	int uCryptLib::blake2s_Hash(uint8_t *out, const void *in, const void *key, const uint8_t outlen, const uint64_t inlen, uint8_t keylen)
	{
		return blake2s( out, in, key, outlen, inlen, keylen );
	}

	int uCryptLib::scrypt(const uint8_t * passwd, size_t passwdlen,
						  const uint8_t * salt, size_t saltlen, 
						  uint64_t N, uint32_t r, uint32_t p,
						  uint8_t * buf, size_t buflen)
	{

		return crypto_scrypt(passwd, passwdlen, salt, saltlen, N, r, p, buf, buflen);
	}
	
	
	bool uCryptLib::base58_Decode(void *bin, size_t *binszp, const char *b58, size_t b58sz)
	{
		size_t binsz = *binszp;
		const unsigned char *b58u = reinterpret_cast<const unsigned char*>(b58);
		unsigned char *binu = reinterpret_cast<unsigned char*>(bin);
		size_t outisz = (binsz + 3) / 4;
		uint32_t *outi= new uint32_t [outisz];
		uint64_t t;
		uint32_t c;
		size_t i, j;
		uint8_t bytesleft = binsz % 4;
		uint32_t zeromask = bytesleft ? (0xffffffff << (bytesleft * 8)) : 0;
		unsigned zerocount = 0;

		if (!b58sz)
			b58sz = strlen(b58);

		memset(outi, 0, outisz * sizeof(*outi));

		// Leading zeros, just count
		for (i = 0; i < b58sz && !b58digits_map[b58u[i]]; ++i)
			++zerocount;

		for ( ; i < b58sz; ++i)
		{
			if (b58u[i] & 0x80)
				// High-bit set on invalid digit
				return false;
			if (b58digits_map[b58u[i]] == -1)
				// Invalid base58 digit
				return false;
			c = (unsigned)b58digits_map[b58u[i]];
			for (j = outisz; j--; )
			{
				t = ((uint64_t)outi[j]) * 58 + c;
				c = (t & 0x3f00000000) >> 32;
				outi[j] = t & 0xffffffff;
			}
			if (c)
				// Output number too big (carry to the next int32)
				return false;
			if (outi[0] & zeromask)
				// Output number too big (last int32 filled too far)
				return false;
		}

		j = 0;
		switch (bytesleft) {
		case 3:
			*(binu++) = (outi[0] &   0xff0000) >> 16;
		case 2:
			*(binu++) = (outi[0] &     0xff00) >>  8;
		case 1:
			*(binu++) = (outi[0] &       0xff);
			++j;
		default:
			break;
		}

		for (; j < outisz; ++j)
		{
			*(binu++) = (outi[j] >> 0x18) & 0xff;
			*(binu++) = (outi[j] >> 0x10) & 0xff;
			*(binu++) = (outi[j] >>    8) & 0xff;
			*(binu++) = (outi[j] >>    0) & 0xff;
		}

		// Count canonical base58 byte count
		binu = reinterpret_cast<unsigned char*>(bin);
		for (i = 0; i < binsz; ++i)
		{
			if (binu[i])
				break;
			--*binszp;
		}
		*binszp += zerocount;

		return true;
	}

	bool uCryptLib::base58_Encode(char *b58, size_t *b58sz, const void *data, size_t binsz)
	{
		const uint8_t *bin = reinterpret_cast<const uint8_t*>(data);
		int carry;
		ssize_t i, j, high, zcount = 0;
		size_t size;

		while (zcount < binsz && !bin[zcount])
			++zcount;

		size = (binsz - zcount) * 138 / 100 + 1;
		uint8_t *buf = new uint8_t[size];
		memset(buf, 0, size);

		for (i = zcount, high = size - 1; i < binsz; ++i, high = j)
		{
			for (carry = bin[i], j = size - 1; (j > high) || carry; --j)
			{
				carry += 256 * buf[j];
				buf[j] = carry % 58;
				carry /= 58;
			}
		}

		for (j = 0; j < size && !buf[j]; ++j);

		if (*b58sz <= zcount + size - j)
		{
			*b58sz = zcount + size - j + 1;
			return false;
		}

		if (zcount)
			memset(b58, '1', zcount);
		for (i = zcount; j < size; ++i, ++j)
			b58[i] = b58digits_ordered[buf[j]];
		b58[i] = '\0';
		*b58sz = i + 1;

		return true;
	}

}