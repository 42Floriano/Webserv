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

#ifndef ADDRESS_STORAGE_HPP
# define ADDRESS_STORAGE_HPP

# include <string>
# include <sys/socket.h>

struct Address_storage
{

private:
        socklen_t				_storage_size;
        struct sockaddr_storage	_storage;

        std::string				_hoststr;
        std::string				_portstr;
        std::string				_unixpath;

public:	/* getters */
        int						family(void)		const;
        u_int32_t				host(void)			const;
        u_int16_t				port(void)			const;
        char					*path(void)			const;
        const std::string&		hoststr(void)		const;
        const std::string&		portstr(void)		const;
        socklen_t				len(void)			const;
        struct sockaddr			*ptr(void)			const;
        struct sockaddr_storage	*storage_ptr(void)	const;

public: /* setters */
        void					configure(const std::string &host, const std::string &port);
        void					configure(const std::string &host, u_int16_t port);
        void					configure(struct sockaddr *addr, socklen_t addrlen);
        void					getaddrinfo(void);
        void					setStorageSize(socklen_t size);
};

#endif
