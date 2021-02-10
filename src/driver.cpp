#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include "actions.hpp"
#include <config.hpp>
#include "clang/Tooling/CommonOptionsParser.h"

using namespace llvm;
using namespace clang;
using namespace clang::tooling;

class LambdaCaptureCheckerAction : public clang::ASTFrontendAction {
public:
  virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
    clang::CompilerInstance &Compiler, llvm::StringRef InFile) {
    return std::unique_ptr<clang::ASTConsumer>(
        new LambdaCaptureCheckerConsumer(&Compiler.getASTContext()));
  }
};

static cl::OptionCategory LambdaCaptureCheckerCategory(
    PROJECT_NAME " options");

int main(int argc, const char **argv) {
  CommonOptionsParser Op(argc, argv, LambdaCaptureCheckerCategory);

  // create a new Clang Tool instance (a LibTooling environment)
  ClangTool Tool(Op.getCompilations(), Op.getSourcePathList());

  return Tool.run(newFrontendActionFactory<LambdaCaptureCheckerAction>().get());
}
