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
#include "HttpMessage.hpp"

bool HttpMessage::getline(std::istream &is, std::string &dst)
{
        console::debug << "getline" << std::endl;
        char c = 0;

        is.clear();
        while (is.good())
        {
//				console::debug << "Getline: In avail before get char: " << is.rdbuf()->in_avail() << std::endl;
                is.get(c);
//				console::debug << "Getline: In avail after get char: " << is.rdbuf()->in_avail() << std::endl;
                if (!is.good())
                        return false;
                dst += c;
                if (dst.size() >= 2 && dst.find("\r\n") != std::string::npos)
                {
                        size_t pos = dst.find("\r\n");
                        if (pos != std::string::npos)
                                dst.erase(pos);
                        return true;
                }
        }
        return false;
}
