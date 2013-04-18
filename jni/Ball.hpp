#ifndef __BALL_HPP__
#define __BALL_HPP__

#include "Paddle.hpp"
#include "PaddleListener.hpp"

#include <osg/Geode>
#include <osg/PositionAttitudeTransform>

namespace test
{

enum GameState
{
	SERVE_P1=100,
	PLAY_P1,
	SERVE_P2=200,
	PLAY_P2
};

class Ball : public osg::PositionAttitudeTransform, public PaddleListener
{
public:
	Ball();

	inline void setVelocity(osg::Vec3d const& velocity) { Velocity = velocity; }

	void setPaddle1(test::Paddle * paddle1);
	void setPaddle2(test::Paddle * paddle2);

	inline void setState(GameState state) { State = state; }

	virtual void accept(osg::NodeVisitor & visitor);

	virtual void paddleMoved(Paddle * paddle, osg::Vec3d const& prevPos, osg::Vec3d const& currPos, osg::BoundingBox const& boundingBox);

protected:
	void update();

	Paddle * getActivePaddle() const;

private:
	osg::Vec3d Velocity;

	osg::ref_ptr<test::Paddle> Paddle1;
	osg::ref_ptr<test::Paddle> Paddle2;

	GameState State;

};

}

#endif
