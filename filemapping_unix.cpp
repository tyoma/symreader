#include "filemapping.h"

#include <fcntl.h>
#include <new>
#include <stdexcept>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

namespace symreader
{
	shared_ptr<const mapped_region> map_file(const char *path)
	{
		struct mapping : mapped_region
		{
			mapping(const char *path)
				: mapped_region(0, 0)
			{
				if ((file = ::open(path, O_RDONLY)) >= 0)
				{
					struct stat st;

					if (::fstat(file, &st) >= 0)
					{
						second = static_cast<size_t>(st.st_size);
						first = ::mmap(0, second, PROT_READ, MAP_PRIVATE, file, 0);
						if (first != MAP_FAILED)
							return;
					}
					close(file);
					throw bad_alloc();
				}
				else
				{
					throw invalid_argument("");
				}
			}

			~mapping()
			{
				::munmap((void *)first, second);
				::close(file);
			}

			int file;
		};

		return shared_ptr<mapping>(new mapping(path));
	}
}
