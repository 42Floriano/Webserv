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

#include "Console.hpp"
#include <iostream>

template<typename Item, size_t MAX_SIZE>
SimpleSet<Item, MAX_SIZE>::SimpleSet(void): _size(0)
{
}

template<typename Item, size_t MAX_SIZE>
SimpleSet<Item, MAX_SIZE>& SimpleSet<Item, MAX_SIZE>::operator=
(const SimpleSet &rhs)
{
        this->_size = rhs._size;

        for (int i = 0; i < this->_size; i++)
        {
                this->_data[i] = rhs._data[i];
        }
}

template<typename Item, size_t MAX_SIZE>
SimpleSet<Item, MAX_SIZE>::~SimpleSet(void)
{
}

template<typename Item, size_t MAX_SIZE>
void	SimpleSet<Item, MAX_SIZE>::add(const Item &item)
{
        if (this->_size < this->_capacity)
        {

                this->_data[this->_size] = item;
                this->_size++;
        }
}

template<typename Item, size_t MAX_SIZE>
void	SimpleSet<Item, MAX_SIZE>::remove(size_t index)
{
        if (this->_size > 0)
        {
                if (index != this->_size - 1)
                        this->_data[index] = this->_data[this->_size - 1];
                this->_size--;
        }
}

template<typename Item, size_t MAX_SIZE>
size_t	SimpleSet<Item, MAX_SIZE>::size(void) const
{
        return (this->_size);
}

template<typename Item, size_t MAX_SIZE>
Item	*SimpleSet<Item, MAX_SIZE>::ptr(void)
{
        return (this->_data);
}

template<typename Item, size_t MAX_SIZE>
int		SimpleSet<Item, MAX_SIZE>::index(const Item &item)
{
        int	i = 0;
        while (i < this->size())
        {
                if (this->_data[i] == item)
                        return (i);
                i++;
        }
        return (-1);
}
