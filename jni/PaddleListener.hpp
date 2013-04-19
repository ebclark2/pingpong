#ifndef __PADDLE_LISTENER_HPP__
#define __PADDLE_LISTENER_HPP__

#include <osg/BoundingBox>

namespace test
{

class Paddle;

class PaddleListener
{
public:
	virtual void paddleMoved(test::Paddle * paddle, osg::Vec3d const& prevPos, osg::Vec3d const& currPos) { }
};

}

#endif
