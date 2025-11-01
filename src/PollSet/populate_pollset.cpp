#include "PollSet.hpp"

void	PollSet::populate_pollset(void)
{
        CallbackDB::iterator it = _callbacks.begin();

        for (; it != _callbacks.end(); ++it)
        {
                short events_to_listen_to = 0;
                EventEmitter emitter = it->first;

                CallbackMap::iterator jt = it->second.begin();

                for (; jt != it->second.end(); ++jt)
                {
                        Event event = jt->first;
                        CallbackVec cbvec = jt->second;
                        if (cbvec.size() > 0)
                                events_to_listen_to |= event;
                }
                if (events_to_listen_to > 0)
                {
                        this->_pollfdset.add((pollfd)
                        {
                                emitter, events_to_listen_to, 0
                        });
                }
        }
}

void	PollSet::empty_pollset(void)
{
        while (this->_pollfdset.size() > 0)
        {
                this->_pollfdset.remove(this->_pollfdset.size() - 1);
        }
}

void	PollSet::delete_callback(Callback cb)
{
        this->_garbage.insert(cb);
}

void	PollSet::cleanup_garbage()
{
        std::set<Callback>::iterator it = this->_garbage.begin();

        for (; it != this->_garbage.end(); ++it)
        {

                this->removeCallback(*it);
                delete *it;
        }
        this->_garbage.erase(this->_garbage.begin(), this->_garbage.end());
}
