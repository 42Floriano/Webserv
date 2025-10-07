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

#ifndef POLLSOCK_HPP
# define POLLSOCK_HPP

/*
 *	Definition of the PollSock class.
 *
 *	It implements both the PollCallback and Socket interface
 *	by inheriting from both.
 *
 * */

# include "Console.hpp"
# include "SimpleSet.hpp"
# include "PollSet.hpp"
# include "Socket.hpp"
# include "PollCallback.hpp"

class PollSock: public PollCallback, public Socket
{

public:		// constructors
        PollSock(PollSet &pset, int domain, int type, int protocol);
        PollSock(PollSet &pset, int fd, Address *addr);
        ~PollSock();

public:	// private fields
        PollSet&			_pset;
        int					_reserved_fd;

protected:	// PollCallback overloads
        void				_onPOLLIN(void);
        void				_onPOLLOUT(void);
        void				_onPOLLERR(void);
        void				_onPOLLHUP(void);

public: //Socket overloads
        void				listen(int backlog = 4096);
        void				listen(const std::string &host,
                        const std::string &port, int backlog = 4096);

public:	// Customizable methods;
        virtual void		onConnection(int clientfd, Address *clientaddr);
        virtual void		onDisconnect(void);
        virtual void		onError(void);
        virtual void		onData(void);
        virtual void		onWritable(void);
        int					fd(void) const;
};

#endif
