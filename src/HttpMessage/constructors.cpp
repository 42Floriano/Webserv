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

HttpMessage::HttpMessage(std::stringbuf &s) : std::iostream(&s)
{
        this->_decoding_phase = 0;
        this->_encoding_phase = 0;
        this->_header_bytelen = 0;
        this->_content_length = 0;
        this->current_body_size = 0;
}

HttpMessage::~HttpMessage(void) {}
