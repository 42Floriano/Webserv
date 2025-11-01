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
#include "FdReader.hpp"
#include "PollSet.hpp"

void	FdReader::on_data_callback()
{
};

void	FdReader::on_eof_callback()
{
        console::debug << "EOF on fd " << this->fd << std::endl;
        this->unregister();
};

void	FdReader::on_read_error_callback()
{
        console::error << "Read error on fd " << this->fd
                       << ": " << strerror(this->read_error) << std::endl;
};

ssize_t	FdReader::_read(char *buf, size_t buflen)
{
        return ::read(this->fd, buf, buflen);
};

FdReader::FdReader(PollSet &pset, int fd, std::streambuf *buff):
        PollableStream(pset, fd, buff),
        eof(false),
        bytesread(0),
        read_error(0)
{
        pset.registerCallback(POLLIN, this);
        //pset.registerCallback(POLLHUP, this); DO NOT WRITE THIS LINE FFS
        pset.registerCallback(POLLERR, this);
};

FdReader::~FdReader(void)
{
        ::close(this->fd);
}

void	FdReader::_onPOLLIN(void)
{
        chunk.resize(this->BUFFER_SIZE, 0);

        errno = 0;
        ssize_t readlen = this->_read(&chunk[0], this->BUFFER_SIZE);
        this->read_error = errno;

        switch (readlen)
        {
        case 0:

                this->eof = true;
                this->on_eof_callback();
                break;

        case -1:
                this->on_read_error_callback();
                break;

        default:
                console::debug
                                << "Succesfull read on fd " << this->fd
                                << " readlen = " << readlen << std::endl;

                this->bytesread += readlen;
                chunk.resize(readlen);
                this->_buffer.clear();
                this->_buffer.write(&chunk[0], readlen);
                this->on_data_callback();
                break;
        }
}
