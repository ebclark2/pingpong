#ifndef __PADDLE_HPP__
#define __PADDLE_HPP__

#include "PaddleListener.hpp"

#include <osg/BoundingBox>
#include <osg/Geode>
#include <osg/PositionAttitudeTransform>

#include <set>

namespace test
{

class Paddle : public osg::Group
{
private:
	static const osg::Vec3d OFFSET;

private:
	typedef std::set<PaddleListener *> PaddleListenerSet;

public:
	Paddle();

	inline osg::Vec3d getPosition() const { return Trans->getPosition(); }
	void setPosition(osg::Vec3d const& pos);
	void setRotation(double rotation);

	void update();

	inline void addPaddleListener(PaddleListener * paddleListener) { PaddleListeners.insert(paddleListener); }
	inline void removePaddleListener(PaddleListener * paddleListener) { PaddleListeners.erase(paddleListener); }

	inline osg::BoundingBox const& getBoundingBox() const { return Geode->getBoundingBox(); }

	void firePaddleMoved(osg::Vec3d const& prevPos, osg::Vec3d const& currPos, osg::BoundingBox const& boundingBox);

private:
	osg::ref_ptr<osg::PositionAttitudeTransform> Trans;
	osg::ref_ptr<osg::Geode> Geode;

	bool HasUpdate;
	osg::Vec3d NewPosition;

	double Rotation;

	PaddleListenerSet PaddleListeners;

};

}

#endif
