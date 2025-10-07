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

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "Client_config.hpp"

#include "PollSock.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include <sstream>

class Client: public PollCallback, public Socket
{
public:
        PollSet& _pset;

        size_t buffer_size;
        size_t byteswritten;
        size_t bytesread;
        std::string rchunk;
        std::string wchunk;
        std::stringstream rbuf;
        std::stringstream wbuf;

        Client(PollSet &pset, int fd, Address *addr);

        int	fd() const;
        void destroy(void);

        virtual void onData(void) = 0;
        virtual void onWritable(void) = 0;
        virtual void onDisconnect(void);
        virtual void onError(void);
        virtual void on_nothing_to_write(void) = 0;

private:
        void _onPOLLIN(void);
        void _onPOLLOUT(void);
        void _onPOLLERR(void);
        void _onPOLLHUP(void);
        void dispatch_wchunk(void);
        void prepare_wchunk(void);
};

#endif
