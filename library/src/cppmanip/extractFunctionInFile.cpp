#include "CppManip.hpp"
#include "ClangFunctionExtractorFactory.hpp"

namespace cppmanip
{

SourceReplacements extractFunctionInFile(const std::string& functionName, SourceSelection selection, const std::string& filename)
{
    auto extractor = ClangFunctionExtractorFactory().createFunctionExtractor(functionName, selection, filename);
    return extractor->extractFunctionInFile();
}

}
