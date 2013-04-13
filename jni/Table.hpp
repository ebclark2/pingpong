#ifndef __TABLE_HPP__
#define __TABLE_HPP__

#include <osg/Geode>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>

namespace test
{

class Table : public osg::PositionAttitudeTransform
{
public:
	Table();

};

}

#endif
