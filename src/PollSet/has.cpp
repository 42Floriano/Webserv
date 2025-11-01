#include "PollSet.hpp"

bool	PollSet::has(Callback cb)
{
        return this->index(cb) != -1;
}

bool	PollSet::has(int fd)
{
        for (int i = 0; i < this->_pollfdset; ++i)
        {
                if (this->_pollfdset.const_ptr()[i].fd == fd)
                        return true;
        }
        return (false);
}
