#ifndef TEST_H_
#define TEST_H_

#include "SCARA.h"

#define MAX_MOTION_NUM 5

uint8_t motion_erase = 1;
uint8_t motion_page = 11;
uint8_t motion_repeat = 0;

const float move_time = 5.0f;
float init_arg[2] = {move_time, ACTUATOR_CONTROL_TIME};
void *p_init_arg = init_arg;
float radius = 0.015f;
float angular_position = 0.0f;

void test()
{
  if (SCARA.moving() || SCARA.drawing()) {
    return;
  }
  else {      
    if (motion_erase == 1){
      if (motion_repeat == 0){
        SCARA.toolMove(TOOL, -0.5f);
        motion_repeat++;
      }    
      else if (motion_repeat == 1){
        std::vector<float> goal_position;
        goal_position.push_back(-0.52);
        goal_position.push_back(0.6);
        goal_position.push_back(0.72);

        SCARA.jointMove(goal_position, 3.0f); 
        motion_repeat++;
      }    
      else if (motion_repeat == 2){
        SCARA.toolMove(TOOL, 0.0f);

        std::vector<float> goal_position;
        goal_position.push_back(-0.52);
        goal_position.push_back(0.6);
        goal_position.push_back(0.72);
        SCARA.jointMove(goal_position, 3.0f); 

        motion_repeat++;
      }    
      else if (motion_repeat == 3){
        SCARA.toolMove(TOOL, -0.5f);

        std::vector<float> goal_position;
        goal_position.push_back(-0.52);
        goal_position.push_back(0.6);
        goal_position.push_back(0.72);
        SCARA.jointMove(goal_position, 3.0f); 

        motion_repeat++;
      }    
      else {
        std::vector<float> goal_position;
        goal_position.push_back(-1.0);
        goal_position.push_back(0.5);
        goal_position.push_back(1.3);
        SCARA.jointMove(goal_position, 2.0f); 

        motion_erase = 0;
        motion_repeat = 0;
      }
    }
    else {
        // std::vector<float> goal_position;
        // goal_position.push_back(-1.0);
        // goal_position.push_back(0.5);
        // goal_position.push_back(1.3);
        // SCARA.jointMove(goal_position, 2.0f); 

        SCARA.toolMove(TOOL, 0.0f);

        if (motion_page == CIRCLE) {
          
          SCARA.drawInit(CIRCLE, move_time, angular_position, p_init_arg);
          SCARA.setRadiusForDrawing(CIRCLE, radius);  
          SCARA.setStartPositionForDrawing(CIRCLE, SCARA.getComponentPositionToWorld(TOOL));
          SCARA.draw(CIRCLE);

          radius += 0.002f;
          motion_repeat++;
          
          if (motion_repeat == 4){
            motion_erase = 1;
            motion_page++;
            motion_repeat = 0;
            radius = 0.015f;
        }
      } 
      else if (motion_page == RHOMBUS) {
        SCARA.drawInit(RHOMBUS, move_time, angular_position, p_init_arg);
        SCARA.setRadiusForDrawing(RHOMBUS, radius);  
        SCARA.setStartPositionForDrawing(RHOMBUS, SCARA.getComponentPositionToWorld(TOOL));
        SCARA.draw(RHOMBUS);

        radius += 0.002f;
        motion_repeat++;

        if (motion_repeat == 4){
          motion_erase = 1;
          motion_page++;
          motion_repeat = 0;
          radius = 0.015f;
        }
      } 
      else if (motion_page == HEART) { 
        radius = 0.030f;
        SCARA.drawInit(HEART, move_time, angular_position, p_init_arg);
        SCARA.setRadiusForDrawing(HEART, radius);  
        SCARA.setStartPositionForDrawing(HEART, SCARA.getComponentPositionToWorld(TOOL));
        SCARA.draw(HEART);

        motion_erase = 1;
        motion_page++;
        radius = 0.015f;
      } 

      else if (motion_page == CIRCLE2) { 
        SCARA.drawInit(CIRCLE, move_time, angular_position, p_init_arg);
        SCARA.setRadiusForDrawing(CIRCLE, radius);  
        SCARA.setStartPositionForDrawing(CIRCLE, SCARA.getComponentPositionToWorld(TOOL));
        SCARA.draw(CIRCLE);

        motion_repeat++;

        if (motion_repeat == 4){
          motion_erase = 1;
          motion_page++;
          motion_repeat = 0;
        }
      } 

      else
        motion_page = 11;

    }
  }
}

#endif // TEST_H_
