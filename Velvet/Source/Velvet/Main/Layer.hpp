#pragma once
#include "Velvet/Common/CommonInclude.hpp"

namespace Velvet {
    class Layer
    {
    public:
        virtual ~Layer() = default;

        Layer(const Layer&) = delete;
        Layer& operator=(const Layer&) = delete;

        Layer(Layer&&) = default;
        Layer& operator=(Layer&&) = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}

        virtual void OnFixedUpdate() {}
        virtual void OnUpdate() {}

        [[nodiscard]] const std::string& GetName() const { return m_Name; }

        virtual bool MeetsRequirements() { return true; }

    protected:
        Layer(std::string name) : m_Name(std::move(name)) {}

    private:
        std::string m_Name;
    };
} // namespace Velvet
