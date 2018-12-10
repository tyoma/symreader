#include "sym-elf.h"

#include "filemapping.h"

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

int main(int argc, const char *argv[])
{
	if (argc < 2)
		return -1;

	shared_ptr<const symreader::mapped_region> image = symreader::map_file(argv[1]);

	cout << hex << setfill('0');
	//symreader::read_sections(&image[0], image.size(), [] (const symreader::section &s) {
	//	cout << "Section: " << s.name << endl;
	//	cout << "	Index: " << setw(8) << s.index << endl;
	//	cout << "	Virtual address: " << setw(8) << s.virtual_address << endl;
	//	cout << "	File offset: " << setw(8) << s.file_offset << endl;
	//	cout << "	Size: " << setw(8) << s.size << endl;
	//	cout << "	Entry size: " << setw(8) << s.entry_size << endl;
	//	cout << endl;
	//});

	symreader::read_symbols(image->first, image->second, [] (const symreader::symbol &s) {
		cout << s.name << "\t" << setw(8) << s.virtual_address << "\t" << setw(8) << s.size << endl;
	});
}
