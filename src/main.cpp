/**
 * @file main.cpp
 * @author Angelo Elias Dalzotto (angelo.dalzotto@edu.pucrs.br)
 * @brief Partial HTTPS functionality implementation (key exchange and cryptography)
 * @version 0.1
 * @date 2022-06-21
 * 
 * @details Maiores informações e exemplo no README.md
 */

#include <iostream>
#include <algorithm>

#include <CLI/CLI.hpp>

#include "DiffieHellman.hpp"
#include "AES_CBC.hpp"

int main(int argc, char *argv[])
{
	/* Create a CLI parser */
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
		/* Check B string */
		if(B_str.size() != 256)
			throw std::invalid_argument("Invalid B size. Should be 256 characters.");

		/* Create a big integer from argument string */
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

		/* Generate 'A' and key */
		DiffieHellman dh(a, B);

		/* Get and print A */
		mpz_class A = dh.get_A();
		std::cout << std::hex << A << std::endl;

		/* Get and print key */
		std::string key = dh.get_key();
		std::cout << key << std::endl;

	} else if(reverse->parsed()){
		/* Check received key size */
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
