/**
 * \file Snowflake.cpp
 *
 * \author Yiming Li
 */

#include "stdafx.h"
#include "Snowflake.h"
using namespace::Gdiplus;


/**
 * \brief Constructor
 */
CSnowflake::CSnowflake()
{
}


/**
 * \brief Destructor
 */
CSnowflake::~CSnowflake()
{
}


/**
 * \brief The function to draw the snow flakes
 * \param graphics The device context to draw on
 * \param brush The corlor brush to dawn with
 */
void CSnowflake::Draw(Gdiplus::Graphics *graphics/*, Gdiplus::SolidBrush *brush*/){
	/*int red = rand() % 255;
	int blue = rand() % 255;
	int green = rand() % 255;
	Gdiplus::SolidBrush brush(Color(red, blue, green));*/
	Gdiplus::SolidBrush brush(Color::White);
	graphics->FillEllipse(&brush, mPosition.X, mPosition.Y, 5, 5);
}


/**
 * \brief The update function to redraw the snowflake
 * \param elapsed the time between each update
 */
void CSnowflake::Update(double elapsed){
	mDeltaX = rand()% 30 - rand() % 30;
	mDeltaY = rand() % 80;
	SetPosition(GetPositionX() + mDeltaX * elapsed, GetPositionY() + mDeltaY * elapsed);
}