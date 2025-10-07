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

#ifndef ADDRESS_HPP
# define ADDRESS_HPP

/*
 *	Wrapper Class for diffent kind of socket addresses !!
 *
 *	In C socket addresses are typically stored inside
 *	a `struct sockaddr_storage`, which is passed
 *	to a socket-function through a pointer of type
 *	`struct sockaddr *`.
 *
 *	Hence, all C socket functions requiring an
 *	address, receive such argument via a pointer
 *	to an obfuscated structure `sockaddr` which points
 *	to a structure `sockaddr_storage`.
 *
 *	Type sockaddr_storage is implement as a union of
 *	types like (these are examples of specializations of
	sockaddr):
 *
 *	- struct sockaddr_un	(unix-domain sockets)
 *	- struct sockaddr_in	(ipV4 sockets)
 *	- struct sockaddr_in6	(ipV6 sockets)
 *
 *	Moral of the story, sometimes, the C socket
 *	api requires some casting and some usless
 *	lines of code to handle addresses.
 *
 *	For a usable C++ socket api, we must create
 *	a class `Address`. We want an omogeneous
 *	interfaces for all type of address we care
 *	about...
 *
 * */

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "Address_storage.hpp"

class Address:
        public Address_storage
{
public: /* constructors */
        Address(struct sockaddr *addr, socklen_t addrlen);
        Address(std::string host, std::string service);
        Address(std::string host, uint16_t port);
        Address(uint32_t host, uint16_t port);
        Address(std::string path);

public: /* orthodox canonical form */
        Address(void);
        Address(const Address &other);
        Address& operator=(const Address &rhs);
        ~Address(void);
};

/* Non member overload to properly print an Address on an output stream*/
std::ostream&	operator<<(std::ostream &output, const Address &address);
std::ostream&	operator<<(std::ostream &output, const Address *address);

/* Non member overload to deref an Address and obtain the sockaddr pointer */
//struct sockaddr	*operator&(const Address &address);

#endif
