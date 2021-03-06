#ifndef CPPMANIP_8928F17D8AA84417B27EA483D089DFED_HPP
#define CPPMANIP_8928F17D8AA84417B27EA483D089DFED_HPP
#include <string>
#include <vector>

namespace clang
{
class VarDecl;
}

namespace cppmanip
{
namespace legacy
{

class FunctionPrinter
{
public:
    typedef std::vector<clang::VarDecl *> Variables;
    typedef std::vector<std::string> Strings;
    virtual ~FunctionPrinter() { }
    virtual std::string printFunction(const std::string& name, const Variables& args, const std::string& body) = 0;
    virtual std::string printFunctionCall(const std::string& name, const Variables& args) = 0;
};

}
}
#endif // CPPMANIP_8928F17D8AA84417B27EA483D089DFED_HPP
