#include "pong.h"

ballPos paddle_pos = 30;
uint8_t paddle_width = 10;
uint8_t paddle_height = 2;
uint8_t paddle_speed = 3;


ballPos ball_x = 20;
ballPos ball_y = 20;

ballPos vel_x = 1;
ballPos vel_y = -2;

uint8_t ball_radius = 3;

uint16_t num_bounces = 0;


void pong_start_screen(void)
{
SSD1306_Fill(SSD1306_COLOR_BLACK);
SSD1306_GotoXY (40, 20);
SSD1306_Puts ("PONG", &Font_11x18, SSD1306_COLOR_WHITE);

SSD1306_GotoXY (15, 50);
SSD1306_Puts ("Press to start", &Font_7x10, SSD1306_COLOR_WHITE);

SSD1306_UpdateScreen();
}

void pong_move_paddle(void)
{

	paddle_pos = paddle_pos + paddle_speed *(BUTTON_RIGHT - BUTTON_LEFT);

	  if(paddle_pos < 0){
		  paddle_pos = 0;
	  } else if (paddle_pos > SSD1306_WIDTH - paddle_width - 1){
		  paddle_pos = SSD1306_WIDTH - paddle_width - 1;
	  }

}

void pong_wait_for_button_press(void)
{
	while(BUTTON_LEFT == 0 && BUTTON_RIGHT == 0)
	{
	}

	while(BUTTON_LEFT == 1 || BUTTON_RIGHT == 1)
	{
	}
}

void reset_game(void)
{
	paddle_pos = 30;

	ball_x = 20;
	ball_y = 20;

	vel_x = 1;
	vel_y = -2;

	num_bounces = 0;

}


void pong_update_ball_pos(void)
{
	ball_x += vel_x;
	ball_y += vel_y;

	if(ball_x < ball_radius && vel_x < 0){
		ball_x = 2*ball_radius -ball_x;
		vel_x = -vel_x;
	} else if (ball_x > SSD1306_WIDTH-ball_radius-1 && vel_x > 0){
		ball_x = 2*SSD1306_WIDTH - ball_x - 2*ball_radius ;
		vel_x = -vel_x;
	}

	if(ball_y < ball_radius && vel_y < 0){
		ball_y = 2*ball_radius -ball_y;
		vel_y = -vel_y;
	}

//	else if (ball_y > SSD1306_HEIGHT-ball_radius-1  && vel_y > 0){
//		ball_y= 2*SSD1306_HEIGHT - ball_y - 2*ball_radius-2;
//		vel_y = -vel_y;
//	}

}

void pong_game_over(void){
	SSD1306_Fill(SSD1306_COLOR_BLACK);
	SSD1306_DrawFilledRectangle((uint8_t) paddle_pos, SSD1306_HEIGHT-2, 10, 1, SSD1306_COLOR_WHITE);
	SSD1306_DrawFilledCircle((uint8_t)ball_x, (uint8_t)ball_y, ball_radius, SSD1306_COLOR_WHITE);
	SSD1306_GotoXY (20, 20);
	SSD1306_Puts ("GAME OVER", &Font_11x18, SSD1306_COLOR_WHITE);

	char score[20];
	itoa(num_bounces, score, 10);

	SSD1306_GotoXY (30, 40);
	SSD1306_Puts (strcat(score, " bounces"), &Font_7x10, SSD1306_COLOR_WHITE);

	SSD1306_UpdateScreen();
}

void bounce_off_paddle(void)
{
	ball_y= 2*SSD1306_HEIGHT - ball_y - 2*ball_radius-2 - 2*paddle_height;
	vel_y = -vel_y;
	num_bounces += 1;
}

bool pong_ball_at_paddle(void)
{
	if(ball_y + vel_y > SSD1306_HEIGHT - 1 - paddle_height){
		return TRUE;
	} else {
		return FALSE;
	}
}

bool ball_in_paddle(void)
{

	ballPos next_frame_x = ball_x + vel_x/2;
	if(next_frame_x > paddle_pos - ball_radius && next_frame_x < paddle_pos + paddle_width + ball_radius){
		return TRUE;
	} else {
		return FALSE;
	}
}


void pong_display_frame(void)
{
	char buffer[20];

	SSD1306_Fill(SSD1306_COLOR_BLACK);
	SSD1306_DrawFilledRectangle((uint8_t) paddle_pos, SSD1306_HEIGHT-2, 10, 1, SSD1306_COLOR_WHITE);
	SSD1306_DrawFilledCircle((uint8_t)ball_x, (uint8_t)ball_y, ball_radius, SSD1306_COLOR_WHITE);
//	SSD1306_GotoXY (2, 2);
//	SSD1306_Puts (itoa(paddle_pos, buffer, 10), &Font_11x18, SSD1306_COLOR_WHITE);

	SSD1306_UpdateScreen();
}

ballPos get_ball_x(void){
	return ball_x;
}

ballPos get_ball_y(void){
	return ball_y;
}
