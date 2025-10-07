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

bool HttpMessage::getchunk(std::istream &is, std::string &buf)
{

        if (is.rdbuf()->in_avail() >= (std::streamsize)buf.size() + 2)
        {
                is.read((char *)buf.data(), buf.size());
                /* TODO: verify here that it ends with CRLF instead of */
                is.ignore(2);
                // The line below is called after this function (that is now static)
                // this->_decoding_phase = HttpMessage::reading_chunk_size;
                return (true);
        }
        return (false);
};
