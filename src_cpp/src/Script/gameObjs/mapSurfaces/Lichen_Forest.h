/*
 * ========================= Lichen_Forest.h ==========================
 *                          -- tpr --
 *                                        CREATE -- 2019.04.10
 *                                        MODIFY -- 
 * ----------------------------------------------------------
 *   地衣
 * ----------------------------
 */
#ifndef TPR_LICHEN_FOREST_H
#define TPR_LICHEN_FOREST_H

//-------------------- CPP --------------------//
#include <string>
#include <vector>
#include <functional>

//-------------------- Engine --------------------//
#include "tprAssert.h"
#include "GameObj.h"
#include "GameObjMesh.h"
#include "AnimFrameSet.h"
#include "PubBinaryValType.h"
#include "MapAltitude.h"
#include "Density.h"


namespace gameObjs{//------------- namespace gameObjs ----------------


//-- 定义了 go.binary 的数据格式 --
inline std::vector<PubBinaryValType> lichen_Forest_pubBinaryValTypes {
    PubBinaryValType::HP,
    PubBinaryValType::MP
};

struct Lichen_Forest_PvtBinary{
    size_t   lichen_ForestId {0};
            //- 简单的从 几种款式中，随机挑选一款 [0,7]
    //===== padding =====//
    //...
};


class Lichen_Forest{
public:
    Lichen_Forest() = default;

    //--- 延迟init ---//
    void init_in_autoMod(   GameObj &goRef_,
                            const IntVec2 &mpos_,
					        float fieldWeight_,
					        const MapAltitude &alti_,
					        const Density &_density );
                            
    void bind( GameObj &goRef_ );

    //--- 从硬盘读取到 go实例数据后，重bind callback
    void rebind( GameObj &goRef_ );

    //--- callback ---//
    void OnRenderUpdate( GameObj &goRef_ ); 
    void OnLogicUpdate( GameObj &goRef_ ); 


    //--  每次调用回调函数，都需要做的 指针重绑定 --
    inline Lichen_Forest_PvtBinary *rebind_ptr( GameObj &goRef_ ){

        tprAssert( goRef_.species == Lichen_Forest::specId );
        return reinterpret_cast<Lichen_Forest_PvtBinary*>(goRef_.get_pvtBinaryPtr());
    }

    //======== static ========//
    static  u32_t  specId; //- 在 onGoSpecIds_SignUp() 中手动设置...


private:
    //--- callback ---//
    void OnActionSwitch( GameObj &goRef_, ActionSwitchType type_ );

};

//---------- static ----------//
inline u32_t  Lichen_Forest::specId {0}; //- 具体值在 goSpecIds.cpp 中分配

//=====< 本类 唯一的 保留实例 >=====
inline Lichen_Forest  lichen_Forest {};


}//------------- namespace gameObjs: end ----------------
#endif 


