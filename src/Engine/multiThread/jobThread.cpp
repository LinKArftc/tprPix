/*
 * ========================== JobThread.h =======================
 *                          -- tpr --
 *                                        CREATE -- 2019.04.24
 *                                        MODIFY -- 
 * ----------------------------------------------------------
 */

//-------------------- C --------------------//
//#include <cassert>

//-------------------- CPP --------------------//
//#include <vector>
#include <iostream>
#include <string>
#include <thread>

//-------------------- Libs --------------------//
//#include "tprDataType.h"

//-------------------- Engine --------------------//
#include "tprAssert.h"
#include "Job.h"
#include "jobs_all.h"
#include "esrc_jobQue.h"


using std::cout;
using std::endl;

//namespace{//------------ namespace --------------//
//}//---------------- namespace end --------------//

/* ===========================================================
 *                   jobThread_main
 * -----------------------------------------------------------
 * -- job thread enter point
 */
void jobThread_main(){

    cout << "jobThread_main(): start;" << endl;

    //-- 一个 jobThread 只有一个 job实例，就在这里
    //   不应放在 堆中，因为 本函数可能是 数个 thread 的 main函数
    Job job {};

    while( true ){

        //-- 唯一的退出条件 --
        if( esrc::atom_exitJobThreadsFlag_load() &&
            esrc::atom_is_jobQue_empty() ){
            break;
        }

        //-- 从 esrc::jobQue 读取一个 job --
        //  若没抢到锁，或者 esrc::jobQue 为空，将阻塞与此，直到条件达成
        job = esrc::atom_pop_from_jobQue(); //- copy

        //-- handle the job --//
        switch (job.jobType){
        case JobType::JustTimeOut:
            //--仅仅说明，单次读取时间到，请再走一次while循环
            //  只有这样，才能保证 不会被 pop 函数永久阻塞
            //  进而才能 合理地 终止 本job线程
            break;
        case JobType::Build_ChunkData:
            //....
            build_chunkData_main( job );
            break;
        
        default:
            tprAssert(0);
        }
    }//--- while: end ---

    //-- exit the job thread --
    cout << "jobThread_main(): end the jobThread: " << std::this_thread::get_id()
         << endl;
}







