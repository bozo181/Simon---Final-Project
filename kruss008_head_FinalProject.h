/*
 * File: kruss008_head_FinalProject.h
 *
 * Author: Tyler Krussow
 */ 
#ifndef kruss008_head_FinalProject_H
#define	kruss008_head_FinalProject_H
#include <xc.h>   


#ifdef	__cplusplus
extern "C" {
#endif 
    void wait_ms(long int ms);
    void delay_ms(void);
    void lcd_init(void);
    void lcd_setCursor(char x, char y);
    void lcd_cmd(char Package);
    void lcd_printString(char *s);
    void shift(void);
#ifdef	__cplusplus
}
#endif 

#endif	/* kruss008_head_FinalProject_H */

