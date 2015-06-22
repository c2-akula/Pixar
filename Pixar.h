//
// Created by deva on 6/20/15.
//

#ifndef PIXAR_PIXAR_H
#define PIXAR_PIXAR_H

#include "Robot.h"

using namespace Roboto;

class Pixar : protected Robot
{
  public:
	Pixar();

	virtual ~Pixar();

  public:
	virtual void init() override;

	virtual Position GetPosition() override;

	virtual void SetPosition( const Position &p ) override;

	virtual void SetAngles( const Angles &t ) override;

	virtual Angles GetAngles() override;

	void apply_jnt_limits( Angles &t );
};


#endif //PIXAR_PIXAR_H
