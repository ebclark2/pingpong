#ifndef __BALL_HPP__
#define __BALL_HPP__

#include "Paddle.hpp"
#include "PaddleListener.hpp"

#include <osg/Geode>
#include <osg/PositionAttitudeTransform>

#include <OpenThreads/Mutex>
#include <OpenThreads/ScopedLock>

#include <list>

namespace test
{

enum GameState
{
	SERVE_P1=100,
	PLAY_P1,
	SERVE_P2=200,
	PLAY_P2
};

class Ball : public osg::Group, public PaddleListener
{
private:
	typedef OpenThreads::Mutex Mutex;
	typedef OpenThreads::ScopedPointerLock<Mutex> ScopedLock;

	struct PaddleMovementData
	{
		Paddle * paddle;
		osg::Vec3d prevPos;
		osg::Vec3d const& currPos;

		PaddleMovementData(Paddle * paddle_, osg::Vec3d const& prevPos_, osg::Vec3d const& currPos_) :
			paddle(paddle_),
			prevPos(prevPos_),
			currPos(currPos_)
		{ }
	};

public:
	Ball();

	void setPaddle1(test::Paddle * paddle1);
	void setPaddle2(test::Paddle * paddle2);

	inline void setState(GameState state) { State = state; }

	virtual void accept(osg::NodeVisitor & visitor);

	virtual void paddleMoved(Paddle * paddle, osg::Vec3d const& prevPos, osg::Vec3d const& currPos);

	inline osg::Vec3d getPosition() const { return Trans->getPosition(); }

protected:
	void update();
	void handlePaddleMoved(Paddle * paddle, osg::Vec3d const& prevPos, osg::Vec3d const& currPos);

	void setVelocity(osg::Vec3d const& velocity);
	void setPosition(osg::Vec3d const& position);

	Paddle * getActivePaddle() const;

private:
	osg::Vec3d Velocity;
	osg::Vec3d VelocityNormal;

	osg::ref_ptr<test::Paddle> Paddle1;
	osg::ref_ptr<test::Paddle> Paddle2;

	osg::ref_ptr<osg::PositionAttitudeTransform> Trans;
	osg::Vec3d PreviousPosition;

	GameState State;
	std::list<PaddleMovementData> PaddleMovements;

	mutable Mutex Mtx;
};

}

#endif
