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

#include <iostream>
#include <cstring>
#include "PollableReadable.hpp"

void	PollableReadable::on_data_callback(void)
{
        console::debug << "PollReadable::on_data_callback" << std::endl;
};

void	PollableReadable::on_eof_callback(void)
{
        console::debug << "PollReadable::on_eof_callback" << std::endl;
};

void	PollableReadable::on_error_callback(int e)
{
        console::debug << "PollReadable::on_error_callback" << std::endl;
		console::error << "Read error: " << strerror(e) << std::endl;
};

ssize_t	PollableReadable::_read(char *buf, size_t buflen)
{
        return ::read(this->fd(), buf, buflen);
};

PollableReadable::PollableReadable(int fd,
                                   std::streambuf *buff): PollableFile(POLL_READABLE_FILE,
                                                           fd, buff), bytesread(0)
{

};

/*
#include <stdio.h>
void	raw_print(std::ostream &os, char *data, size_t len) {
	printf("Data: %*s\n", (int)len, data);
	os << "Data< ";
	for (size_t i = 0; i < len - 1; i++)
		os << data[i] << ", ";
	os << data[len - 1] << ">";
	os << std::endl;
	console::debug << "salut" << std::endl;
}
*/

void	PollableReadable::_onPOLLIN(void)
{

        char	*buf = new char[this->BUFFER_SIZE + 1];
        ssize_t	readlen;

        errno = 0;
        readlen = this->_read(buf, this->BUFFER_SIZE);
        int	err = errno;

        switch (readlen)
        {
        case 0:
                console::debug << "EOF on fd " << this->fd() << std::endl;
                this->on_eof_callback();
                break;
        case -1:
                console::debug << "Read error on fd " << this->fd() << std::endl;
                this->on_error_callback(err);
                break;
        default:
                this->_buffer.clear();
                console::debug
                                << "Succesfull read on fd " << this->fd()
                                << ", readlen = " << readlen << std::endl;
                this->bytesread += readlen;
                size_t x = this->_buffer.tellp();
                this->_buffer.write(buf, readlen);
                size_t y = this->_buffer.tellp();
                console::debug << "x: " << x << std::endl;
                console::debug << "y: " << y << std::endl;
                this->on_data_callback();
                break;
        }
        delete[] buf;
}
