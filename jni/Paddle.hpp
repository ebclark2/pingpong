#ifndef __PADDLE_HPP__
#define __PADDLE_HPP__

#include <osg/PositionAttitudeTransform>

namespace test
{

class Paddle : public osg::Group
{
private:
	static const osg::Vec3d OFFSET;

public:
	Paddle();

	inline osg::Vec3d getPosition() const { return Trans->getPosition(); }
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
