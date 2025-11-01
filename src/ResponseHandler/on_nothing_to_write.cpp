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

#include "ResponseHandler.hpp"

static bool	we_are_done(Request &req, Response &res)
{
        if (req._decoding_phase < HttpMessage::decoding_done)
                return false;
        if (res._encoding_phase != HttpMessage::encoding_done)
                return false;
        return true;
}

void ResponseHandler::on_nothing_to_write(void)
{
        if (we_are_done(this->req, this->res))
        {
                if (this->internal_handler)
                {
                        this->unregister_internal_handler();
                        this->close_internal_handler();
                        this->delete_internal_handler();
                }
                this->unregister();
                this->PollCallback::close();
                delete this;
        }
}
