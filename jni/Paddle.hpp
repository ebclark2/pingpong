#ifndef __PADDLE_HPP__
#define __PADDLE_HPP__

#include <osg/Geode>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>

namespace test
{

class Paddle : public osg::Group
{
public:
	Paddle();

	void setPosition(osg::Vec3d const& pos);
	void setRotation(double rotation);

	void update();

private:
	osg::ref_ptr<osg::PositionAttitudeTransform> Trans;

	bool HasUpdate;
	osg::Vec3d NewPosition;

	double Rotation;

};

}

#endif
