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

#ifndef CONSOLEBUFFER_HPP
# define CONSOLEBUFFER_HPP

# include <ctime>
# include <iostream>
# include <sstream>
# include <string>

class	ConsoleBuffer: public std::stringbuf
{
private:
        bool			_active;
        unsigned int	_indent_level;
        std::string		_name;
        std::string		_prefix;
        std::ostream&	_output;

public:
        ConsoleBuffer(std::ostream &output, const std::string &name);
        ~ConsoleBuffer(void);

public:
        void			on(void);
        void			off(void);
        void			prefix(const std::string &s);
        int				sync();
        ConsoleBuffer&	operator++(void);
        ConsoleBuffer&	operator--(void);
};

#endif
