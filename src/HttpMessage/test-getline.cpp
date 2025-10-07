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

#include "HttpMessage.hpp"
#include <sstream>
#include <iostream>

int	main()
{

        std::stringstream	_s;
        std::iostream		s(_s.rdbuf());
        std::string			buff;

        s << "Hello World\r\n";

        bool has_line = HttpMessage::getline(s, buff);
        std::cout << has_line << std::endl;
        std::cout << "Buf[" << buff << "]" << std::endl;
        return (0);
}
