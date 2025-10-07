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

#include "CGIReader.hpp"

void	CGIReader::_onPOLLHUP(void)
{
        size_t contlen = this->_buffer.rdbuf()->in_avail();
        console::debug << "Avil in CGIHandler: " << contlen << std::endl;
        console::debug << "Headers are sealed? " << this->headers->is_sealed() <<
                       std::endl;
        std::stringstream ss;
        ss << contlen;
        this->headers->insert("Content-Length", ss.str());
        this->headers->seal();
        this->pset.removeCallback(POLLHUP, this);
}
