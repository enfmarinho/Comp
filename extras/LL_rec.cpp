// Declarações dos parsers para cada não-terminal

void f_S() {
    switch (token) {
        case kw_program:
            f_PROGRAM();
            // Aqui deveria vir a checagem do fim ($), mas normalmente isso é feito depois do parse principal
            break;
        default:
            error();
    }
}

void f_PROGRAM();
void f_T_PROGRAM();
void f_U_PROGRAM();
void f_DECL();
void f_VAR_DECL();
void f_T_VAR_DECL();
void f_U_VAR_DECL();
void f_PROC_DECL();
void f_T_PROC_DECL();
void f_X_PROC_DECL();
void f_U_PROC_DECL();
void f_V_PROC_DECL();

void f_Y_PROC_DECL();
void f_Z_PROC_DECL();
void f_REC_DECL();
void f_T_REC_DECL();
void f_U_REC_DECL();
void f_PARAMFIELD_DECL();
void f_STMT_LIST();
void f_T_STMT_LIST();

// NÂO SEI SE TA CERTO
void f_OPT_EXP() {
    switch (token) {
        case kw_new:
        case kw_ref:
        case op_not:
        case open_paren:
        case id:
            f_EXP();
            break;
        case float_literal:
        case int_literal:
        case string_literal:
        case bool_literal:
        case kw_null:
        case kw_deref:
            f_EXP();
            break;
        default:
            // epsilon production: faz nada, só sai da função
            break;
    }
}
void f_EXP() {
    switch (token) {
        case kw_new:
            eat(kw_new);
            eat(id);
            break;
        case kw_ref:
            f_REF_VAR();
            break;
        case op_not:
            f_L_EXP();
            f_OPT_EXP();
            break;
        case open_paren:
            f_L_EXP();
            f_OPT_EXP();
            break;
        case id:
            f_L_EXP();
            f_OPT_EXP();
            break;
        case float_literal:
            f_L_EXP();
            f_OPT_EXP();
            break;
        case int_literal:
            f_L_EXP();
            f_OPT_EXP();
            break;
        case string_literal:
            f_L_EXP();
            f_OPT_EXP();
            break;
        case bool_literal:
            f_L_EXP();
            f_OPT_EXP();
            break;
        case kw_null:
            f_L_EXP();
            f_OPT_EXP();
            break;
        case kw_deref:
            f_L_EXP();
            f_OPT_EXP();
            break;
        default:
            error();
    }
}
void f_L_EXP();
void f_L2_EXP();
void f_LU_EXP();

void f_LU2_EXP();
void f_R_EXP();
void f_R2_EXP();
void f_A_EXP();
void f_A2_EXP();
void f_AU_EXP();
void f_AU2_EXP();
void f_POW_EXP();
void f_POW_EXP2();
void f_FIM_EXP();
void f_REF_VAR();
void f_DEREF_VAR();
void f_VAR();

void f_REC_VAR();
void f_NAME_VAR();
void f_NAMELESS_VAR();
void f_NAMELESS_DEREF_VAR_VAR();
void f_NO_PAREN_VAR();
void f_LITERAL();
void f_void_LITERAL();
void f_STMT();
void f_NAME_STMT();
void f_OPT_DOT_NAME_ASSIGN_EXP();
void f_ASSIGN_STMT();
void f_NAME_ASSIGN_STMT();
void f_NAMELESS_ASSIGN_STMT();

void f_OPT_DOT_NAME();
void f_IF_STMT();
void f_T_IF_STMT();
void f_WHILE_STMT();
void f_RETURN_STMT();
void f_CALL_STMT();
void f_NAME_CALL_STMT();
void f_T_CALL_STMT();
void f_U_CALL_STMT();
void f_DO_STMT();
void f_DO_STMT_LIST();
void f_TYPE();
