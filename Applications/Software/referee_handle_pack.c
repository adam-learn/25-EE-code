#include "cover_headerfile_h.h"
#include "referee_handle_pack.h"

REFEREE_DATA_t REFEREE_DATA;

frame_header_struct_t referee_receive_header;
frame_header_struct_t referee_send_header;

ext_game_status_t game_status;//0x0001  比赛状态数据
ext_game_result_t game_result;//0x0002  比赛结果数据
ext_game_robot_HP_t game_robot_HP;//0x0003  机器人血量数据

ext_event_data_t event_data;//0x0101  场地事件数据

ext_supply_projectile_action_t supply_projectile_action;//0x0102  补给站动作标识数据

ext_referee_warning_t referee_warning;//0x0104  裁判警告数据

ext_dart_remaining_time_t dart_remaining_time;//0x0105  飞镖发射时间数据 

ext_robot_status_t robot_status;//0x201  机器人性能体系数据

ext_power_heat_data_t power_heat_data;//0x202  实时功率热量数据

ext_robot_pos_t robot_pos;//0x203  机器人位置数据

ext_buff_t robot_buff;//0x0204  机器人增益数据

ext_air_support_data_t air_support_data;//0x0205  空中支援时间数据

ext_hurt_data_t hurt_data;//0x0206  伤害状态数据

ext_shoot_data_t shoot_data;//0x0207  实时射击数据

ext_projectile_allowance_t projectile_allowance;//0x0208  允许发弹量

ext_rfid_status_t rfid_status;//0x0209  机器人 RFID 状态

ext_dart_client_cmd_t dart_client_cmd;//0x020A  飞镖选手端指令数据

ext_ground_robot_position_t ground_robot_position;//0x020B  地面机器人位置数据

ext_radar_mark_data_t radar_mark_data;//0x020C  雷达标记进度数据

ext_robot_interaction_data_t robot_interaction_data;//0x0301  机器人交互数据

ext_map_command_t map_command;//0x0303  选手端小地图交互数据

ext_map_robot_data_t map_robot_data;//0x0305  选手端小地图接收雷达数据

ext_map_sentry_data_t map_sentry_data;//0x0307  选手端小地图接收哨兵数据




ext_custom_robot_data_t custom_robot_data;//0x0302  自定义控制器与机器人交互数据

ext_remote_control_t remote_control;//0x0304  键鼠遥控数据

ext_custom_client_data_t custom_client_data;//0x0306  自定义控制器与选手端交互数据





void init_referee_struct_data(void)
{
    memset(&referee_receive_header, 0, sizeof(frame_header_struct_t));
    memset(&referee_send_header, 0, sizeof(frame_header_struct_t));

    memset(&game_status, 0, sizeof(ext_game_status_t));
    memset(&game_result, 0, sizeof(ext_game_result_t));
    memset(&game_robot_HP, 0, sizeof(ext_game_robot_HP_t));

    memset(&event_data, 0, sizeof(ext_event_data_t));

    memset(&supply_projectile_action, 0, sizeof(ext_supply_projectile_action_t));

    memset(&referee_warning, 0, sizeof(ext_referee_warning_t));

    memset(&dart_remaining_time, 0, sizeof(ext_dart_remaining_time_t));

    memset(&robot_status, 0, sizeof(ext_robot_status_t));

    memset(&power_heat_data, 0, sizeof(ext_power_heat_data_t));

    memset(&robot_pos, 0, sizeof(ext_robot_pos_t));

    memset(&air_support_data, 0, sizeof(ext_air_support_data_t));

    memset(&hurt_data, 0, sizeof(ext_hurt_data_t));

    memset(&shoot_data, 0, sizeof(ext_shoot_data_t));

    memset(&projectile_allowance, 0, sizeof(ext_projectile_allowance_t));

    memset(&rfid_status, 0, sizeof(ext_rfid_status_t));    

    memset(&dart_client_cmd, 0, sizeof(ext_dart_client_cmd_t));   

    memset(&ground_robot_position, 0, sizeof(ext_ground_robot_position_t));           

    memset(&radar_mark_data, 0, sizeof(ext_radar_mark_data_t));   

    memset(&radar_mark_data, 0, sizeof(ext_radar_mark_data_t));          

    memset(&robot_interaction_data, 0, sizeof(ext_robot_interaction_data_t));
 
    memset(&map_command, 0, sizeof(ext_map_command_t));

    memset(&map_robot_data, 0, sizeof(ext_map_robot_data_t));

    memset(&custom_robot_data, 0, sizeof(ext_custom_robot_data_t));

    memset(&remote_control, 0, sizeof(ext_remote_control_t));

    memset(&custom_client_data, 0, sizeof(ext_custom_client_data_t));

}

void referee_data_solve(uint8_t *frame)
{
    uint16_t cmd_id = 0;
    uint8_t index = 0;

    memcpy(&referee_receive_header, frame, sizeof(frame_header_struct_t));

    index += sizeof(frame_header_struct_t);

    memcpy(&cmd_id, frame + index, sizeof(uint16_t));
    index += sizeof(uint16_t);

    switch (cmd_id)
    {
        case GAME_STATE_CMD_ID:
        {
            memcpy(&game_status, frame + index, sizeof(ext_game_status_t));
        }
        break;
        case GAME_RESULT_CMD_ID:
        {
            memcpy(&game_result, frame + index, sizeof(ext_game_result_t));
        }
        break;
        case GAME_ROBOT_HP_CMD_ID:
        {
            memcpy(&game_robot_HP, frame + index, sizeof(ext_game_robot_HP_t));
        }
        break;
        case FIELD_EVENTS_CMD_ID:
        {
            memcpy(&event_data, frame + index, sizeof(ext_event_data_t));
        }
        break;
        case SUPPLY_PROJECTILE_ACTION_CMD_ID:
        {
            memcpy(&supply_projectile_action, frame + index, sizeof(ext_supply_projectile_action_t));
        }
        break;
        case REFEREE_WARNING_CMD_ID:
        {
            memcpy(&referee_warning, frame + index, sizeof(ext_referee_warning_t));
        }
        break;
        case DART_LAUNCH_TIME_CMD_ID:
        {
            memcpy(&dart_remaining_time, frame + index, sizeof(ext_dart_remaining_time_t));
        }
        break;
        case ROBOT_STATE_CMD_ID:
        {
            memcpy(&robot_status, frame + index, sizeof(ext_robot_status_t));
        }
        break;
        case POWER_HEAT_DATA_CMD_ID:
        {
            memcpy(&power_heat_data, frame + index, sizeof(ext_power_heat_data_t));
        }
        break;
        case ROBOT_POS_CMD_ID:
        {
            memcpy(&robot_pos, frame + index, sizeof(ext_robot_pos_t));
        }
        break;
        case BUFF_MUSK_CMD_ID:
        {
            memcpy(&robot_buff, frame + index, sizeof(ext_buff_t));
        }
        break;
        case AERIAL_ROBOT_ENERGY_CMD_ID:
        {
            memcpy(&air_support_data, frame + index, sizeof(ext_air_support_data_t));
        }
        break;
        case ROBOT_HURT_CMD_ID:
        {
            memcpy(&hurt_data, frame + index, sizeof(ext_hurt_data_t));
        }
        break;
        case SHOOT_DATA_CMD_ID:
        {
            memcpy(&shoot_data, frame + index, sizeof(ext_shoot_data_t));
        }
        break;
        case BULLET_REMAINING_CMD_ID:
        {
            memcpy(&projectile_allowance, frame + index, sizeof(ext_projectile_allowance_t));
        }
        break;
        case ROBOT_RFID_STATE_CMD_ID:
        {
            memcpy(&rfid_status, frame + index, sizeof(ext_rfid_status_t));
        }
        break;
        case DART_PLAYER_COMMAND_CMD_ID:
        {
            memcpy(&dart_client_cmd, frame + index, sizeof(ext_dart_client_cmd_t));
        }
        break;
        case GROUND_ROBOT_POSITION_CMD_ID:
        {
            memcpy(&ground_robot_position, frame + index, sizeof(ext_ground_robot_position_t));
        }
        break;
        case RADAR_MARKS_PROGRESS_CMD_ID:
        {
            memcpy(&radar_mark_data, frame + index, sizeof(ext_radar_mark_data_t));
        }
        break;
        case ROBOT_INTERACTION_CMD_ID:
        {
            memcpy(&robot_interaction_data, frame + index, sizeof(ext_robot_interaction_data_t));
        }
        break;
        case CUSTOM_CONTROLLER_AND_BOT_INTERACTION_CMD_ID:
        {
            memcpy(&custom_robot_data, frame + index, sizeof(ext_custom_robot_data_t));
        }
        break;
        case PLAYER_SIDE_MINIMAP_INTERACTION_CMD_ID:
        {
            memcpy(&map_command, frame + index, sizeof(ext_map_command_t));
        }
        break;
        case KEYBOARD_AND_MOUSE_REMOTE_CONTROL_CMD_ID:
        {
            memcpy(&remote_control, frame + index, sizeof(ext_remote_control_t));
        }
        break;
        case PLAYER_MINIMAP_RECEIVES_RADAR_CMD_ID:
        {
            memcpy(&map_robot_data, frame + index, sizeof(ext_map_robot_data_t));
        }
        break;
        case INTERACTION_DATA_BETWEEN_CONTROLLER_AND_PLAYER_CMD_ID:
        {
            memcpy(&custom_client_data, frame + index, sizeof(ext_custom_client_data_t));
        }
        break;
        case PLAYER_MINIMAP_RECEIVES_SENTRY_CMD_ID:
        {
            memcpy(&map_sentry_data, frame + index, sizeof(ext_map_sentry_data_t));
        }
        break;
        default:
        {
            break;
        }
    }
}



//从裁判系统获取车辆ID
uint8_t get_robot_id(void)
{
    return robot_status.robot_id;
}


//从裁判系统获取车辆电管底盘输出功率和缓冲能量
void get_chassis_power_and_buffer(fp32 *power, uint16_t *buffer)
{
    *power = power_heat_data.chassis_power;
    *buffer = power_heat_data.buffer_energy;
}


//从裁判系统获取车辆底盘电压 电流 电管底盘输出能量功率 和 缓冲能量
void get_chassis_VOL_CUR_POW_BUF(uint16_t *chassis_voltage,uint16_t *chassis_current,float *chassis_power, uint16_t *buffer_energy)
{
    *chassis_voltage = power_heat_data.chassis_voltage;
    *chassis_current = power_heat_data.chassis_current;
    *chassis_power   = power_heat_data.chassis_power;
    *buffer_energy   = power_heat_data.buffer_energy; 
}


void get_chassis_power_limit(uint16_t *chassis_power_limit)
{
    *chassis_power_limit = robot_status.chassis_power_limit;
}


const ext_robot_status_t *get_robot_state_point(void)
{
    return &robot_status;
}

const ext_power_heat_data_t *get_power_heat_data_point(void)
{
    return &power_heat_data;
}


const ext_shoot_data_t *get_shoot_data_point(void)
{
    return &shoot_data;
}



void Required_Data(void) //后续可根据需要自行添加
{
		REFEREE_DATA.Initial_SPEED = shoot_data.initial_speed; 
		REFEREE_DATA.Launching_Frequency = shoot_data.launching_frequency;

		REFEREE_DATA.Barrel_Heat = power_heat_data.shooter_17mm_1_barrel_heat;  		
		REFEREE_DATA.CooLing_Value = robot_status.shooter_barrel_cooling_value;		
		REFEREE_DATA.Heat_Limit =  robot_status.shooter_barrel_heat_limit;	
		REFEREE_DATA.Chassis_Voltage =  power_heat_data.chassis_voltage; 
		REFEREE_DATA.Chassis_Current =  power_heat_data.chassis_current;  
		REFEREE_DATA.Buffer_Energy = power_heat_data.buffer_energy;
		REFEREE_DATA.Chassis_Power = power_heat_data.chassis_power; 
		REFEREE_DATA.Chassis_Power_Limit = robot_status.chassis_power_limit; 
}





