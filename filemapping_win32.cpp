#include "filemapping.h"

#include <windows.h>

using namespace std;

namespace symreader
{
	shared_ptr<const mapped_region> map_file(const char *path)
	{
		struct mapping : mapped_region
		{
			mapping(const char *path)
				: file(::CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL), &::CloseHandle)
			{
				second = ::GetFileSize(file.get(), NULL);
				file_mapping.reset(::CreateFileMapping(file.get(), NULL, PAGE_READONLY, 0, second, NULL), &::CloseHandle);
				first = ::MapViewOfFile(file_mapping.get(), FILE_MAP_READ, 0, 0, second);
			}

			~mapping()
			{	::UnmapViewOfFile(first);	}

			shared_ptr<void> file, file_mapping;
		};
		
		return shared_ptr<mapping>(new mapping(path));
	}
}
