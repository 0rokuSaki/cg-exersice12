/*****************************************************************//**
 * \file   Point.h
 * \brief  Declaration of struct Point.
 * 
 * \author aaron
 * \date   March 2023
 *********************************************************************/

#pragma once
/* A representation of a point in 2d */
struct Point
{
    double x, y;

    Point() : x(0.0), y(0.0) {}

    Point(double xVal, double yVal) : x(xVal), y(yVal) {}
};
