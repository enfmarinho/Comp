#ifndef NON_TERMINALS_H
#define NON_TERMINALS_H

// This values have meaning and are used to index and to perform some
// arithmetic, bad practice i know, but apparently this is the way to go
#define PROGRAM 1
#define T_PROGRAM 2
#define U_PROGRAM 3
#define DECL 4
#define VAR_DECL 5
#define T_VAR_DECL 6
#define U_VAR_DECL 7
#define PROC_DECL 8
#define T_PROC_DECL 9
#define X_PROC_DECL 10
#define U_PROC_DECL 11
#define V_PROC_DECL 12
#define Y_PROC_DECL 13
#define Z_PROC_DECL 14
#define REC_DECL 15
#define T_REC_DECL 16
#define U_REC_DECL 17
#define PARAMFIELD_DECL 18
#define STMT_LIST 19
#define T_STMT_LIST 20
#define OPT_EXP 21
#define EXP 22
#define PREC_EXP 23
#define L_EXP 24
#define L2_EXP 25
#define LU_EXP 26
#define LU2_EXP 27
#define R_EXP 28
#define R2_EXP 29
#define A_EXP 30
#define A2_EXP 31
#define AU_EXP 32
#define AU2_EXP 33
#define POW_EXP 34
#define POW_EXP2 35
#define FIM_EXP 36
#define REF_VAR 37
#define DEREF_VAR 38
#define VAR 39
#define REC_VAR 40
#define NAME_VAR 41
#define NAMELESS_VAR 42
#define NAMELESS_DEREF_VAR_VAR 43
#define NO_PAREN_VAR 44
#define LITERAL 45
#define BOOL_LITERAL 46
#define STMT 47
#define NAME_STMT 48
#define OPT_DOT_NAME_ASSIGN_EXP 49
#define ASSIGN_STMT 50
#define NAME_ASSIGN_STMT 51
#define NAMELESS_ASSIGN_STMT 52
#define OPT_DOT_NAME 53
#define IF_STMT 54
#define T_IF_STMT 55
#define WHILE_STMT 56
#define RETURN_STMT 57
#define CALL_STMT 58
#define NAME_CALL_STMT 59
#define T_CALL_STMT 60
#define U_CALL_STMT 61
#define DO_STMT 62
#define DO_STMT_LIST 63
#define TYPE 64
#define NUMBER_OF_NON_TERMINALS                                                \
  65 // Its actually 64, but for coding purposes lets leave it like that
#define END 66
#define EMPTY 257

#endif // !NON_TERMINALS_H
