#include "ClangFunctionExtractor.hpp"
#include "text/OffsetConverter.hpp"
#include "io/TextFileOps.hpp"
#include "TranslationUnitFunctionExtractorFactory.hpp"
#include "clangutil/runTranslationUnitHandlerOnFile.hpp"
#include "text/TextReplacementRecorder.hpp"

namespace cppmanip
{
namespace
{
SourceReplacements recordReplacements(const text::OffsetBasedTextModifier& sourceOperations, const std::string& filename)
{
    text::OffsetConverter offsetCoverter(io::loadTextFromFile(filename));
    text::TextReplacementRecorder recorder(std::bind(&text::OffsetConverter::getLocationFromOffset, &offsetCoverter, std::placeholders::_1));
    sourceOperations.apply(recorder);
    return recorder.getReplacements();
}
}

SourceReplacements ClangFunctionExtractor::extractFunctionInFile()
{
    clangutil::runTranslationUnitHandlerOnFile(translationUnitHandler, filename);
    return recordReplacements(textModifier, filename);
}

}

