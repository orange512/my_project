/*************************************************************************
	> File Name: red_module.h
	> Author: 
	> Mail: 
	> Created Time: 2017年11月03日 星期五 18时29分52秒
 ************************************************************************/

#ifndef _RED_MODULE_H
#define _RED_MODULE_H
int send_packet(int connfd,struct msg msg);
int recv_packet(int connfd,struct msg msg);
#endif
