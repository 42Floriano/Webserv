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

#ifndef SIMPLESET_HPP
# define SIMPLESET_HPP

#include <cstddef>
#include "Console.hpp"

template<typename Item, size_t MAX_SIZE>
class SimpleSet
{

protected:
        static const size_t	_capacity = MAX_SIZE;
        Item				_data[MAX_SIZE];
        size_t				_size;

public:
        SimpleSet(void);
        SimpleSet& operator=(const SimpleSet &rhs);
        virtual ~SimpleSet(void);

public:
        void		add(const Item &item);
        void		remove(size_t index);
        size_t		size(void) const;
        Item		*ptr(void);
        const Item	*const_ptr(void) const
        {
                return this->_data;
        };
        int			index(const Item &item);
};

#include "SimpleSet.tpp"

#endif
