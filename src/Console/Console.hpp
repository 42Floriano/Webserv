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

#ifndef CONSOLE_HPP
# define CONSOLE_HPP


#include "color.hpp"
#include "ConsoleBuffer.hpp"

class Console: public std::ostream
{
private:
        ConsoleBuffer	*_inner_buffer;
public:
        Console(ConsoleBuffer *buffer);
        ~Console(void);

        ConsoleBuffer	*inner_buffer(void);
        Console&		operator()(const std::string &s);
        Console&		operator++();
        Console&		operator--();
        void			on(void);
        void			off(void);
};

#include "_console.hpp"

#endif
