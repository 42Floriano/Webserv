/*

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU Affero General Public License as
 published by the Free Software Foundation, either version 3 of the
 License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Affero General Public License for more details.

 You should have received a copy of the GNU Affero General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#ifndef POLLABLEWRITABLE_HPP
# define POLLABLEWRITABLE_HPP

#include <unistd.h>
#include <string>
#include <cerrno>

#include "PollableFile.hpp"

class	PollableWritable: public PollableFile
{

private:
        std::string	missing_chunk;

private:
        virtual void		on_error_callback(int e);
        virtual void		on_nothing_to_write_callback() = 0;
        virtual void		on_write_success_callback() = 0;
        virtual ssize_t		_write(char *buf, size_t buflen);
        virtual	std::string	_get_chunk(void);

public:
        PollableWritable(int fd, std::streambuf *buf);

private:
        void			_onPOLLOUT(void);
};

#endif
