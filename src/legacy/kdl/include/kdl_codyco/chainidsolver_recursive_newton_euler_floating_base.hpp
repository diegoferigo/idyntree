// Copyright  (C)  2009  Ruben Smits <ruben dot smits at mech dot kuleuven dot be>

// Version: 1.0
// Author: Ruben Smits <ruben dot smits at mech dot kuleuven dot be>
// Maintainer: Ruben Smits <ruben dot smits at mech dot kuleuven dot be>
// URL: http://www.orocos.org/kdl

// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#ifndef KDL_CHAIN_IDSOLVER_RECURSIVE_NEWTON_EULER_FLOATING_BASE_HPP
#define KDL_CHAIN_IDSOLVER_RECURSIVE_NEWTON_EULER_FLOATING_BASE_HPP

#ifdef __DEPRECATED
#warning <chainidsolver_recursive_newton_euler_floating_base.hpp> is deprecated.
#endif

#include <kdl_codyco/chainidsolver_floating_base.hpp>

namespace KDL{
    /**
     * \brief Recursive newton euler inverse dynamics solver
     *
     * The algorithm implementation is based on the book "Rigid Body
     * Dynamics Algorithms" of Roy Featherstone, 2008
     * (ISBN:978-0-387-74314-1) See page 96 for the pseudo-code.
     *
     * It calculates the torques for the joints, given the motion of
     * the joints (q,qdot,qdotdot), external forces on the segments
     * (expressed in the segments reference frame) and the dynamical
     * parameters of the segments.
     */
    class ChainIdSolver_RNE_FB : public ChainIdSolver_FB{
    public:
        /**
         * Constructor for the solver, it will allocate all the necessary memory
         * \param chain The kinematic chain to calculate the inverse dynamics for, an internal copy will be made.
         * \param grav The gravity vector to use during the calculation (not used by the floating base solver).
         */
        ChainIdSolver_RNE_FB(const Chain& chain,Vector grav=Vector::Zero());



        ~ChainIdSolver_RNE_FB(){};

        /**
         * Function to calculate from Cartesian forces to joint torques,
         * for a fixed base.
         * Input parameters;
         * \param q The current joint positions
         * \param q_dot The current joint velocities
         * \param q_dotdot The current joint accelerations
         * \param f_ext The external forces (no gravity) on the segments
         * Output parameters:
         * \param torques the resulting torques for the joints
         */
        int CartToJnt(const KDL::JntArray &q, const KDL::JntArray &q_dot, const KDL::JntArray &q_dotdot, const Wrenches& f_ext,JntArray &torques);

        /**
             * Calculate floating base inverse dynamics, from joint positions, velocity, acceleration,
             * base velocity, base acceleration, external forces
             * to joint torques/forces.
             *
             * @param q input joint positions
             * @param q_dot input joint velocities
             * @param q_dotdot input joint accelerations
             * @param base_velocity velocity of the floating base
             *        (the linear part has no influence on the dynamics)
             * @param base_acceleration acceleration of the floating base
             *        (proper acceleration, considering also gravitational acceleration)
             * @param f_ext external forces
             *
             * @param torque output joint torques
             * @param base_wrench output base wrench
             *
             * @return if < 0 something went wrong
             */
        int CartToJnt(const KDL::JntArray &q, const KDL::JntArray &q_dot, const KDL::JntArray &q_dotdot, const Twist& base_velocity, const Twist& base_acceleration, const Wrenches& f_ext,JntArray &torques, Wrench& base_force);


    private:
        Chain chain;
        unsigned int nj;
        unsigned int ns;
        std::vector<Frame> X;
        std::vector<Twist> S;
        std::vector<Twist> v;
        std::vector<Twist> a;
        std::vector<Wrench> f;
        Twist ag;

    };
}

#endif
