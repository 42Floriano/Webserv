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

#ifndef _COLOR_HPP
# define _COLOR_HPP

#include <string>

class color
{

public:
        class ansi
        {
        public:
                static const std::string	yellow;
                static const std::string	green;
                static const std::string	blue;
                static const std::string	red;
                static const std::string	magenta;
                static const std::string	cyan;
                static const std::string	dflt;
        };
};

#endif
