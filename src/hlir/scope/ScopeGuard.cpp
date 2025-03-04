#include "../../headers/Hlir.h"

namespace hlir {

    /**
     * @brief RAII class for managing scope entry and exit
     * 
     * ScopeGuard automatically manages scope lifetime by calling enterLocalScope
     * on construction and exitLocalScope on destruction, ensuring proper cleanup
     * even in the presence of exceptions.
     */
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