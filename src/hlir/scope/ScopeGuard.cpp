#include "../../headers/Hlir.h"

namespace hlir {

    ScopeGuard::ScopeGuard(std::shared_ptr<Function> func, const std::shared_ptr<Statement> &statement)
        : function(std::move(func))
    {
        if (function) {
            function->enterLocalScope(statement);
        }
    }

    ScopeGuard::~ScopeGuard()
    {
        if (function) {
            function->exitLocalScope();
        }
    }

} // namespace hlir