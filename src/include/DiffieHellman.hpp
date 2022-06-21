#include <gmpxx.h>

class DiffieHellman
{
public:
	DiffieHellman(const mpz_class _a, const mpz_class _B);

	mpz_class get_A();
	mpz_class get_V();
	std::string get_key();

	/* RFC5114 prime number */
	static const mpz_class p;

	/* RFC5114 generator */
	static const mpz_class g;

private:
	void gen_A();
	void gen_V();
	void gen_key();

	const mpz_class a;
	const mpz_class B;

	mpz_class A;
	mpz_class V;

	std::string key;
};
