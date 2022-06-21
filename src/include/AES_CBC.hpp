#include <string>

class AES_CBC {
public:
	static std::string hex_decode(std::string encoded);
	static std::string hex_encode(std::string decoded);

	AES_CBC(const std::string _key);

	std::string decrypt(const std::string cyphertext);
	std::string encrypt(const std::string plaintext);

private:
	const std::string key;

};
