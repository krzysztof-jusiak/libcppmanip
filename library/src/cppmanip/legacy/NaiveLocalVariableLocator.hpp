#ifndef CPPMANIP_050F6B6B2ADD47528D05772006AEF4C7_HPP
#define CPPMANIP_050F6B6B2ADD47528D05772006AEF4C7_HPP
#include <cppmanip/LocalVariableUsageDetector.hpp>

namespace cppmanip
{
namespace legacy
{

class NaiveLocalVariableLocator : public LocalVariableUsageDetector
{
public:
    virtual Variables findLocalVariablesRequiredForStmts(clang::StmtRange stmts);
    virtual Variables findVariablesDeclaredByAndUsedAfterStmts(clang::StmtRange stmts, clang::Stmt& parent);
};

}
}
#endif // CPPMANIP_050F6B6B2ADD47528D05772006AEF4C7_HPP
