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

#include "PollSet.hpp"
#include "FdWriter.hpp"

ssize_t	FdWriter::_write(char *buf, size_t buflen)
{
        return ::write(this->fd, buf, buflen);
};

void FdWriter::_get_chunk(void)
{
        if (chunk.size() > 0)
                return;
        else
        {
                chunk.resize(this->BUFFER_SIZE + 1, 0);
                this->_buffer.read(&chunk[0], chunk.size() - 1);
                chunk.resize(this->_buffer.gcount());
        }
}

FdWriter::FdWriter(PollSet &pset, int fd, std::streambuf *buf):
        PollableStream(pset, fd, buf)
{
        pset.registerCallback(POLLOUT, this);
        //pset.registerCallback(POLLHUP, this);
        //pset.registerCallback(POLLERR, this);
}

void    FdWriter::_onPOLLERR(void)
{
        throw 42;
}

void	FdWriter::_onPOLLOUT(void)
{
        this->_get_chunk();
        console::error << "CHUNK: " << this->chunk << std::endl;

        if (chunk.size() > 0)
        {
                this->nothing_to_write = false;

                errno = 0;
                ssize_t writelen = this->_write(&chunk[0], chunk.size());
                this->write_error = errno;

                if (writelen == -1)
                {
                        console::error << strerror(this->write_error) << std::endl;
                        this->on_error_callback();
                }
                else
                {
                        console::error << "gm bro " << writelen << std::endl;
                        console::error << "gm bro " << chunk.size() << std::endl;
                        this->nothing_to_write = false;
                        chunk = chunk.substr(writelen);
                        this->on_write_success_callback();
                }
        }
        else
        {
                this->nothing_to_write = true;
                this->on_nothing_to_write_callback();
        }
}

void FdWriter::on_error_callback()
{
        console::error << "Failed to write" << std::endl;
        //throw 42;
}

void FdWriter::on_nothing_to_write_callback()
{
}

void FdWriter::on_write_success_callback()
{
}
