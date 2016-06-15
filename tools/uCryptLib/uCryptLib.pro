######################################################################
# Automatically generated by qmake (3.0) So. Apr. 17 11:19:10 2016
######################################################################

TEMPLATE = lib

TARGET = uCryptLib

DESTDIR = "$$_PRO_FILE_PWD_/../uCryptLib-lib"


DEPENDPATH += include/lib \
              include/blake2 \
              include/libsodium \
              include/rapidjson \
              include/scrypt


INCLUDEPATH += include/lib \
               include/blake2 \
               include/libsodium \
               include/rapidjson \
               include/scrypt


LIBS += -Linclude/lib
LIBS += -lsodium
#LIBS += -Linclude/lib -lscrypt_sse2
#LIBS += -Linclude/lib -lcperciva_aesni


CONFIG += c++11 \
          c++14 \
          qt \
          create_prl \
          #shared
          static

CONFIG += debug \
          warn_on

CONFIG -= app_bundle

QT -= gui # only the core module is used for the lib

VERSION += 1.1.0

DEFINES += UCRYPTLIB \
           HAVE_CONFIG_H # for the scrypt function

# Input
HEADERS += uCryptLib.h \
           include/blake2/blake2-config.h \
           include/blake2/blake2-impl.h \
           include/blake2/blake2-kat.h \
           include/blake2/blake2.h \
           include/blake2/blake2b-load-sse2.h \
           include/blake2/blake2b-load-sse41.h \
           include/blake2/blake2b-round.h \
           include/blake2/blake2s-load-sse2.h \
           include/blake2/blake2s-load-sse41.h \
           include/blake2/blake2s-load-xop.h \
           include/blake2/blake2s-round.h \
           include/libsodium/sodium.h \
           include/rapidjson/allocators.h \
           include/rapidjson/document.h \
           include/rapidjson/encodedstream.h \
           include/rapidjson/encodings.h \
           include/rapidjson/filereadstream.h \
           include/rapidjson/filewritestream.h \
           include/rapidjson/fwd.h \
           include/rapidjson/istreamwrapper.h \
           include/rapidjson/memorybuffer.h \
           include/rapidjson/memorystream.h \
           include/rapidjson/ostreamwrapper.h \
           include/rapidjson/pointer.h \
           include/rapidjson/prettywriter.h \
           include/rapidjson/rapidjson.h \
           include/rapidjson/reader.h \
           include/rapidjson/schema.h \
           include/rapidjson/stream.h \
           include/rapidjson/stringbuffer.h \
           include/rapidjson/writer.h \
           include/libsodium/sodium/core.h \
           include/libsodium/sodium/crypto_aead_aes256gcm.h \
           include/libsodium/sodium/crypto_aead_chacha20poly1305.h \
           include/libsodium/sodium/crypto_auth.h \
           include/libsodium/sodium/crypto_auth_hmacsha256.h \
           include/libsodium/sodium/crypto_auth_hmacsha512.h \
           include/libsodium/sodium/crypto_auth_hmacsha512256.h \
           include/libsodium/sodium/crypto_box.h \
           include/libsodium/sodium/crypto_box_curve25519xsalsa20poly1305.h \
           include/libsodium/sodium/crypto_core_hchacha20.h \
           include/libsodium/sodium/crypto_core_hsalsa20.h \
           include/libsodium/sodium/crypto_core_salsa20.h \
           include/libsodium/sodium/crypto_core_salsa2012.h \
           include/libsodium/sodium/crypto_core_salsa208.h \
           include/libsodium/sodium/crypto_generichash.h \
           include/libsodium/sodium/crypto_generichash_blake2b.h \
           include/libsodium/sodium/crypto_hash.h \
           include/libsodium/sodium/crypto_hash_sha256.h \
           include/libsodium/sodium/crypto_hash_sha512.h \
           include/libsodium/sodium/crypto_int32.h \
           include/libsodium/sodium/crypto_int64.h \
           include/libsodium/sodium/crypto_onetimeauth.h \
           include/libsodium/sodium/crypto_onetimeauth_poly1305.h \
           include/libsodium/sodium/crypto_pwhash.h \
           include/libsodium/sodium/crypto_pwhash_argon2i.h \
           include/libsodium/sodium/crypto_pwhash_scryptsalsa208sha256.h \
           include/libsodium/sodium/crypto_scalarmult.h \
           include/libsodium/sodium/crypto_scalarmult_curve25519.h \
           include/libsodium/sodium/crypto_secretbox.h \
           include/libsodium/sodium/crypto_secretbox_xsalsa20poly1305.h \
           include/libsodium/sodium/crypto_shorthash.h \
           include/libsodium/sodium/crypto_shorthash_siphash24.h \
           include/libsodium/sodium/crypto_sign.h \
           include/libsodium/sodium/crypto_sign_ed25519.h \
           include/libsodium/sodium/crypto_sign_edwards25519sha512batch.h \
           include/libsodium/sodium/crypto_stream.h \
           include/libsodium/sodium/crypto_stream_aes128ctr.h \
           include/libsodium/sodium/crypto_stream_chacha20.h \
           include/libsodium/sodium/crypto_stream_salsa20.h \
           include/libsodium/sodium/crypto_stream_salsa2012.h \
           include/libsodium/sodium/crypto_stream_salsa208.h \
           include/libsodium/sodium/crypto_stream_xsalsa20.h \
           include/libsodium/sodium/crypto_uint16.h \
           include/libsodium/sodium/crypto_uint32.h \
           include/libsodium/sodium/crypto_uint64.h \
           include/libsodium/sodium/crypto_uint8.h \
           include/libsodium/sodium/crypto_verify_16.h \
           include/libsodium/sodium/crypto_verify_32.h \
           include/libsodium/sodium/crypto_verify_64.h \
           include/libsodium/sodium/export.h \
           include/libsodium/sodium/private/common.h \
           include/libsodium/sodium/private/curve25519_ref10.h \
           include/libsodium/sodium/randombytes.h \
           include/libsodium/sodium/randombytes_nativeclient.h \
           include/libsodium/sodium/randombytes_salsa20_random.h \
           include/libsodium/sodium/randombytes_sysrandom.h \
           include/libsodium/sodium/runtime.h \
           include/libsodium/sodium/utils.h \
           include/libsodium/sodium/version.h \
           include/rapidjson/error/en.h \
           include/rapidjson/error/error.h \
           include/rapidjson/internal/biginteger.h \
           include/rapidjson/internal/diyfp.h \
           include/rapidjson/internal/dtoa.h \
           include/rapidjson/internal/ieee754.h \
           include/rapidjson/internal/itoa.h \
           include/rapidjson/internal/meta.h \
           include/rapidjson/internal/pow10.h \
           include/rapidjson/internal/regex.h \
           include/rapidjson/internal/stack.h \
           include/rapidjson/internal/strfunc.h \
           include/rapidjson/internal/strtod.h \
           include/rapidjson/internal/swap.h \
           include/rapidjson/msinttypes/inttypes.h \
           include/rapidjson/msinttypes/stdint.h \
           include/scrypt/cpusupport.h \
           include/scrypt/crypto_scrypt.h \
           include/scrypt/scrypt_platform.h \
           include/scrypt/sha256.h \
           include/scrypt/warnp.h \
           include/scrypt/config.h \
           include/scrypt/crypto_scrypt_smix.h \
           include/scrypt/crypto_scrypt_smix_sse2.h \
           include/scrypt/insecure_memzero.h \
           include/scrypt/sysendian.h


SOURCES += uCryptLib.cpp \
           include/blake2/blake2b.c \
           include/blake2/blake2bp.c \
           include/blake2/blake2s.c \
           include/blake2/blake2sp.c \
           include/scrypt/cpusupport_x86_aesni.c \
           include/scrypt/cpusupport_x86_sse2.c \
           include/scrypt/crypto_scrypt.c \
           include/scrypt/sha256.c \
           include/scrypt/warnp.c \
           include/scrypt/crypto_scrypt_smix.c \
           include/scrypt/crypto_scrypt_smix_sse2.c \
           include/scrypt/insecure_memzero.c
