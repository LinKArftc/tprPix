/*
 * ========================= config.h ==========================
 *                          -- tpr --
 *                                        CREATE -- 2018.11.21
 *                                        MODIFY --
 * ----------------------------------------------------------
 *   配置 参数
 *   临时，后期会更换为 lua 来实现
 * ----------------------------
 */
#ifndef _TPR_CONFIG_H_
#define _TPR_CONFIG_H_

//-- window 显示尺寸（像素）--
//   拉升窗口将会改变这个值
#define SCR_WIDTH  880
#define SCR_HEIGHT  660

//-- 游戏工作尺寸（游戏像素）--
//   由于是 pixel游戏，所以这个值会很小。
//   这个值 也是 Camera 的尺寸
//-- 目前版本中，拉升窗口并不会改变这个值。（后期应实现 自动匹配）
//-- 请尽量确保此变量 与 SCR_WIDTH／SCR_HEIGHT 等比例
//#define WORK_WIDTH  160
//#define WORK_HEIGHT 120
#define WORK_WIDTH  220
#define WORK_HEIGHT 165


//-- 是否开启 全屏模式 --
inline bool IS_FULL_SCREEN = false; 


//-- 一个 mapSection 占有 256*256 个 mapEnt
#define SECTION_W_ENTS 256
#define SECTION_H_ENTS 256

//-- 一个 mapent 占用 5*5像素
//   CAN'T CHANGE !!! 
//#define PIXES_PER_MAPENT  3
#define PIXES_PER_MAPENT  5
#define HALF_PIXES_PER_MAPENT 2.5

//-- camera.viewingBox z_deep
#define VIEWING_BOX_Z_DEEP  1000



#endif