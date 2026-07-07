#pragma once

namespace Velvet {
    class RefCounted
    {
    public:
        U16 GetRefCount() const { return m_RefCount; }
        U16 GetScopeCount() const { return m_RefCount; }

    private:
        void IncRefCount() { m_RefCount++; }
        void DecRefCount() { m_RefCount--; }

        void IncScopeCount() { m_ScopeCount++; }
        void DecScopeCount() { m_ScopeCount--; }

    private:
        // TODO: Make these atomic?
        U16 m_RefCount = 0;
        U16 m_ScopeCount = 0;

        template<typename T>
        friend class Ref;
        template<typename T>
        friend class Scope;
        // TODO: Create Weak class
        template<typename T>
        friend class Weak;
    };

    template<typename T>
    class Ref;
    template<typename T>
    class Scope;
    // TODO: Create Weak class
    template<typename T>
    class Weak;
    template<typename T>

    class Ref
    {
    public:
        Ref(std::nullptr_t) {}

        Ref& operator=(std::nullptr_t)
        {
            Destroy();
            return *this;
        }

        ~Ref() { Destroy(); }

        Ref(const Ref& other) : m_Data(other.m_Data)
        {
            if (m_Data)
                m_Data->IncRefCount();
        }

        Ref& operator=(const Ref& other)
        {
            if (this == &other)
                return *this;

            Destroy();

            m_Data = other.m_Data;
            if (m_Data)
                m_Data->IncRefCount();

            return *this;
        }

        Ref(Ref&& rhs) noexcept : m_Data(rhs.m_Data) { rhs.m_Data = nullptr; }

        Ref& operator=(Ref&& rhs) noexcept
        {
            if (this == &rhs)
                return *this;

            Destroy();

            m_Data = rhs.m_Data;
            rhs.m_Data = nullptr;

            return *this;
        }

        Ref(const Scope<T>& scope) : m_Data(scope.m_Data)
        {
            if (m_Data)
                m_Data->IncRefCount();
        }

        Ref& operator=(const Scope<T>& scope)
        {
            m_Data = scope.m_Data;

            if (m_Data)
                m_Data->IncRefCount();

            return *this;
        }

        template<typename U>
            requires std::is_convertible_v<U*, T*>
        Ref(const Ref<U>& other) : m_Data(other.m_Data)
        {
            if (m_Data)
                m_Data->IncRefCount();
        }

        template<typename U>
            requires std::is_convertible_v<U*, T*>
        Ref& operator=(const Ref<U>& other)
        {
            Destroy();

            m_Data = other.m_Data;
            if (m_Data)
                m_Data->IncRefCount();

            return *this;
        }

        template<typename U>
            requires std::is_convertible_v<U*, T*>
        Ref(Ref<U>&& rhs) : m_Data(rhs.m_Data)
        {
            rhs.m_Data = nullptr;
        }

        template<typename U>
            requires std::is_convertible_v<U*, T*>
        Ref& operator=(Ref<U>&& rhs)
        {
            if (this == &rhs)
                return *this;

            Destroy();

            m_Data = rhs.m_Data;
            rhs.m_Data = nullptr;

            return *this;
        }

        T& operator*() { return *m_Data; }
        const T& operator*() const { return *m_Data; }

        T* operator->() { return m_Data; }
        const T* operator->() const { return m_Data; }

        T* Raw() { return m_Data; }

        template<typename... Args>
        static Ref<T> Create(Args... args)
        {
            return Ref(new T(std::forward<Args>(args)...));
        }

        void Destroy()
        {
            if (m_Data)
            {
                m_Data->DecRefCount();
                if (m_Data->GetRefCount() == 0 && m_Data->GetScopeCount() == 0)
                    delete m_Data;

                m_Data = nullptr;
            }
        }

    private:
        Ref(T* data) : m_Data(data)
        {
            if (m_Data)
                m_Data->IncRefCount();
        }

    private:
        T* m_Data = nullptr;

        template<typename U>
        friend class Ref;
        template<typename U>
        friend class Scope;
        template<typename U>
        friend class Weak;
    };

    template<typename T>
    class Scope
    {
    public:
        ~Scope() { Destroy(); }

        Scope(std::nullptr_t) {}
        Scope& operator=(std::nullptr_t)
        {
            Destroy();
            return *this;
        }

        Scope(const Scope&) = delete;
        Scope& operator=(const Scope&) = delete;

        Scope(Scope&& rhs) noexcept : m_Data(rhs.m_Data) { rhs.m_Data = nullptr; }
        Scope& operator=(Scope&& rhs) noexcept
        {
            if (this == &rhs)
                return *this;

            Destroy();

            m_Data = rhs.m_Data;
            rhs.m_Data = nullptr;

            return *this;
        }

        template<typename U>
            requires std::is_convertible_v<U*, T*>
        Scope(Scope<U>&& rhs) : m_Data(rhs.m_Data)
        {
            rhs.m_Data = nullptr;
        }

        template<typename U>
            requires std::is_convertible_v<U*, T*>
        Scope& operator=(Scope<U>&& rhs)
        {
            if (this == &rhs)
                return *this;

            Destroy();

            m_Data = rhs.m_Data;
            rhs.m_Data = nullptr;

            return *this;
        }

        T& operator*() { return *m_Data; }
        const T& operator*() const { return *m_Data; }

        T* operator->() { return m_Data; }
        const T* operator->() const { return m_Data; }

        T* Raw() { return m_Data; }

        template<typename... Args>
        static Scope Create(Args... args)
        {
            return Scope(new T(std::forward<Args>(args)...));
        }

        void Destroy()
        {
            if (m_Data)
            {
                m_Data->DecScopeCount();
                delete m_Data;

                m_Data = nullptr;
            }
        }

    private:
        Scope(T* data) : m_Data(data)
        {
            if (m_Data)
                m_Data->IncScopeCount();
        }

    private:
        T* m_Data = nullptr;

        template<typename U>
        friend class Ref;
        template<typename U>
        friend class Scope;
        template<typename U>
        friend class Weak;
    };
} // namespace Velvet
