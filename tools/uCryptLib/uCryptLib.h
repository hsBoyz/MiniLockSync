/*  This file is part of µCryptLib. A Cryptography Library that's
 *  built to make encryption and decryption as easy and fast as
 *  possible for third party tools.
 *
 *  This library was originally written by Michael Römer as part of an assignment.
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

#ifndef UCRYPTLIB_H
#define UCRYPTLIB_H

#include <QtGlobal> // Q_DECL_EXPORT && Q_DECL_IMPORT

#if defined(UCRYPTLIB)
  #define UCRYPTLIB_LIB_SPEC Q_DECL_EXPORT
  #pragma message ("uCryptLib Export")
#else
  #define UCRYPTLIB_LIB_SPEC Q_DECL_IMPORT
  #pragma message ("uCryptLib Import")
#endif

/*
#if defined(_UNICODE) || defined(UNICODE)
  #pragma message ("Compiler Message: Unicode will be defined")
#else
  #pragma message ("Compiler Message: Unicode not defined")
#endif
*/

#include <stddef.h>
#include <string>
#include <cstdint>


namespace uCrypt
{
  /*!
   * \brief The uCryptLib class is part of a Cryptography Library that's
   *        built to make encryption and decryption as easy and fast as
   *        possible for third party tools.
   */
  class UCRYPTLIB_LIB_SPEC uCryptLib
  {
  public:
    static const uint8_t _BLAKE2S_OUTBYTES = 32;
    static const uint8_t _BASE58_DECODED_SIZE = 33;
    static const uint8_t _PUBLICKEYBYTES = 32;
    static const uint8_t _SECRETKEYBYTES = 32;
    static const uint8_t _ID_CHECKSUM_LEN = 1;

    /*!
     * \brief uCryptLib Default-Konstruktor
     */
    uCryptLib();

    /*!
     * \brief uCryptLib Konstruktor, welcher sofort eine Initialisierung durchführt.
     * \param eMail Der String eMail erwartet die E-Mailadresse des Anwenders zur initialisierung.
     * \param passwd Der String passwd erwartet das Passwort des Anwenders zur initialisierung.
     */
    uCryptLib(std::string eMail, std::string passwd);

    /*!
     * \brief DecryptFile Decryptfile führt die Entschlüsselung der Datei durch.
     * \param fileName Der String fileName erwartet den Dateinamen der zu entschlüsselnden Datei.
     * \param sourcePath Der String sourcePath erwartet den Pfad zu der zu entschlüsselnden Datei.
     * \param targetPath Der String targedPath erwartet den Speicherpfad der zu entschlüsselnden Datei.
     * \return uint8_t Bei erfolgreicher Entschlüsselung wird 0 ausgegeben.
     */
    uint8_t DecryptFile(std::string fileName, std::string sourcePath, std::string targetPath = "");

    /*!
     * \brief EncryptFile EncryptFile führt die Verschlüsselung der Datei durch.
     * \param fileName Der String fileName erwartet den Dateinamen der zu verschlüsselnden Datei.
     * \param sourcePath Der String sourcePath erwartet den Pfad zu der zu verschlüsselnden Datei.
     * \param recipientIDs Das Array recipientsIDs erwartet ein Stringarray aus allen Schlüsseln der Empfänger.
     * \param numRecipients Die Variable numRecipients erwartet die Anzahl der Empfänger.
     * \param targetPath Der String targedPath erwartet den Speicherpfad zu der zu verschlüsselnden Datei.
     * \return uint8_t Bei erfolgreicher Verschlüsselung wird 0 ausgegeben.
     */
    uint8_t EncryptFile(std::string fileName, std::string sourcePath, std::string recipientIDs[], uint8_t numRecipients, std::string targetPath = "");

    /*!
     * \brief getIdentificationNumber getIdentificationNumber gibt die Variable _identificationNumber zurück.
     * \return std::string Der Rückgabewert ist die Variable _identificationNumber.
     */
    std::string getIdentificationNumber();

    /*!
     * \brief uCryptInit Die Methode uCryptInit führt eine Initialisierung durch.
     * \param eMail Der String eMail erwartet die E-Mailadresse des Anwenders zur initialisierung.
     * \param passwd Der String passwd erwartet das Passwort des Anwenders zur initialisierung.
     */
    void uCryptInit(std::string eMail, std::string passwd);

    /*!
     * \brief getBitEntropy Die Methode getBitEntropy überprüft den String auf seine Bit Entropie.
     * \param s Der String s erwartet den String, welcher überprüft werden soll.
     * \return double Der Rückgabewert ist die Entropie des übergebenen Parameters s.
     */
    static double getBitEntropy(std::string s);

    /*!
     * \brief blake2s_Hash Die Methode blake2s_Hash ruft führt den blake2s Algorithmus für 32-Bit Maschinen aus.
     * \param out
     * \param in
     * \param key
     * \param outlen
     * \param inlen
     * \param keylen
     * \return
     */
    static int  blake2s_Hash(uint8_t *out, const void *in, const void *key, const uint8_t outlen, const uint64_t inlen, uint8_t keylen);

    /*!
     * \brief scrypt crypto_scrypt(passwd, passwdlen, salt, saltlen, N, r, p, buf, buflen):
     * Compute scrypt(passwd[0 .. passwdlen - 1], salt[0 .. saltlen - 1], N, r,
     * p, buflen) and write the result into buf.  The parameters r, p, and buflen
     * must satisfy r * p < 2^30 and buflen <= (2^32 - 1) * 32.  The parameter N
     * must be a power of 2 greater than 1.
     *
     * \return Return 0 on success; or -1 on error.
     */
    static int  scrypt(const uint8_t *, size_t, const uint8_t *, size_t, uint64_t, uint32_t, uint32_t, uint8_t *, size_t);

    /*!
     * \brief base64_Encode Die Methode base64_Encode kodiert den eingegebenen String ins base64 Format.
     * \param bytes_to_encode Die Variable bytes_to_encode erwartet einen Pointer zu dem zu kodierenden String.
     * \param in_len Die Variable in_len erwartet die Länge des zu kodierenden Strings.
     * \return Der Rückgabewert ist der kodierte String
     */
    static std::string base64_Encode(unsigned char const *bytes_to_encode, unsigned int in_len);

    /*!
     * \brief base64_Decode Die Methode base64_Decode dekodiert den eingegebenen String.
     * \param encoded_string Die Variabe encoded_string erwartet den kodierten String.
     * \return Der Rückgabewert ist der dekodierte String.
     */
    static std::string base64_Decode(std::string const &encoded_string);

    /*!
     * \brief base58_Decode Die Methode base58_Decode dekodiert den eingegebenen String.
     * \param bin Die Variable bin erwartet den Wert der Variable _BASE58_DECODED_SIZE im binären Format.
     * \param binszp Die Variable binszp erwartet den Wert der Variable _BASE58_DECODED_SIZE als Integer.
     * \param b58 Die Variable b58 erwartet den zu dekodierenden String.
     * \param b58sz Die Variable b58sz erwartet die Länge des zu dekodierenden Strings.
     * \return Der Rückgabewert ist im Fehlerfall false, ansonsten true.
     */
    static bool base58_Decode(void *bin, size_t *binszp, const char *b58, size_t b58sz);

    /*!
     * \brief base58_Encode Die Methode base58_Encode kodiert den eingegebenen String ins base58 Format.
     * \param b58 Die Variable b58 erwartet einen String auf dem der kodierte String abgebildet wird.
     * \param b58sz Die Variable b58sz erwartet die Größe der Variable b58.
     * \param data Die Variable data erwartet den zu kodierenden String.
     * \param binsz Die Variable binsz erwartet die Größe der Variable data.
     * \return Der Rückgabewert ist im Fehlerfall false, ansonsten true.
     */
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
    static inline bool is_base64(unsigned char c)
    {
      return (isalnum(c) || (c == '+') || (c == '/'));
    }

    bool isInitialized;
    uint8_t _secretKey[_SECRETKEYBYTES];
    uint8_t _publicKey[_PUBLICKEYBYTES];
    std::string _identificationNumber;

    static double log2(double number);
    static void incrementChunkCounter(uint8_t *fullNonce);
    static uint32_t readChunkLength(uint8_t *data, size_t szData, size_t offset);
    static uint8_t writeChunkLength(uint8_t *data, size_t szData, size_t chunkLen);
    static void setLastChunkFlag(uint8_t *fullNonce);
  }; // class uCryptLib
} // namespace uCrypt

#endif // UCRYPTLIB_H
