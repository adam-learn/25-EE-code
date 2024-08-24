//
// Created by RM UI Designer
//

#include "ui_default_Ungroup_3.h"
#include "string.h"

#define FRAME_ID 0
#define GROUP_ID 0
#define START_ID 3

ui_string_frame_t ui_default_Ungroup_3;

ui_interface_string_t* ui_default_Ungroup_anti = &ui_default_Ungroup_3.option;

void _ui_init_default_Ungroup_3() {
    ui_default_Ungroup_3.option.figure_name[0] = FRAME_ID;
    ui_default_Ungroup_3.option.figure_name[1] = GROUP_ID;
    ui_default_Ungroup_3.option.figure_name[2] = START_ID;
    ui_default_Ungroup_3.option.operate_tpyel = 1;
    ui_default_Ungroup_3.option.figure_tpye = 7;
    ui_default_Ungroup_3.option.layer = 5;
    ui_default_Ungroup_3.option.font_size = 30;
    ui_default_Ungroup_3.option.start_x = 1350;
    ui_default_Ungroup_3.option.start_y = 660;
    ui_default_Ungroup_3.option.color = 7;
    ui_default_Ungroup_3.option.str_length = 4;
    ui_default_Ungroup_3.option.width = 3;
    strcpy(ui_default_Ungroup_anti->string, "ANTI");

    ui_proc_string_frame(&ui_default_Ungroup_3);
    SEND_MESSAGE((uint8_t *) &ui_default_Ungroup_3, sizeof(ui_default_Ungroup_3));
}

void _ui_update_default_Ungroup_3() {
    ui_default_Ungroup_3.option.operate_tpyel = 2;

    ui_proc_string_frame(&ui_default_Ungroup_3);
    SEND_MESSAGE((uint8_t *) &ui_default_Ungroup_3, sizeof(ui_default_Ungroup_3));
}

void _ui_remove_default_Ungroup_3() {
    ui_default_Ungroup_3.option.operate_tpyel = 3;

    ui_proc_string_frame(&ui_default_Ungroup_3);
    SEND_MESSAGE((uint8_t *) &ui_default_Ungroup_3, sizeof(ui_default_Ungroup_3));
}