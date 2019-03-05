
// Generated from /Users/pgr09/Documents/Onderwijs/2.3/Compilers-OperatingSystems/git/Practical/Shell/Base/ShellGrammar.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "ShellGrammarVisitor.h"


/**
 * This class provides an empty implementation of ShellGrammarVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  ShellGrammarBaseVisitor : public ShellGrammarVisitor {
public:

  virtual antlrcpp::Any visitSequence(ShellGrammarParser::SequenceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSeqDelim(ShellGrammarParser::SeqDelimContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPipeline(ShellGrammarParser::PipelineContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSimpleCommand(ShellGrammarParser::SimpleCommandContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIoRedirect(ShellGrammarParser::IoRedirectContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitString(ShellGrammarParser::StringContext *ctx) override {
    return visitChildren(ctx);
  }


};

