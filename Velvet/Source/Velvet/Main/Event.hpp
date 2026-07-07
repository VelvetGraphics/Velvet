#pragma once
#include "Velvet/Common/CommonInclude.hpp"

namespace Velvet {
    class Event;
    using EventFn = std::function<void(Event&)>;

    namespace EventCategory {
        // TODO: Bit macro
        enum Category
        {
            None = 0,
            Application = 1 << 0,
            Window = 1 << 1,
            Input = 1 << 2,
            Renderer = 1 << 3,
        };
    } // namespace EventCategory

    // TODO: Implement more event types
    enum class EventType
    {
        None = 0,

        WindowClosed,
        WindowMoved,
        WindowResized,
        WindowFocused,
        WindowLostFocus,
        WindowMinimized,
        WindowUnMinimized,

        KeyPressed,
        KeyReleased,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled
    };

    class Event : public RefCounted
    {
    public:
        bool Handled = false;

        virtual EventType GetType() = 0;
        virtual EventCategory::Category GetCateGory() = 0;

#define EVENT_TYPE_FUNCTIONS(type)                                                                                     \
    EventType GetType() override { return type; }                                                                      \
    static EventType Type() { return type; }

#define EVENT_CATEGORY_FUNCTION(category)                                                                              \
    EventCategory::Category GetCateGory() override { return category; }

    public:
        virtual ~Event() = default;

    protected:
        Event() = default;
    };

    class EventBus final
    {
    public:
        EventBus() = default;
        ~EventBus() = default;

        EventBus(const EventBus&) = delete;
        EventBus& operator=(const EventBus&) = delete;

        EventBus(EventBus&&) = default;
        EventBus& operator=(EventBus&&) = default;

        void Queue(Scope<Event>&& event) { m_Back.push_back(std::move(event)); }
        void Dispatch();

        template<typename T>
            requires std::derived_from<T, Event>
        void Subscribe(EventFn fn)
        {
            m_Subscribers[T::Type()].push_back(fn);
        }

    private:
        std::vector<Scope<Event>> m_Front;
        std::vector<Scope<Event>> m_Back;

        std::unordered_map<EventType, std::vector<EventFn>> m_Subscribers;
    };
} // namespace Velvet
