//
// Created by deva on 6/20/15.
//

#include <math.h>
#include "Pixar.h"

using namespace std;
using namespace Roboto;

void Pixar::init()
{
	Pixar();
}

Pixar::Pixar() : Robot( 3, 3 )
{
	m_jnt_lims[0] = make_pair( 0, 180 );
	m_jnt_lims[1] = make_pair( 0, 180 );
	m_jnt_lims[2] = make_pair( 0, 180 );

	m_links[0] = 75;
	m_links[1] = 150;
	m_links[2] = 150;

	m_pos[0] = 0;
	m_pos[1] = 0;
	m_pos[2] = 200;

	m_theta[0] = 0;
	m_theta[1] = 0;
	m_theta[2] = 0;

}

Pixar::~Pixar()
{ }

void Pixar::SetPosition( const Position &p )
{
	m_pos = p;
}

void Pixar::SetAngles( const Angles &t )
{
	m_theta = t;
}

Position Pixar::GetPosition()
{
	const auto l0 = m_links[0];
	const auto l1 = m_links[1];

	const auto th0 = m_theta[0];
	const auto th1 = m_theta[1];
	const auto th2 = m_theta[2];

	const auto c0 = Cos[th0];
	const auto c1 = Cos[th1];

	const auto s0 = Sin[th0];
	const auto s1 = Sin[th1];

//	x
	m_pos[0] = l1 * s0 * (Cos[th1 - th2] - c1);
//	y
	m_pos[1] = l1 * c0 * (Cos[th1 - th2] - c1);

//	z
	m_pos[2] = l0 + (l1 * s1) - l1 * Sin[th1 - th2];

	return m_pos;
}

Angles Pixar::GetAngles()
{
	const auto l0 = m_links[0];
	const auto l1 = m_links[1];
	const auto l2 = m_links[2];

	const auto x = m_pos[0];
	const auto y = m_pos[1];
	const auto z = m_pos[2];

	const auto hyp = sqrt((x * x) + (z * z) + (l0 * l0) - (2 * z * l0));

	m_theta[0] = (M_PI / 2 - atan2( y, x )) * Rad2Deg; // Angle about the z-axis

//	we compute the angle below the hypotenuse, bet, drawn from the base origin
//	to the end-effector at some point (x, z) in the ZX-plane.
	const auto beta = atan2( z - l0, x );

//  we then compute the angle above the hypotenuse, alp, such that (alp + bet)
//	gives us our j1 angle.
	const auto cosalp = (hyp * hyp + l1 * l1 - l2 * l2) / (2 * hyp * l1);
	const auto sinalp = sqrt( 1 - cosalp * cosalp );
	const auto alpha = atan2( sinalp, cosalp );
	m_theta[1] = (alpha + beta) * Rad2Deg; // j1 about y-axis

//  we will now use cosine and sine rule to compute the angle made by
//	j2, between l1 and l2.
	const auto cosgam = (l1 * l1 + l2 * l2 - hyp * hyp) / (2 * l1 * l2);
	const auto singam = (hyp * sinalp) / l2;

	m_theta[2] = atan2( singam, cosgam ) * Rad2Deg; // j2 about y-axis


//	we apply any joint limits we exercise
	apply_jnt_limits( m_theta );

//	then we set the member variable
	SetAngles( m_theta );

	return m_theta;
}

void Pixar::apply_jnt_limits( Angles &t )
{
	auto min = 0;
	auto max = 0;

	for ( auto i = 0; i < t.size(); ++i )
	{
		min = m_jnt_lims[i].first;
		max = m_jnt_lims[i].second;
		if ( t[i] > max )
		{
			t[i] = max;
		} else if ( t[i] < min )
		{
			t[i] = min;
		}
	}
}
