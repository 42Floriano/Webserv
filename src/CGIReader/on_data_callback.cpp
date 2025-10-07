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
#include "CGIReader.hpp"

void	CGIReader::on_data_callback(void)
{
        this->FdReader::on_data_callback();
        this->_buffer.clear();
        console::debug << "Avil in CGIHandler: " << this->_buffer.rdbuf()->in_avail() <<
                       std::endl;
        console::debug << "CGIReader::on_data_callback() START" << std::endl;
        ++console::debug;
        if (!this->headers->is_sealed() && this->headers_parsed == false)
        {
                console::debug << "Trying to parse headers" << std::endl;
                while (HttpMessage::getline(this->_buffer, this->line_buffer))
                {
                        console::debug << "Header line: " << this->line_buffer << std::endl;
                        try
                        {
                                this->headers->parse(this->line_buffer);
                        }
                        catch (const std::exception &err)
                        {
                                //throw std::runtime_error("CGIReader: headers parsing failed");,
                                break ;
                        }
                        this->line_buffer.clear();
                        if (this->headers->is_sealed())
                                break;
                }
                if (this->headers->is_sealed())
                {
                        this->headers->unseal();
                        this->headers_parsed = true;
                }
        }
        else
                console::debug << "No headers to parse" << std::endl;
        --console::debug;
        console::debug << "CGIReader::on_data_callback() END" << std::endl;
        console::debug << "Avil in CGIHandler: " << this->_buffer.rdbuf()->in_avail() <<
                       std::endl;
}
