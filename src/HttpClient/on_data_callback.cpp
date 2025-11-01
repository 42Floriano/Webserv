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

#include "HttpClient.hpp"
#include "ResponseHandler.hpp"

void	HttpClient::on_data_callback(void)
{
        if (this->req._decoding_phase != HttpMessage::decoding_done)
        {
                try
                {
                        HttpMessage::decode(this->req);
                }
                catch (const std::exception &err)
                {
                        this->req._decoding_phase = HttpMessage::decoding_error;
                }
        }

        if (this->req._decoding_phase > HttpMessage::decoding_header
                        && this->handled == false)
        {
                this->handleResponse();
                this->pset.registerCallback(POLLOUT, this);
                this->handled = true;
        }

        if (this->req._decoding_phase == HttpMessage::decoding_done)
        {
                this->pset.removeCallback(POLLIN, this);
        }
}
