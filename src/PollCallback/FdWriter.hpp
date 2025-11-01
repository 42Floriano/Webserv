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

#include "PollableStream.hpp"

struct	FdWriter: public PollableStream
{
        int	write_error;
        bool nothing_to_write;
        std::string	missing_chunk;
        std::string chunk;

        virtual void		on_error_callback();
        virtual void		on_nothing_to_write_callback();
        virtual void		on_write_success_callback();
        virtual ssize_t		_write(char *buf, size_t buflen);
        void				_get_chunk(void);

        FdWriter(PollSet &pser, int fd, std::streambuf *buf);

private:
        void			_onPOLLOUT(void);
        void			_onPOLLERR(void);
};

#endif
