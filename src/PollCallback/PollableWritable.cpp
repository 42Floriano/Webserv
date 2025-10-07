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

#include "PollableWritable.hpp"

ssize_t	PollableWritable::_write(char *buf, size_t buflen)
{
        return ::write(this->fd(), buf, buflen);
};

std::string	PollableWritable::_get_chunk(void)
{
        if (missing_chunk.size() > 0)
                return missing_chunk;
        else
        {
                std::streamsize	chunk_len;
                std::string		str;

                str.resize(this->BUFFER_SIZE + 1, 0);
                this->_buffer.read(&str[0], str.size() - 1);
                chunk_len = this->_buffer.gcount();
                if (chunk_len > 0)
                {
                        str.resize(chunk_len);
                        return (str);
                }
                else
                {
                        return std::string();
                }
        }
}

PollableWritable::PollableWritable(int fd, std::streambuf *buf):
        PollableFile(POLL_WRITABLE_FILE, fd, buf)
{

}

void	PollableWritable::on_error_callback(int e)
{
        (void) e;
};

void	PollableWritable::_onPOLLOUT(void)
{
        int			err;
        ssize_t		writelen;
        std::string chunk = this->_get_chunk();

        if (chunk.size() > 0)
        {
                errno = 0;
                writelen = this->_write(&chunk[0], chunk.size());
                err = errno;

                switch (writelen)
                {
                case -1:
                        this->on_error_callback(err);
                        break;
                default:
                        if (writelen < (ssize_t) chunk.size())
                        {
                                this->missing_chunk = chunk.substr(writelen);
                        }
                        this->on_write_success_callback();
                }

        }
        else
        {
                this->on_nothing_to_write_callback();
        }
}
