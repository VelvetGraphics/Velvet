#pragma once

namespace Velvet {
    namespace ApplicationState {
        enum State
        {
            // TODO: Bit macro
            None = 0,
            Init = 1 << 0,
            Destroy = 1 << 1,
            Running = 1 << 2,
            Last = 3,
        };
    }

    using AppState = U64;
} // namespace Velvet
