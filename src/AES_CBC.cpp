#include "AES_CBC.hpp"

#include <cryptopp/hex.h>
#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/osrng.h>

std::string AES_CBC::hex_decode(std::string encoded)
{
	std::string decoded;
	CryptoPP::StringSource decoder(
		encoded, 
		true,
		new CryptoPP::HexDecoder(
			new CryptoPP::StringSink(decoded)
		)
	);
	return decoded;
}

std::string AES_CBC::hex_encode(std::string decoded)
{
	std::string encoded;
	CryptoPP::StringSource encoder(
		reinterpret_cast<const CryptoPP::byte*>(decoded.data()), 
		decoded.size(), 
		true,
		new CryptoPP::HexEncoder(
			new CryptoPP::StringSink(encoded)
		)
	);
	return encoded;
}

AES_CBC::AES_CBC(const std::string _key) :
	key(hex_decode(_key))
{

}


std::string AES_CBC::decrypt(const std::string cyphertext)
{
	/* Decode hex message */
	const std::string dec_C = hex_decode(cyphertext);

	/* Separate IV from the first block of received message and remaining message */
	const std::string iv(dec_C, 0, CryptoPP::AES::BLOCKSIZE);
	const std::string c(dec_C, CryptoPP::AES::BLOCKSIZE, dec_C.length() - CryptoPP::AES::BLOCKSIZE);

	/* Set key and IV */
	CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption aes_dec;
	aes_dec.SetKeyWithIV(
		reinterpret_cast<const CryptoPP::byte*>(key.data()), 
		key.size(), 
		reinterpret_cast<const CryptoPP::byte*>(iv.data())
	);

	/* Decrypt */
	std::string plaintext;
	CryptoPP::StringSource ss(
		c,
		true, 
		new CryptoPP::StreamTransformationFilter(
			aes_dec,
			new CryptoPP::StringSink(plaintext)
		)
	);

	return plaintext;
}

std::string AES_CBC::encrypt(const std::string plaintext)
{
	/* Gen. random IV */
	CryptoPP::AutoSeededRandomPool prng;
	CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE);
	prng.GenerateBlock(iv, iv.size());

	/* Set key and IV */
	CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption aes_enc;
	aes_enc.SetKeyWithIV(
		reinterpret_cast<const CryptoPP::byte*>(key.data()), 
		key.size(), 
		iv
	);

	/* Encrypt */
	std::string cyphertext;
	CryptoPP::StringSource ss(
		reinterpret_cast<const CryptoPP::byte*>(plaintext.data()), 
		plaintext.size(), 
		true, 
		new CryptoPP::StreamTransformationFilter(
			aes_enc,
			new CryptoPP::StringSink(cyphertext)
		)
	);

	/* Concatenate random generated IV with cyphertext and encode to hex */
	const std::string striv(reinterpret_cast<char*>(iv.data()), iv.size());
	return hex_encode(striv+cyphertext);
}
