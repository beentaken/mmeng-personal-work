//---------------------------------------------------------------------------
#ifndef COMMONH
#define COMMONH
//---------------------------------------------------------------------------

#ifdef _MSC_VER
#pragma warning(disable: 4290) // Suppress 'C++ Exception Specification ignored'
#endif

#include <string>

const char PLUS_OP   = '+';
const char MINUS_OP  = '-';
const char MULT_OP   = '*';
const char DIVIDE_OP = '/';

enum Kind {OPERATOR, LITERAL, IDENTIFIER};

struct ExprNode
{
  ExprNode *left;  // left sub-expression
  ExprNode *right; // right sub-expression
  Kind kind;       // kind of node this is
  union
  {
    char op;   // the operator
    int value; // the literal value
    char id;   // the identifier
  } data;
};

void FreeExprTree(ExprNode* tree);
void FreeChildren(ExprNode* tree);
bool IsAddOp(char token);
bool IsMulOp(char token);
bool IsIdentifier(char token);
bool IsLiteral(char token);
int GetNodeCount(void);
void FreeNode(ExprNode* node);
ExprNode *AllocateNode(void);

class ExprTreeException
{
  private:
    int error_code_;
    std::string message_;
  public:
    ExprTreeException(int ErrCode, const std::string& Message) :
        error_code_(ErrCode), message_(Message) {};
    virtual ~ExprTreeException() {
    }
    virtual int code(void) const {
      return error_code_;
    }
    virtual const char *what(void) const {
      return message_.c_str();
    }
    enum EXPRTREE_EXCEPTION {E_NO_MEMORY, E_BAD_TOKEN, E_DIVIDE_BY_ZERO};
};

#endif
