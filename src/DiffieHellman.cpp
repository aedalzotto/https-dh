#include "DiffieHellman.hpp"
#include "AES_CBC.hpp"

#include <cryptopp/sha.h>

/* RFC5114 */
const mpz_class DiffieHellman::p(
	"B10B8F96A080E01DDE92DE5EAE5D54EC"
	"52C99FBCFB06A3C69A6A9DCA52D23B61"
	"6073E28675A23D189838EF1E2EE652C0"
	"13ECB4AEA906112324975C3CD49B83BF"
	"ACCBDD7D90C4BD7098488E9C219A7372"
	"4EFFD6FAE5644738FAA31A4FF55BCCC0"
	"A151AF5F0DC8B4BD45BF37DF365C1A65"
	"E68CFDA76D4DA708DF1FB2BC2E4A4371", 
	16
);

/* RFC5114 */
const mpz_class DiffieHellman::g(
	"A4D1CBD5C3FD34126765A442EFB99905"
	"F8104DD258AC507FD6406CFF14266D31"
	"266FEA1E5C41564B777E690F5504F213"
	"160217B4B01B886A5E91547F9E2749F4"
	"D7FBD7D3B9A92EE1909D0D2263F80A76"
	"A6A24C087A091F531DBF0A0169B6A28A"
	"D662A4D18E73AFA32D779D5918D08BC8"
	"858F4DCEF97C2A24855E6EEB22B3B2E5", 
	16
);

DiffieHellman::DiffieHellman(const mpz_class _a, const mpz_class _B) :
	a(_a),
	B(_B)
{
	gen_A();
	gen_V();
	gen_key();
}

void DiffieHellman::gen_A()
{
	/* A = g^a%p; */
	mpz_powm_sec(A.get_mpz_t(), g.get_mpz_t(), a.get_mpz_t(), p.get_mpz_t());
}

void DiffieHellman::gen_V()
{
	/* V = B^a%p; = g^(a*b) */
	mpz_powm_sec(V.get_mpz_t(), B.get_mpz_t(), a.get_mpz_t(), p.get_mpz_t());
}

void DiffieHellman::gen_key()
{
	CryptoPP::SHA256 hash;

	/* Convert bigint to an array of decoded bytes to use with CryptoPP */
	const std::string enc_V = V.get_str(16);
	const std::string dec_V = AES_CBC::hex_decode(enc_V);

	/* Compute SHA256 of V */
	key.resize(CryptoPP::SHA256::DIGESTSIZE);
	CryptoPP::SHA256().CalculateDigest(
		reinterpret_cast<CryptoPP::byte*>(key.data()), 
		reinterpret_cast<const CryptoPP::byte*>(dec_V.data()), 
		dec_V.size()
	);

	/* Get only the first 128 bits of SHA256 and encode to hex */
	key.resize(CryptoPP::SHA256::DIGESTSIZE/2);
	key = AES_CBC::hex_encode(key);
}

mpz_class DiffieHellman::get_A()
{
	return A;
}

mpz_class DiffieHellman::get_V()
{
	return V;
}

std::string DiffieHellman::get_key()
{
	return key;
}
