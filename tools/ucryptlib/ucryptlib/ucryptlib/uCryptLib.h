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

#ifndef UCRYPTOLIB_H
#define UCRYPTOLIB_H

#ifdef COMPILE_UCRYPTOLIB
	#define UCRYPTOLIB_EXPORT __declspec(dllexport)
	#pragma message ("Export Symbols")
#else
	#define UCRYPTOLIB_EXPORT __declspec(dllimport)
	#pragma message ("Import Symbols")

	#ifdef _DEBUG
		#pragma message ("Compiler Message: DEBUG")
		#pragma comment (lib, "uCryptLib.Debug.lib")
	#else
		#pragma message ("Compiler Message: RELEASE")
		#pragma comment (lib, "uCryptLib.Release.lib")
	#endif
#endif

#ifdef _UNICODE
#pragma message ("Compiler Message: Unicode will be defined")
#else
#pragma message ("Compiler Message: Unicode not defined")
#endif

#include <stddef.h>
#include <string>
#include <cstdint>

namespace uCrypt
{
	class UCRYPTOLIB_EXPORT uCryptLib
	{
	public:
		static const uint8_t _BLAKE2S_OUTBYTES = 32;
		static const uint8_t _BASE58_DECODED_SIZE = 33;
		static const uint8_t _PUBLICKEYBYTES = 32;
		static const uint8_t _SECRETKEYBYTES = 32;
		static const uint8_t _ID_CHECKSUM_LEN = 1;
		uCryptLib();
		uCryptLib(std::string eMail, std::string passwd);

		uint8_t DecryptFile(std::string fileName, std::string path);
		uint8_t EncryptFile(std::string fileName, std::string path, std::string recipientIDs[], uint8_t numRecipients);

		std::string getIdentificationNumber();
		void uCryptInit(std::string eMail, std::string passwd);

		static double getBitEntropy(std::string s);

		static int  blake2s_Hash(uint8_t *out, const void *in, const void *key, const uint8_t outlen, const uint64_t inlen, uint8_t keylen);
		static int  scrypt(const uint8_t *, size_t, const uint8_t *, size_t, uint64_t, uint32_t, uint32_t, uint8_t *, size_t);
		static std::string base64_Encode(unsigned char const *, unsigned int);
		static std::string base64_Decode(std::string const &);
		static bool base58_Decode(void *bin, size_t *binszp, const char *b58, size_t b58sz);
		static bool base58_Encode(char *b58, size_t *b58sz, const void *data, size_t binsz);
		
	private:
		static const size_t   _CHUNK_SIZE = 1048576;
		static const uint16_t _FILENAME_LEN_PADDED = 256;
		static const uint8_t  _FILEKEY_LEN = 32;
		static const uint8_t  _FILENONCE_LEN = 16;
		static const uint8_t  _FULLNONCE_LEN = 24;
		static const uint8_t  _CHUNK_NUM_LEN = 8;
		static const uint8_t  _CHUNK_LEN_ARR_LEN = 4;
		static const uint8_t  _MAGIC_BYTES_SIZE = 8;
		static const uint8_t  _PADDING_BYTES_LEN = 16;

		static const uint64_t _SCRYPT_N = 131072; // 2^17
		static const uint32_t _SCRYPT_r = 8;
		static const uint32_t _SCRYPT_p = 1;

		static const int8_t b58digits_map[];
		static const char b58digits_ordered[];

		static const std::string base64_chars; 
		static inline bool is_base64(unsigned char c) {  return (isalnum(c) || (c == '+') || (c == '/')); }

		bool isInitialized;
		uint8_t _secretKey[_SECRETKEYBYTES];
		uint8_t _publicKey[_PUBLICKEYBYTES];
		std::string _identificationNumber;

		static double log2(double number);
		static void incrementChunkCounter(uint8_t *fullNonce);
		static uint32_t readChunkLength(uint8_t *data, size_t szData, size_t offset);
		static uint8_t writeChunkLength(uint8_t *data, size_t szData, size_t chunkLen);
		static void setLastChunkFlag(uint8_t *fullNonce);
	};
}




#endif