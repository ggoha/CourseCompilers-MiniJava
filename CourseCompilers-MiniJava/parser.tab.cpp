/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 4 "parser.y"

#include <iostream>
#include "PrettyPrinter.h"
#include "CTypes.h"
extern "C" int yylex();
void yyerror( int*, const char* );

/* Line 371 of yacc.c  */
#line 76 "parser.tab.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.hpp".  */
#ifndef YY_YY_PARSER_TAB_HPP_INCLUDED
# define YY_YY_PARSER_TAB_HPP_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     UMINUS = 258,
     INTEGER_LITERAL = 259,
     CLASS = 260,
     BINARY_OPERATOR = 261,
     COMMENT = 262,
     ID = 263,
     PUBLIC = 264,
     STATIC = 265,
     VOID = 266,
     MAIN = 267,
     STRING = 268,
     EXTENDS = 269,
     BOOLEAN = 270,
     IF = 271,
     ELSE = 272,
     WHILE = 273,
     PRINTLN = 274,
     LENGTH = 275,
     TRUE = 276,
     FALSE = 277,
     THIS = 278,
     NEW = 279,
     RETURN = 280,
     INT = 281
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 18 "parser.y"

	int ival;
	char sval[255];
	CProgram* program;
	IStatement* statement;
	CClassDecls* classdecls; 
	CClassDecl* classdecl; 
	CMainClass* cmain;
	CMethodDecl* cmethoddecl;
	CMethodDecls* cmethoddecls;
	CVarDecl* cvardecl;
	CVarDecls* cvardecls;
	CStatements* cstatements;
	CFormalList* cformallist;
	CFormalRests* cformalrests;
	CFormalRest* cformalrest;
	CType* ctype;
	CExp* cexp;
	CExpList* cexplist;
	CExpRests* cexprests;
	CexpRest* cexprest;


/* Line 387 of yacc.c  */
#line 169 "parser.tab.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (int* hasError);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_PARSER_TAB_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 197 "parser.tab.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   329

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  63
/* YYNRULES -- Number of states.  */
#define YYNSTATES  169

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   281

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    12,     2,     2,     2,     2,    13,     2,
       9,    10,     5,     3,    41,     4,    11,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    40,
      14,    42,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     7,     2,     8,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,    39,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     6,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    13,    31,    38,    44,
      50,    55,    64,    72,    80,    87,    89,    92,    94,    97,
     101,   115,   128,   141,   153,   155,   158,   162,   165,   167,
     170,   174,   178,   180,   182,   184,   188,   196,   202,   208,
     213,   221,   225,   229,   233,   236,   241,   245,   250,   254,
     261,   263,   265,   267,   269,   271,   277,   282,   285,   289,
     292,   294,   296,   299
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      44,     0,    -1,    46,    -1,    46,    45,    -1,    47,    -1,
      45,    47,    -1,    16,    19,    38,    20,    21,    22,    23,
       9,    24,     7,     8,    19,    10,    38,    57,    39,    39,
      -1,    16,    19,    38,    48,    49,    39,    -1,    16,    19,
      38,    48,    39,    -1,    16,    19,    38,    49,    39,    -1,
      16,    19,    38,    39,    -1,    16,    19,    25,    19,    38,
      48,    49,    39,    -1,    16,    19,    25,    19,    38,    48,
      39,    -1,    16,    19,    25,    19,    38,    49,    39,    -1,
      16,    19,    25,    19,    38,    39,    -1,    50,    -1,    48,
      50,    -1,    51,    -1,    49,    51,    -1,    56,    19,    40,
      -1,    20,    56,    19,     9,    53,    10,    38,    48,    52,
      36,    58,    40,    39,    -1,    20,    56,    19,     9,    53,
      10,    38,    48,    36,    58,    40,    39,    -1,    20,    56,
      19,     9,    53,    10,    38,    52,    36,    58,    40,    39,
      -1,    20,    56,    19,     9,    53,    10,    38,    36,    58,
      40,    39,    -1,    57,    -1,    52,    57,    -1,    56,    19,
      54,    -1,    56,    19,    -1,    55,    -1,    54,    55,    -1,
      41,    56,    19,    -1,    37,     7,     8,    -1,    26,    -1,
      37,    -1,    19,    -1,    38,    57,    39,    -1,    27,     9,
      58,    10,    57,    28,    57,    -1,    29,     9,    58,    10,
      57,    -1,    30,     9,    58,    10,    40,    -1,    19,    42,
      58,    40,    -1,    19,     7,    58,     8,    42,    58,    40,
      -1,    58,     3,    58,    -1,    58,     4,    58,    -1,    58,
       5,    58,    -1,     4,    58,    -1,    58,    13,    13,    58,
      -1,    58,    14,    58,    -1,    58,     7,    58,     8,    -1,
      58,    11,    31,    -1,    58,    11,    19,     9,    59,    10,
      -1,    15,    -1,    32,    -1,    33,    -1,    19,    -1,    34,
      -1,    35,    37,     7,    58,     8,    -1,    35,    19,     9,
      10,    -1,    12,    58,    -1,     9,    58,    10,    -1,    58,
      60,    -1,    58,    -1,    61,    -1,    60,    61,    -1,    41,
      58,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   103,   103,   104,   107,   108,   111,   114,   115,   116,
     117,   118,   119,   120,   121,   124,   125,   128,   129,   132,
     135,   136,   137,   138,   141,   142,   145,   146,   149,   150,
     153,   156,   157,   158,   159,   163,   164,   165,   166,   167,
     168,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   191,
     192,   195,   196,   199
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "'+'", "'-'", "'*'", "UMINUS", "'['",
  "']'", "'('", "')'", "'.'", "'!'", "'&'", "'<'", "INTEGER_LITERAL",
  "CLASS", "BINARY_OPERATOR", "COMMENT", "ID", "PUBLIC", "STATIC", "VOID",
  "MAIN", "STRING", "EXTENDS", "BOOLEAN", "IF", "ELSE", "WHILE", "PRINTLN",
  "LENGTH", "TRUE", "FALSE", "THIS", "NEW", "RETURN", "INT", "'{'", "'}'",
  "';'", "','", "'='", "$accept", "Program", "ClassDecls", "MainClass",
  "ClassDecl", "VarDecls", "MethodDecls", "VarDecl", "MethodDecl",
  "Statements", "FormalList", "FormalRests", "FormalRest", "Type",
  "Statement", "Exp", "ExpList", "ExpRests", "ExpRest", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,    43,    45,    42,   258,    91,    93,    40,
      41,    46,    33,    38,    60,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   123,   125,
      59,    44,    61
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    43,    44,    44,    45,    45,    46,    47,    47,    47,
      47,    47,    47,    47,    47,    48,    48,    49,    49,    50,
      51,    51,    51,    51,    52,    52,    53,    53,    54,    54,
      55,    56,    56,    56,    56,    57,    57,    57,    57,    57,
      57,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    59,
      59,    60,    60,    61
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,    17,     6,     5,     5,
       4,     8,     7,     7,     6,     1,     2,     1,     2,     3,
      13,    12,    12,    11,     1,     2,     3,     2,     1,     2,
       3,     3,     1,     1,     1,     3,     7,     5,     5,     4,
       7,     3,     3,     3,     2,     4,     3,     4,     3,     6,
       1,     1,     1,     1,     1,     5,     4,     2,     3,     2,
       1,     1,     2,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     0,     1,     0,     3,     4,     0,
       0,     5,     0,     0,     0,     0,     0,    34,     0,    32,
      33,    10,     0,     0,    15,    17,     0,     0,     0,     0,
       0,     8,     0,    16,     9,    18,     0,     0,    14,     0,
       0,     0,    31,     7,    19,     0,    12,     0,    13,     0,
       0,    11,     0,     0,     0,     0,    27,     0,     0,     0,
      26,    28,     0,    34,     0,     0,     0,     0,     0,     0,
       0,    24,     0,    29,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    50,    53,    51,    52,    54,     0,     0,
       0,     0,     0,     0,     0,    25,    30,     0,     0,     0,
       0,     0,     0,    44,     0,    57,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    35,     0,     0,     0,
       0,     0,    39,     0,     0,     0,    58,     0,     0,    41,
      42,    43,     0,     0,    48,     0,    46,    23,     0,     0,
       0,     0,     0,     0,    37,    38,    56,     0,    47,     0,
      45,    21,     0,    22,     6,     0,     0,    55,    60,     0,
      20,    40,    36,     0,    59,    61,    49,    63,    62
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     7,     3,     8,    22,    23,    24,    25,    70,
      52,    60,    61,    26,    71,    89,   159,   164,   165
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -76
static const yytype_int16 yypact[] =
{
      11,     5,    29,    15,    18,   -76,    13,    15,   -76,    38,
      19,   -76,    60,    65,    71,    67,    57,   -76,    61,   -76,
      97,   -76,   118,     6,   -76,   -76,    92,    91,   132,   101,
     123,   -76,     8,   -76,   -76,   -76,    94,   130,   -76,   141,
      10,   136,   -76,   -76,   -76,   125,   -76,    39,   -76,    61,
     134,   -76,   137,   143,   145,   135,   115,   149,   155,    61,
     115,   -76,   162,     9,   161,   166,   167,   131,   193,   160,
     175,   -76,   158,   -76,   150,   131,   131,   131,   131,   131,
     131,   131,   131,   -76,   -76,   -76,   -76,   -76,     4,    59,
       9,   144,   131,   180,   131,   -76,   -76,   193,   221,    72,
     233,   245,   257,   315,   269,   -76,   186,   194,   131,   131,
     131,   131,   117,   187,   131,   164,   -76,    89,   131,   102,
     169,   172,   -76,   193,   193,   177,   -76,   196,   131,   310,
     310,   315,   281,   206,   -76,   131,   -76,   -76,   182,   114,
     188,   191,   131,   205,   -76,   -76,   -76,   293,   -76,   131,
     -76,   -76,   200,   -76,   -76,   119,   193,   -76,     7,   209,
     -76,   -76,   -76,   131,   201,   -76,   -76,   305,   -76
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -76,   -76,   -76,   -76,   234,    -6,    43,   -14,    14,   176,
     -76,   -76,   197,    -9,   -55,   -75,   -76,   -76,    87
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      98,    99,   100,   101,   102,   103,   104,   105,    33,    29,
     108,   109,   110,    91,   111,    95,    75,   117,   112,   119,
     113,   114,    39,   106,     4,    33,    18,     1,    18,     5,
      18,     6,    10,   129,   130,   131,   132,    35,    95,   136,
      53,   107,   120,   139,    13,    34,    35,    43,   163,    48,
      72,    76,    69,   147,    35,    33,     9,    14,    12,    18,
     150,    35,   108,   109,   110,    32,   111,   155,   143,   144,
     112,    40,   113,   114,   158,   108,   109,   110,    51,   111,
      17,    15,    47,   112,    16,   113,   114,    19,   167,    27,
      17,    18,   108,   109,   110,    28,   111,    19,    20,   115,
     112,   162,   113,   114,    30,   108,   109,   110,    20,   111,
      21,    36,   122,   112,    37,   113,   114,   108,   109,   110,
      41,   111,   108,   109,   110,   112,   111,   113,   114,   138,
     112,    42,   113,   114,    44,    80,   133,    17,    18,    45,
      81,    54,   140,    82,    19,    49,    83,    55,   134,    50,
      84,    17,    18,    57,   152,    20,    59,    31,    19,   161,
      17,    18,    56,    85,    86,    87,    88,    19,    62,    20,
      77,    38,    74,    58,    63,    78,    79,    96,    20,    63,
      46,    19,    64,   116,    65,    66,    19,    64,    97,    65,
      66,    67,    20,    68,    90,   127,    92,    20,    68,    90,
     135,   128,    64,   137,    65,    66,   146,    64,   141,    65,
      66,    94,    90,    68,   142,   149,   118,   145,    68,   166,
      64,   151,    65,    66,   108,   109,   110,   153,   111,   121,
     154,    68,   112,   156,   113,   114,   108,   109,   110,   160,
     111,    11,   163,   123,   112,    93,   113,   114,   108,   109,
     110,   168,   111,     0,     0,   124,   112,    73,   113,   114,
     108,   109,   110,     0,   111,     0,     0,   125,   112,     0,
     113,   114,   108,   109,   110,     0,   111,     0,     0,   126,
     112,     0,   113,   114,   108,   109,   110,     0,   111,   148,
       0,     0,   112,     0,   113,   114,   108,   109,   110,     0,
     111,   157,     0,     0,   112,     0,   113,   114,   108,   109,
     110,     0,   111,     0,     0,   110,   112,   111,   113,   114,
       0,   112,   111,   113,   114,     0,   112,     0,   113,   114
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-76)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      75,    76,    77,    78,    79,    80,    81,    82,    22,    18,
       3,     4,     5,    68,     7,    70,     7,    92,    11,    94,
      13,    14,    28,    19,    19,    39,    20,    16,    20,     0,
      20,    16,    19,   108,   109,   110,   111,    23,    93,   114,
      49,    37,    97,   118,    25,    39,    32,    39,    41,    39,
      59,    42,    58,   128,    40,    69,    38,    38,    20,    20,
     135,    47,     3,     4,     5,    22,     7,   142,   123,   124,
      11,    28,    13,    14,   149,     3,     4,     5,    39,     7,
      19,    21,    39,    11,    19,    13,    14,    26,   163,    22,
      19,    20,     3,     4,     5,    38,     7,    26,    37,    40,
      11,   156,    13,    14,     7,     3,     4,     5,    37,     7,
      39,    19,    40,    11,    23,    13,    14,     3,     4,     5,
      19,     7,     3,     4,     5,    11,     7,    13,    14,    40,
      11,     8,    13,    14,    40,     4,    19,    19,    20,     9,
       9,     7,    40,    12,    26,     9,    15,    10,    31,    24,
      19,    19,    20,     8,    40,    37,    41,    39,    26,    40,
      19,    20,    19,    32,    33,    34,    35,    26,    19,    37,
       9,    39,    10,    38,    19,     9,     9,    19,    37,    19,
      39,    26,    27,    39,    29,    30,    26,    27,    38,    29,
      30,    36,    37,    38,    19,     9,    36,    37,    38,    19,
      13,     7,    27,    39,    29,    30,    10,    27,    39,    29,
      30,    36,    19,    38,    42,     9,    36,    40,    38,    10,
      27,    39,    29,    30,     3,     4,     5,    39,     7,     8,
      39,    38,    11,    28,    13,    14,     3,     4,     5,    39,
       7,     7,    41,    10,    11,    69,    13,    14,     3,     4,
       5,   164,     7,    -1,    -1,    10,    11,    60,    13,    14,
       3,     4,     5,    -1,     7,    -1,    -1,    10,    11,    -1,
      13,    14,     3,     4,     5,    -1,     7,    -1,    -1,    10,
      11,    -1,    13,    14,     3,     4,     5,    -1,     7,     8,
      -1,    -1,    11,    -1,    13,    14,     3,     4,     5,    -1,
       7,     8,    -1,    -1,    11,    -1,    13,    14,     3,     4,
       5,    -1,     7,    -1,    -1,     5,    11,     7,    13,    14,
      -1,    11,     7,    13,    14,    -1,    11,    -1,    13,    14
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    16,    44,    46,    19,     0,    16,    45,    47,    38,
      19,    47,    20,    25,    38,    21,    19,    19,    20,    26,
      37,    39,    48,    49,    50,    51,    56,    22,    38,    56,
       7,    39,    49,    50,    39,    51,    19,    23,    39,    48,
      49,    19,     8,    39,    40,     9,    39,    49,    39,     9,
      24,    39,    53,    56,     7,    10,    19,     8,    38,    41,
      54,    55,    19,    19,    27,    29,    30,    36,    38,    48,
      52,    57,    56,    55,    10,     7,    42,     9,     9,     9,
       4,     9,    12,    15,    19,    32,    33,    34,    35,    58,
      19,    57,    36,    52,    36,    57,    19,    38,    58,    58,
      58,    58,    58,    58,    58,    58,    19,    37,     3,     4,
       5,     7,    11,    13,    14,    40,    39,    58,    36,    58,
      57,     8,    40,    10,    10,    10,    10,     9,     7,    58,
      58,    58,    58,    19,    31,    13,    58,    39,    40,    58,
      40,    39,    42,    57,    57,    40,    10,    58,     8,     9,
      58,    39,    40,    39,    39,    58,    28,     8,    58,    59,
      39,    40,    57,    41,    60,    61,    10,    58,    61
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (hasError, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, hasError); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, int* hasError)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, hasError)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    int* hasError;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (hasError);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, int* hasError)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, hasError)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    int* hasError;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, hasError);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, int* hasError)
#else
static void
yy_reduce_print (yyvsp, yyrule, hasError)
    YYSTYPE *yyvsp;
    int yyrule;
    int* hasError;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , hasError);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, hasError); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, int* hasError)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, hasError)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    int* hasError;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (hasError);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (int* hasError)
#else
int
yyparse (hasError)
    int* hasError;
#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1792 of yacc.c  */
#line 103 "parser.y"
    { (yyval.program) = new CProgram( (yyvsp[(1) - (1)].cmain) ); }
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 104 "parser.y"
    {(yyval.program) = new CProgram( (yyvsp[(1) - (2)].cmain), (yyvsp[(2) - (2)].classdecls) ); }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 107 "parser.y"
    { (yyval.classdecls) = new CClassDecls((yyvsp[(1) - (1)].classdecl)); }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 108 "parser.y"
    { (yyval.classdecls) = (yyvsp[(1) - (2)].classdecls)->addNext((yyvsp[(2) - (2)].classdecl)); }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 111 "parser.y"
    { (yyval.cmain) = new CMainClass( (yyvsp[(2) - (17)].sval), (yyvsp[(12) - (17)].sval), (yyvsp[(15) - (17)].statement) );}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 114 "parser.y"
    { (yyval.classdecl) = new CClassDecl((yyvsp[(2) - (6)].sval), (yyvsp[(4) - (6)].cvardecls), (yyvsp[(5) - (6)].cmethoddecls)); }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 115 "parser.y"
    { (yyval.classdecl) = new CClassDecl( (yyvsp[(2) - (5)].sval), (yyvsp[(4) - (5)].cvardecls),0 ); }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 116 "parser.y"
    { (yyval.classdecl) = new CClassDecl( (yyvsp[(2) - (5)].sval), 0,(yyvsp[(4) - (5)].cmethoddecls) );  }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 117 "parser.y"
    { (yyval.classdecl) = new CClassDecl((yyvsp[(2) - (4)].sval),0,0); }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 118 "parser.y"
    { (yyval.classdecl) = new CClassDeclsInheritance((yyvsp[(2) - (8)].sval), (yyvsp[(4) - (8)].sval), (yyvsp[(6) - (8)].cvardecls), (yyvsp[(7) - (8)].cmethoddecls)); }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 119 "parser.y"
    { (yyval.classdecl) = new CClassDeclsInheritance((yyvsp[(2) - (7)].sval), (yyvsp[(4) - (7)].sval), (yyvsp[(6) - (7)].cvardecls),0); }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 120 "parser.y"
    { (yyval.classdecl) = new CClassDeclsInheritance((yyvsp[(2) - (7)].sval), (yyvsp[(4) - (7)].sval), 0,(yyvsp[(6) - (7)].cmethoddecls)); }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 121 "parser.y"
    { (yyval.classdecl) = new CClassDeclsInheritance((yyvsp[(2) - (6)].sval), (yyvsp[(4) - (6)].sval),0,0); }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 124 "parser.y"
    { (yyval.cvardecls) = new CVardecls((yyvsp[(1) - (1)].cvardecl)); }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 125 "parser.y"
    {(yyval.cvardecls) = (yyvsp[(1) - (2)].cvardecls)->addNext((yyvsp[(2) - (2)].cvardecl)); }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 128 "parser.y"
    { (yyval.cmethoddecls) = new CMethodDecls((yyvsp[(1) - (1)].cmethoddecl)); }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 129 "parser.y"
    {(yyval.cmethoddecls) = (yyvsp[(1) - (2)].cmethoddecls)->addNext((yyvsp[(2) - (2)].cmethoddecl)); }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 132 "parser.y"
    { (yyval.cvardecl) = new CVarDecl((yyvsp[(1) - (3)].ctype), (yyvsp[(2) - (3)].sval)); }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 135 "parser.y"
    { (yyval.cmethoddecl) = new CMethodDecls( (yyvsp[(2) - (13)].ctype), (yyvsp[(3) - (13)].sval), (yyvsp[(5) - (13)].cformallist), (yyvsp[(8) - (13)].cvardecls), (yyvsp[(9) - (13)].cstatements), (yyvsp[(11) - (13)].cexp) ); }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 136 "parser.y"
    { (yyval.cmethoddecl) = new CMethodDecls( (yyvsp[(2) - (12)].ctype), (yyvsp[(3) - (12)].sval), (yyvsp[(5) - (12)].cformallist), (yyvsp[(8) - (12)].cvardecls),0, (yyvsp[(10) - (12)].cexp)); }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 137 "parser.y"
    { (yyval.cmethoddecl) = new CMethodDecls( (yyvsp[(2) - (12)].ctype), (yyvsp[(3) - (12)].sval), (yyvsp[(5) - (12)].cformallist), 0,(yyvsp[(8) - (12)].cstatements), (yyvsp[(10) - (12)].cexp)); }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 138 "parser.y"
    { (yyval.cmethoddecl) = new CMethodDecls( (yyvsp[(2) - (11)].ctype), (yyvsp[(3) - (11)].sval), (yyvsp[(5) - (11)].cformallist), 0,0,(yyvsp[(9) - (11)].cexp)); }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 141 "parser.y"
    { (yyval.cstatements) = new CStatements((yyvsp[(1) - (1)].statement)); }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 142 "parser.y"
    { (yyval.cstatements) = (yyvsp[(1) - (2)].cstatements)->addNext((yyvsp[(2) - (2)].statement)) ; }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 145 "parser.y"
    { (yyval.cformallist) = new CFormalList((yyvsp[(1) - (3)].ctype), (yyvsp[(2) - (3)].sval), (yyvsp[(3) - (3)].cformalrests)) ; }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 146 "parser.y"
    { (yyval.cformallist) = new CFormalList( (yyvsp[(1) - (2)].ctype), (yyvsp[(2) - (2)].sval) ); }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 149 "parser.y"
    { (yyval.cformalrests) = new CFormalRests((yyvsp[(1) - (1)].cformalrest)); }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 150 "parser.y"
    {(yyval.cformalrests) = (yyvsp[(1) - (2)].cformalrests); (yyvsp[(1) - (2)].cformalrests)->addNext((yyvsp[(2) - (2)].cformalrest)); }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 153 "parser.y"
    { (yyval.cformalrest) = new CFormalRest((yyvsp[(2) - (3)].ctype),(yyvsp[(3) - (3)].sval)); }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 156 "parser.y"
    {(yyval.ctype) = new CType( CType::_mas ); }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 157 "parser.y"
    { (yyval.ctype) = new CType( CType::_bool ); }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 158 "parser.y"
    { (yyval.ctype) = new CType( CType::_int ); }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 159 "parser.y"
    { (yyval.ctype) = new CType( CType::_id, (yyvsp[(1) - (1)].sval) );}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 163 "parser.y"
    {(yyval.statement) = new CStatementBRACKETS((yyvsp[(2) - (3)].statement)); }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 164 "parser.y"
    { (yyval.statement) = new CStatementIF((yyvsp[(3) - (7)].cexp),(yyvsp[(5) - (7)].statement),(yyvsp[(7) - (7)].statement)); }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 165 "parser.y"
    { (yyval.statement) = new CStatementWHILE((yyvsp[(3) - (5)].cexp),(yyvsp[(5) - (5)].statement)); }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 166 "parser.y"
    {(yyval.statement) = new CStatementPRINTLN((yyvsp[(3) - (5)].cexp)); }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 167 "parser.y"
    { (yyval.statement) = new CStatementASIGNMENT((yyvsp[(1) - (4)].sval),(yyvsp[(3) - (4)].cexp)); }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 168 "parser.y"
    { (yyval.statement) = new CStatementSQUEREASIGNMENT((yyvsp[(1) - (7)].sval),(yyvsp[(3) - (7)].cexp),(yyvsp[(6) - (7)].cexp)); }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 171 "parser.y"
    { (yyval.cexp) = new CExpBinary((yyvsp[(1) - (3)].cexp),'+', (yyvsp[(3) - (3)].cexp)); }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 172 "parser.y"
    { (yyval.cexp) = new CExpBinary((yyvsp[(1) - (3)].cexp),'-', (yyvsp[(3) - (3)].cexp)); }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 173 "parser.y"
    { (yyval.cexp) = new CExpBinary((yyvsp[(1) - (3)].cexp),'*', (yyvsp[(3) - (3)].cexp)); }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 174 "parser.y"
    { (yyval.cexp) = new CExpUnaryMinus((yyvsp[(2) - (2)].cexp)); }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 175 "parser.y"
    { (yyval.cexp) = new CExpBinary((yyvsp[(1) - (4)].cexp),'&', (yyvsp[(4) - (4)].cexp)); }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 176 "parser.y"
    { (yyval.cexp) = new CExpBinary((yyvsp[(1) - (3)].cexp),'<', (yyvsp[(3) - (3)].cexp)); }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 177 "parser.y"
    { (yyval.cexp) = new CExpInSquareBrackets((yyvsp[(1) - (4)].cexp), (yyvsp[(3) - (4)].cexp)); }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 178 "parser.y"
    { (yyval.cexp) = new CExpPointLENGTH((yyvsp[(1) - (3)].cexp)); }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 179 "parser.y"
    {(yyval.cexp) = new CExpPointID((yyvsp[(1) - (6)].cexp), (yyvsp[(3) - (6)].sval), (yyvsp[(5) - (6)].cexplist)); }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 180 "parser.y"
    { (yyval.cexp) = new CExpINTEGER_LITERAL( (yyvsp[(1) - (1)].ival) ); }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 181 "parser.y"
    { (yyval.cexp) = new CExpSingleOp(true); }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 182 "parser.y"
    { (yyval.cexp) = new CExpSingleOp(false); }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 183 "parser.y"
    { (yyval.cexp) = new CExpID((yyvsp[(1) - (1)].sval)); }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 184 "parser.y"
    { (yyval.cexp) = new CExpTHIS(); }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 185 "parser.y"
    { (yyval.cexp) = new CExpNEWINT((yyvsp[(4) - (5)].cexp)); }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 186 "parser.y"
    { (yyval.cexp) = new CExpNEWID((yyvsp[(2) - (4)].sval)); }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 187 "parser.y"
    { (yyval.cexp) = new CExpExclamationMark((yyvsp[(2) - (2)].cexp)); }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 188 "parser.y"
    { (yyval.cexp) = new CExpCircleBrackets((yyvsp[(2) - (3)].cexp)); }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 191 "parser.y"
    { (yyval.cexplist) = new CExpList((yyvsp[(1) - (2)].cexp), (yyvsp[(2) - (2)].cexprests)); }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 192 "parser.y"
    {(yyval.cexplist) = new CExpList((yyvsp[(1) - (1)].cexp)); }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 195 "parser.y"
    { (yyval.cexprests) = new CExpRest((yyvsp[(1) - (1)].cexprest)); }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 196 "parser.y"
    {(yyval.cexprests) = (yyvsp[(1) - (2)].cexprests)->addNext((yyvsp[(2) - (2)].cexprest)); }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 199 "parser.y"
    { (yyval.cexprest) = new CExpRest((yyvsp[(2) - (2)].cexp)); }
    break;


/* Line 1792 of yacc.c  */
#line 1932 "parser.tab.cpp"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (hasError, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (hasError, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, hasError);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, hasError);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (hasError, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, hasError);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, hasError);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 201 "parser.y"

/* Функция обработки ошибки. */
void yyerror( int*, const char* str )
{
	std::cout << str << std::endl;
}