project(
	'Diffie-Hellman', 
	'cpp', 
	default_options : ['cpp_std=c++17']
)

incdir = include_directories('src/include')

src = [
	'src/main.cpp', 
	'src/DiffieHellman.cpp',
	'src/AES_CBC.cpp'
]

gmpxx = dependency('gmpxx')
gmp = dependency('gmp')
cryptopp = dependency('libcryptopp')
if meson.get_compiler('cpp').has_header('CLI/CLI.hpp')
    CLI11_dep = declare_dependency()
else
    CLI11_dep = dependency(
        'CLI11',
        fallback: [ 'CLI11', 'CLI11_dep' ],
    )
endif


deps = [
	gmpxx,
	gmp,
	cryptopp,
	CLI11_dep
]

executable('dh', src, dependencies: deps, include_directories: incdir)
