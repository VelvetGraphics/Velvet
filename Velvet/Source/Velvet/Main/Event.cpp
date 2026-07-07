#include "Event.hpp"

namespace Velvet {
    void EventBus::Dispatch()
    {
        std::swap(m_Back, m_Front);
        m_Back.clear();

        for (Scope<Event>& e : m_Front)
        {
            auto it = m_Subscribers.find(e->GetType());
            if (it == m_Subscribers.end())
                continue;

            for (EventFn& fn : it->second)
                fn(*e);
        }
    }
} // namespace Velvet
