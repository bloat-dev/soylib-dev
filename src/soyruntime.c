
/******************************/
/* Soy Engine App   v1x2      */
/* Copyright 2021 Maj Z Novak */
/* All Rights Reserved        */
/* 							  */
/******************************/

/******************************/
/* Usage:                     */
/*                            */
/* Create the soyApp object   */
/* globally and initialize it */
/* in your main() function    */
/* using user_functions(..)   */
/* and open_application(..):  */
/*                            */
/* soyApp app;                */
/*                            */
/* int main() {               */
/* 	user_functions(...);      */
/* 	open_application(...);    */
/* }                          */
/*                            */
/* The engine will run until  */
/* the 'running' flag in the  */
/* soyApp struct is set to    */
/* FALSE or 0.         	      */
/*                            */
/* User must supply their     */
/* own INIT, FREE and UPDATE  */
/* functions and register     */
/* them with the app.         */
/* User functions must match  */
/* the following formats      */
/* exactly (except the name): */
/* 							  */
/* UPDATE FUNCTION FORMAT:    */
/* int myUpdate(double delta) */
/* 							  */
/* INIT FUNCTION FORMAT:      */
/* int myInit(double delta)   */
/* 							  */
/* FREE FUNCTION FORMAT:      */
/* int myFree(double delta)   */
/* 							  */
/******************************/

/******************************/
/* #include "soyengine.h"     */
/* this is the only header	  */
/* you need to include        */
/* 							  */
/******************************/
#include "soyengine.h"


/********************************************************************/
/* soyApp structure:          										*/
/*                                                                  */
/* public members:                                                  */
/*                                                                  */
/*   -flag running     .... App will run while TRUE                 */
/*   -flag clearBuffer .... App will clear the draw buffer if TRUE  */
/*   -soyWindow window .... Operating system window structure       */
/*   -soyCanvas canvas .... Drawing surface structure               */
/* 							                                        */
/********************************************************************/
soyApp app;

/***************************************************/
/* Initialize global variables here                */
/*                                                 */
/***************************************************/
soyModel cubeModel;
soyTransform trans;

float animFloat = 0.0f;

/***************************************************/
/* Initialize all your 'created' objects here      */
/*                                                 */
/***************************************************/
int user_init() {
	create_model(&cubeModel, "Assets/Meshes/blendCube.obj", "cube");
	return 0;
}

/***************************************************/
/* Free all your 'created' objects here            */
/*                                                 */
/***************************************************/
int user_free() {
	free_model(&cubeModel);
	return 0;
}

/***************************************************/
/* This gets called every frame                    */
/*                                                 */
/***************************************************/
int user_update(double delta) {
	animFloat+=delta*0.0001;
	trans = soy_transform(0,0,-10);
	transform_rotate(&trans, 0.25f, 0.0f, animFloat*0.2);
	draw_set_colour(0,0,0,255);
	draw_model(&cubeModel, &app.mainCamera, &trans, NULL, NULL);
	return 0;
}

/***************************************************/
/* application entry point                         */
/*                                                 */
/***************************************************/
int main(int argc, char* argv[]) {

	/************************************************************************/
	/* User must register their own functions with user_functions(...).     */
	/* If a parameter is NULL, the engine will use a default method         */
	/* Format: app address / init / update / free                           */
	/*                                                                      */
	/************************************************************************/
	user_functions(&app, user_init, user_update, user_free );

	/************************************************************************/
	/* After registering functions, open and run the application until      */
	/* a close event occurs or user sets 'running' flag to 0 or FALSE		*/
	/* Format: app address / width / height / pixel size / title            */
	/*                                                                      */
	/************************************************************************/
	open_application(&app, 1080, 720, 1, "SoyLib v1.3");
	return 0;
}
