#include "ClangFunctionExtractorFactory.hpp"
#include "ClangFunctionExtractor.hpp"
#include "text/TextOperationApplier.hpp"
#include "text/OffsetConverter.hpp"
#include "text/TextReplacementRecorder.hpp"
#include "makeWithDependencies.hpp"
#include "LocationRange.hpp"
#include "TranslationUnitFunctionExtractorFactory.hpp"
#include "io/TextFileOps.hpp"
#include "clangutil/runTranslationUnitHandlerOnFile.hpp"

namespace cppmanip
{

namespace
{
SourceReplacements recordReplacements(const text::OffsetBasedTextModifier& sourceOperations, const std::string& filename)
{
    text::OffsetConverter offsetCoverter(io::loadTextFromFile(filename));
    text::TextReplacementRecorder recorder([&](unsigned offset) { return offsetCoverter.getLocationFromOffset(offset); });
    sourceOperations.apply(recorder);
    return recorder.getReplacements();
}
}

FunctionExtractorPtr ClangFunctionExtractorFactory::createFunctionExtractor(
    const std::string& functionName, SourceSelection selection, const std::string& filename)
{
    struct WithDeps
    {
        text::OffsetBasedTextOperationApplier textModifier;
        ClangFunctionExtractor extractor;
        WithDeps(const std::string& functionName, SourceSelection selection, const std::string& filename)
            : extractor(
                std::bind(
                    clangutil::runTranslationUnitHandlerOnFile,
                    TranslationUnitFunctionExtractorFactory().createFunctionExtractor(
                        functionName, LocationRange(selection.from, selection.to), textModifier), filename),
                std::bind(recordReplacements, std::ref(textModifier), filename)) { }
    };
    auto withDeps = std::make_shared<WithDeps>(functionName, selection, filename);
    return std::shared_ptr<FunctionExtractor>(withDeps, &withDeps->extractor);
}

}

