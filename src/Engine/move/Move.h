/*
 * ========================= Move.h ==========================
 *                          -- tpr --
 *                                        CREATE -- 2019.01.13
 *                                        MODIFY --
 * ----------------------------------------------------------
 */
#ifndef TPR_MOVE_H_
#define TPR_MOVE_H_

//-------------------- C --------------------//
//#include <cassert>

//-------------------- CPP --------------------//
#include <functional>

//-------------------- Engine --------------------//
#include "tprAssert.h"
#include "SpeedLevel.h"
#include "MapCoord.h"
#include "DirAxes.h"

//-- need --
class GameObj;
class GameObjPos;
class Collision;



enum class MoveType : int {
    Crawl,
    Drag //- 类似 camera的运动方式：go快速向 目标pos 靠拢
               //  被用于 UI 图标运动
};


//-- 初级版本，在未来可能会发展成 数个 crawl实例 ／ 数个 fly实例
class Move{
    using F_RenderUpdate = std::function< void() >;
public:
    Move() = default;

    //- 在 gameObj.init() 中被调用 --
    inline void init(   GameObj *_goPtr, 
                        GameObjPos *_goPosPtr,
                        Collision *_collisionPtr ){ //-- MUST --
        this->goPtr    = _goPtr;
        this->goPosPtr = _goPosPtr;
        this->collisionPtr = _collisionPtr;
    }

    inline void RenderUpdate(){
        this->renderUpdataFunc();
    }

    //------- flags -------//
    inline bool is_crawl() const {
        return (this->moveType==MoveType::Crawl);
    }

    //------- set -------//
    inline void set_MoveType( MoveType _type ){
        this->moveType = _type;
        switch ( _type ){
            case MoveType::Crawl:      
                this->renderUpdataFunc = std::bind( &Move::crawl_renderUpdate, this ); 
                return;
            case MoveType::Drag: 
                this->renderUpdataFunc = std::bind( &Move::drag_renderUpdate, this ); 
                return;
            default:
                tprAssert(0);
                return;
        }
    }
    inline void set_speedLvl( SpeedLevel _lv ){
        this->speedLvl = _lv;
    }
    void set_newCrawlDirAxes( const DirAxes &_newDirAxes );


    inline void set_drag_targetFPos( const glm::vec2 &_FPos ){
        tprAssert( this->moveType == MoveType::Drag );
        if( _FPos == this->targetFPos ){
            return;
        }
        this->targetFPos = _FPos;
        this->isMoving = true;
    }

    //------- get -------//
    inline const SpeedLevel &get_speedLvl() const {
        return this->speedLvl;
    }
    inline bool is_drag_moving() const {
        tprAssert( this->moveType == MoveType::Drag );
        return this->isMoving;
    } 

private:

    void crawl_renderUpdate();
    void drag_renderUpdate();


    void crawl_renderUpdate_inn(const DirAxes &_newDirAxes,
                                const glm::vec2 &_speedV );

    //===== vals =====//
    GameObj     *goPtr    {nullptr}; //- 每个 fly实例 都属于一个 go实例, 强关联
    GameObjPos  *goPosPtr {nullptr};
    Collision   *collisionPtr {nullptr}; 

    MoveType   moveType {MoveType::Crawl};
    SpeedLevel   speedLvl  { SpeedLevel::LV_3 };

    
    DirAxes  newDirAxes     {};  //- 本次渲染帧，新传入的 方向值（每一帧都被外部代码更新）
    DirAxes  currentDirAxes {};  //- 当前正在处理的  方向值。（只在节点帧被改写）

    glm::vec2 targetFPos  {};

    F_RenderUpdate renderUpdataFunc {nullptr}; //- functor
                                               //- 只在初始化阶段绑定，也许未来是可以切换的，但目前未实现


    //===== flags =====//
    bool   isMoving {false};

};


#endif 

