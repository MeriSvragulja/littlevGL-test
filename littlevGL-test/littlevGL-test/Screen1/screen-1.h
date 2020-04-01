/**
 * @file lv_tutorial_hello_world
 *
 */

#ifndef LV_TUTORIAL_HELLO_WORLD_H
#define LV_TUTORIAL_HELLO_WORLD_H

#ifdef __cplusplus
extern "C" {
#endif

    /*********************
     *      INCLUDES
     *********************/
#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lvgl.h"
#include "lv_ex_conf.h"
#else
#include "../../../lvgl/lvgl.h"
#include "../../../lv_ex_conf.h"
#endif


     /*********************
      *      DEFINES
      *********************/

      /**********************
       *      TYPEDEFS
       **********************/

       /**********************
        * GLOBAL PROTOTYPES
        **********************/
    void create_screen1(void);

    /**********************
     *      MACROS
     **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_TUTORIAL_HELLO_WORLD_H*/
