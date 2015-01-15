/**
 * \file Snowflake.h
 *
 * \author Yiming Li
 *
 * \brief The snowfalke class to inplement the snow
 */

#pragma once
#include <memory>
using namespace::Gdiplus;

/**
 * \brief The snow flake class to implement snow
 */
class CSnowflake
{
public:
	CSnowflake();
	~CSnowflake();
	void Draw(Gdiplus::Graphics *graphics/*, Gdiplus::SolidBrush *brush*/);
	void Update(double elapsed);

	/** \brief The getter function to get the pointer next
	* \return The pointer to next */
	std::shared_ptr<CSnowflake> GetNext(){ return mNext; }
	/** \brief setter function to set the pointer next
	* \param n pointer to next */
	void SetNext(std::shared_ptr<CSnowflake> n){ mNext = n; }
	/** \brief setter function to set the position
	* \param x, x coordinate; 
	* \param y, y coordinate */
	void SetPosition(double x, double y){ mPosition.X = (long)x; mPosition.Y = (long)y; }
	/** \brief The getter function to get the x position
	* \return the x position */
	int GetPositionX(){ return mPosition.X; }
	/** \brief The getter function to get the y position
	* \return the y position */
	int GetPositionY(){ return mPosition.Y; }



private:
	/// The smart pointer pointed to next snowflake in the linked list
	std::shared_ptr<CSnowflake> mNext = nullptr;
	/// The current position of the snowflake
	Gdiplus::Point mPosition;
	/// The velocity of this snowflake on x
	double mDeltaX;
	/// The velocity of this snowflake on y
	double mDeltaY;
};

