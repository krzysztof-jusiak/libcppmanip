#include "CppManip.hpp"
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include "TextFileOps.hpp"
#include "ClangToolArgsBuilder.hpp"
#include "MethodExtractorFrontendActionFactory.hpp"
#include "TextOperationApplier.hpp"
#include "TextReplacer.hpp"

void performFrontendActionForFile(clang::tooling::FrontendActionFactory& actionFactory, std::string sourceFilename)
{
    ClangToolArgsBuilder args;
    args.setSourceFilename(sourceFilename);
    auto argc = args.getArgc();
    auto argv = args.getArgv();
    clang::tooling::CommonOptionsParser parser(argc, argv);
    clang::tooling::ClangTool tool(parser.GetCompilations(), { sourceFilename }); // clang bug: parser.GetSourcePathList() uses statics and "adds up" source file names
    tool.run(&actionFactory);
}

void applySourceOperationsToFile(TextOperationApplier& sourceOperations, const std::string& filename)
{
    std::string source = loadTextFromFile(filename);
    TextReplacer replacer(source);
    sourceOperations.apply(replacer);
    std::string modifiedSource = replacer.getText();
    writeTextToFile(modifiedSource, filename); 
}

void extractMethodInFile(const std::string& methodName, SourceSelection selection, const std::string& filename)
{
    llvm::outs() << "extracting " << selection.from << " " << selection.to << "\n";
    TextOperationApplier sourceOperations;
    MethodExtractorFrontendActionFactory factory(methodName, selection, sourceOperations);
    performFrontendActionForFile(factory, filename);
    applySourceOperationsToFile(sourceOperations, filename);
}