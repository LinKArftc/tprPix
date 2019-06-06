/*
 * ========================= gl_funcs.h ===================
 *                          -- tpr --
 *                                        CREATE -- 2018.11.21
 *                                        MODIFY -- 
 * ----------------------------------------------------------
 *   gl 模块中的 公共函数
 * ----------------------------
 */
#ifndef TPR_GL_H_
#define TPR_GL_H_
//=== *** glad FIRST, glfw SECEND *** ===
#include<glad/glad.h>  
#include<GLFW/glfw3.h>

//------------------- Engine --------------------//
#include "IntVec.h"

//------ gl_support.cpp -----//
void glfw_init();
void glfw_hints_set();
void glfw_window_creat();
void glfw_oth_set();
void glfw_callback_set();

void glad_init();
void glad_set();

#endif
