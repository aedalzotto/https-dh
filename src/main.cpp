#include <iostream>
#include <algorithm>

#include <CLI/CLI.hpp>

#include "DiffieHellman.hpp"
#include "AES_CBC.hpp"

int main(int argc, char *argv[])
{
	CLI::App app{"Partial HTTPS functionality example."};

	/* Require 1 subcommand */
	app.require_subcommand(1, 1);

	/* Add 2 subcommands: keygen and reverse */
	CLI::App *keygen = app.add_subcommand("keygen", "Generate a key based on received B and generated A");
	CLI::App *reverse = app.add_subcommand("reverse", "Decrypt a CYPHERTEXT, reverse it, and reencrypt using a KEY.");

	/* Keygen options */
	std::string B_str;
	keygen->add_option("B", B_str, "B value computed from p, g, and b.")->required();

	/* Reverse options */
	std::string cyphertext;
	reverse->add_option("CYPHERTEXT", cyphertext, "Cyphertext to modify.")->required();

	std::string key;
	reverse->add_option("KEY", key, "AES key.")->required();

	try {
    	app.parse(argc, argv);
	} catch (const CLI::ParseError &e) {
		return app.exit(e);
	}

	if(keygen->parsed()){
		if(B_str.size() != 256)
			throw std::invalid_argument("Invalid B size. Should be 256 characters.");

		const mpz_class B(
			B_str,
			16
		);

		/* Chosen 'a' value */
		const mpz_class a(
			"69696969696969696969696969696969"
			"69696969696969696969696969696969"
			"69696969696969696969696969696969"
			"69696969696969696969696969696969"
			"69696969696969696969696969696969"
			"69696969696969696969696969696969"
			"69696969696969696969696969696969"
			"69696969696969696969696969696969", 
			16
		);

		DiffieHellman dh(a, B);

		mpz_class A = dh.get_A();
		std::cout << std::hex << A << std::endl;

		std::string key = dh.get_key();
		std::cout << key << std::endl;
	} else if(reverse->parsed()){
		if(key.size() != 32)
			throw std::invalid_argument("Invalid KEY size. Should be 32 characters.");

		AES_CBC aes(key);

		/* Decrypt cyphertext */
		std::string plaintext = aes.decrypt(cyphertext);
		std::cout << plaintext << std::endl;	

		/* Reverse decrypted message */
		std::reverse(plaintext.begin(), plaintext.end());
		// std::cout << plaintext << std::endl;

		/* Encrypt reversed string */
		std::string cypherans = aes.encrypt(plaintext);
		std::cout << cypherans << std::endl;

		/* Decrypt the reversed string just to be sure */
		// plaintext = aes.decrypt(cypherans);
		// std::cout << plaintext << std::endl;
	}

	return EXIT_SUCCESS;
}
