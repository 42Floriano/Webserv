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

#include "Console.hpp"

ConsoleBuffer	*Console::inner_buffer(void)
{
        return this->_inner_buffer;
};

Console::Console(ConsoleBuffer *buffer):
        std::ostream(buffer),
        _inner_buffer(buffer) {};

Console::~Console(void)
{

};

Console&	Console::operator()(const std::string &s)
{
        this->_inner_buffer->prefix(s);
        return (*this);
};

Console&	Console::operator++()
{
        this->inner_buffer()->operator++();
        return (*this);
};

Console&	Console::operator--()
{
        this->inner_buffer()->operator--();
        return (*this);
};

void	Console::on(void)
{
        this->inner_buffer()->on();
};

void	Console::off(void)
{
        this->inner_buffer()->off();
};
