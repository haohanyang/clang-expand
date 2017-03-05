#ifndef CLANG_EXPAND_SYMBOL_SEARCH_ACTION_HPP
#define CLANG_EXPAND_SYMBOL_SEARCH_ACTION_HPP

// Project includes
#include "clang-expand/common/state.hpp"
#include "clang-expand/common/structures.hpp"

// Clang includes
#include <clang/Basic/SourceLocation.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Lex/Token.h>

// Standard includes
#include <functional>
#include <memory>
#include <string>

namespace clang {
class CompilerInstance;
class FileID;
class SourceManager;
}

namespace llvm {
class StringRef;
}

namespace ClangExpand::SymbolSearch {

class State;

class Action : public clang::ASTFrontendAction {
 public:
  using super = clang::ASTFrontendAction;
  using ASTConsumerPointer = std::unique_ptr<clang::ASTConsumer>;

  Action(const Structures::EasyLocation& targetLocation,
         const StateCallback& stateCallback);

  bool BeginInvocation(clang::CompilerInstance& compiler) override;

  bool BeginSourceFileAction(clang::CompilerInstance& compiler,
                             llvm::StringRef filename) override;

  /// Creates the Consumer instance, forwarding the command line options.
  ASTConsumerPointer CreateASTConsumer(clang::CompilerInstance& compiler,
                                       llvm::StringRef filename) override;

 private:
  clang::FileID _getFileID(clang::SourceManager& sourceManager) const;

  std::string _spelling;
  StateCallback _stateCallback;
  clang::SourceLocation _callLocation;
  bool _alreadyFoundMacro;
  Structures::EasyLocation _targetLocation;
};

}  // namespace ClangExpand::SymbolSearch

#endif  // CLANG_EXPAND_SYMBOL_SEARCH_ACTION_HPP