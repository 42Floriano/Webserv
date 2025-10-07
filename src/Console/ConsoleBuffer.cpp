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

#include "ConsoleBuffer.hpp"

ConsoleBuffer::ConsoleBuffer(std::ostream &output, const std::string &name):
        _active(true),
        _indent_level(0),
        _name(name),
        _prefix(""),
        _output(output) {};

ConsoleBuffer::~ConsoleBuffer(void)
{
        // Flushes the buffer when deconstructing
        if (this->_active && this->in_avail() > 0)
        {
                this->sync();
        }
};

void	ConsoleBuffer::on(void)
{
        this->_active = true;
};

void	ConsoleBuffer::off(void)
{
        this->_active = false;
};

void	ConsoleBuffer::prefix(const std::string &s)
{
        this->_prefix = s;
};

ConsoleBuffer&	ConsoleBuffer::operator++(void)
{
        this->_indent_level += 8;
        return (*this);
};

ConsoleBuffer&	ConsoleBuffer::operator--(void)
{
        this->_indent_level -= 8;
        return (*this);
};

int	ConsoleBuffer::sync()
{
        time_t ts = time(NULL);
        tm		*hts = localtime(&ts);
        //std::string	timestamp(ctime(&ts));
        //timestamp.erase(timestamp.size() - 1);
        if (this->_active)
        {
                _output
                                << "["
                                <<  hts->tm_hour << ":"
                                << hts->tm_min << ":"
                                << hts->tm_sec
                                << "]"
                                << " - "
                                << '[' << this->_name << ']'
                                << ": "
                                << std::string(this->_indent_level, ' ')
                                << _prefix << (_prefix.empty() ? "" : ": ")
                                << this;
                //<< ": " << _postfix
                //<< "\n";
        }
        return (0);
};
