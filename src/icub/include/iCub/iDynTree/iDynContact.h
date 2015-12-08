/*
 * Copyright (C) 2015 RobotCub Consortium
 * Author: Nuno Guedelha
 * CopyPolicy: Released under the terms of the GNU GPL v2.0.
 *
 */

/**
 * Class representing a contact on the tactile sensor system (skin) of iCub.
 *
 * \section intro_sec Description
 *
 * \section tested_os_sec Tested OS
 *
 * Linux
 *
 * \author Nuno Guedelha
 *
 * Copyright (C) 2015 RobotCub Consortium
 * CopyPolicy: Released under the terms of the GNU GPL v2.0.
 *
 *
 **/

#ifndef __IDYNCONTACTS_H__
#define __IDYNCONTACTS_H__

#include <iDynTree/Core/Position.h>
#include <iDynTree/Core/Wrench.h>

namespace iDynTree
{
    /**
     * Class representing an external contact acting on a link of the robot body, as dynContact from
     * icub namespace.
     * This class attributes match those of dynContact but based on skinDynLib::iDynTree structures.
     * A contact is identified by a unique id, a link index, a frame index, the center of
     * pressure (CoP), the contact force and moment.
     * All the vectors (i.e. CoP, force, moment) are expressed w.r.t. the reference frame of the link.
     *
     * This class is used in the process of estimating the contact wrenches. It is filled with data
     * parsed from skinDynLib::dynContact.
     * In the estimation process the link number and the contact position are supposed to be known.
     * The force direction and the moment may be either known or unknown, depending on the sensor
     * data.
     */
    class iDynContact
    {
    protected:
        // unique id of the contact, copied from dynContact.
        unsigned long contactId;
        /// number of the link where the contact is applied
        unsigned int linkIndex;
        /// number of the frame where the contact is applied
        unsigned int frameIndex;
        /// 3-dim center of pressure of the contact expressed w.r.t. the reference frame of the link
        Position CoP;
        ///contact force direction (3-dim unit vector)
        Force Fdir;
        /// contact force module
        double Fmodule;
        ///contact force (3-dim vector)
        Force F;
        /// contact moment (3-dim vector)
        Moment Mu;
        /// contact wrench resulting from contact force/moment
        Wrench spatialF;

        /// True if the moment applied at the contact point is known
        bool muKnown;
        /// True if the direction of the force applied at the contact point is known
        bool fDirKnown;


    public:
        //~~~~~~~~~~~~~~~~~~~~~~
        //   CONSTRUCTORS
        //~~~~~~~~~~~~~~~~~~~~~~
        /**
         * Default constructor
         */
        iDynContact();
        /**
         * Constructor with moment and force direction. If these are unknown, default value is NULL.
         * @param _bodyPart the body part associated to this contact
         * @param _linkNumber the number of the link on which this contact is applied
         * @param _CoP the 3-dim center of pressure of this contact in link reference frame
         * @param _Mu the moment applied at this contact, expressed in link reference frame
         * @param _Fdir the direction of the contact force, expressed in link reference frame
         */
        iDynContact(const unsigned long _contactId, const unsigned int _linkIndex,
                    unsigned int _frameIndex, const Position & _CoP,
                    const Force & _Fdir, const Moment & _Mu);

#if 0
        /**
         * Constructor from a dynContact object.
         * @param otherDynContact
         */
        iDynContact(const dynContact & otherDynContact);
        //~~~~~~~~~~~~~~~~~~~~~~
        //   GET methods
        //~~~~~~~~~~~~~~~~~~~~~~
        /**
         * Get the contact force and moment in a single (6x1) vector
         * @return a 6x1 vector as a spatial force class Wrench
         */
        virtual const  Wrench & getWrench() const;
        /**
         * Get the contact force.
         * @return a 3-dim vector
         */
        virtual const  Force & getForce() const;
        /**
         * Get the contact force direction.
         * @return a 3-dim vector with norm equal to one
         */
        virtual const  Force & getForceDirection() const;
        /**
         * Get the contact force module.
         * @return the intensity of the contact force
         */
        virtual double getForceModule() const;
        /**
         * Get the contact moment.
         * @return a 3-dim vector
         */
        virtual const  Moment & getMoment() const;
        /**
         * Get the contact center of pressure expressed in the link reference frame.
         * @return a 3-dim vector
         */
        virtual const  Position & getCoP() const;
        /**
         * Get the link index where the contact is applied (where 0 is the first link of the chain).
         * @return the contact link index
         */
        virtual unsigned int  getLinkIndex() const;
        /**
         * Get the frame index where the contact is applied
         * @return the contact frame index
         */
        virtual unsigned int  getFrameIndex() const;
        /**
         * Get the id of this contact.
         * @return the contact id
         */
        virtual unsigned long getId() const;

        //~~~~~~~~~~~~~~~~~~~~~~
        //   IS methods
        //~~~~~~~~~~~~~~~~~~~~~~
        /**
         * Get true if the moment applied at this contact is known a-priori.
         * @return true if the moment is known, false otherwise.
         */
        virtual bool isMomentKnown() const;
        /**
         * Get true if the direction of the force applied at this contact is known a-priori.
         * @return true if the force direction is known, false otherwise.
         */
        virtual bool isForceDirectionKnown() const;

        //~~~~~~~~~~~~~~~~~~~~~~
        //   SET methods
        //~~~~~~~~~~~~~~~~~~~~~~
        /**
         * Set the direction of the contact force
         * @param _Fdir a 3-dim vector containing the direction of the contact force
         * @return true if the operation succeeded, false otherwise
         * @note If norm(_Fdir) is not 1 then _Fdir is normalized so that its norm is 1
         */
        virtual bool setForceDirection(const Force & _Fdir);
        /**
         * Set the contact force module
         * @param _Fmodule the module of the contact force
         * @return true if the operation succeeded, false otherwise
         */
        virtual bool setForceModule(double _Fmodule);
        /**
         * Set the contact force
         * @param _F a 3-dim vector containing the contact force
         * @return true if the operation succeeded, false otherwise
         */
        virtual bool setForce(const Force & _F);
        /**
         * Set the contact moment
         * @param _Mu a 3-dim vector containing the contact moment
         * @return true if the operation succeeded, false otherwise
         */
        virtual bool setMoment(const Moment & _Mu);
        /**
         * Set the contact force and moment
         * @param _F a 3-dim vector containing the contact force
         * @param _Mu a 3-dim vector containing the contact moment
         * @return true if the operation succeeded, false otherwise
         */
        virtual bool setWrench(const Force & _F, const Moment & _Mu);
        /**
         * Set the contact force and moment as a single (6x1) vector
         * @param _FMu a 6x1 vector where 0:2=force 3:5=moment
         * @return true if the operation succeeded, false otherwise
         */
        virtual bool setWrench(const Wrench & _spatialF);
        /**
         * Set the contact center of pressure in link reference frame
         * @param _CoP a 3x1 vector
         * @return true if the operation succeeded, false otherwise
         */
        virtual bool setCoP(const Position &_CoP);
        /**
         * Set the contact link number (0 is the first link)
         * @param _linkNum the link number
         * @return true if the operation succeeded, false otherwise
         */
        virtual void setLinkIndex(unsigned int _linkIndex);
        /**
         * Set the body part of this contact
         * @param _bodyPart the contact body part
         * @return true if the operation succeeded, false otherwise
         */
        virtual void setFrameIndex(BodyPart _frameIndex);

        //~~~~~~~~~~~~~~~~~~~~~~
        //   FIX/UNFIX methods
        //~~~~~~~~~~~~~~~~~~~~~~
        /**
         * Fix the direction of the contact force. Differently from the method
         * setForceDirection, this method also sets the flag 'fDirKnown'
         * to true, so when estimating the contact wrenches the solver considers the
         * force direction of this contact as known a-priori.
         * @param _Fdir the contact force direction
         * @return true iff operation succeeded, false otherwise
         */
        virtual bool fixForceDirection(const yarp::sig::Vector &_Fdir);
        /**
         * Equivalent to calling fixMoment(zeros(3)).
         */
        virtual bool fixMoment();
        /**
         * Fix the contact moment. Differently from the method
         * setMoment, this method also sets the flag 'muKnown'
         * to true, so when estimating the contact wrenches the solver considers the
         * moment of this contact as known a-priori.
         * @param _Mu the contact moment
         * @return true iff operation succeeded, false otherwise
         */
        virtual bool fixMoment(const yarp::sig::Vector &_Mu);
        /**
         * Set the flag fDirKnown to false so that when estimating the contact wrenches
         * the solver estimates also the force direction and does not consider it as known
         * a-priori.
         */
        virtual void unfixForceDirection();
        /**
         * Set the flag muKnown to false so that when estimating the contact wrenches
         * the solver estimates also the contact moment and does not consider it as known
         * a-priori.
         */
        virtual void unfixMoment();

        //~~~~~~~~~~~~~~~~~~~~~~
        //   SERIALIZATION methods
        //~~~~~~~~~~~~~~~~~~~~~~
        /*
         * Read iDynContact from a connection. It expects a list of 4 elements, that are:
         * - a list of 3 int, containing contactId, bodyPart and linkNumber
         * - a list of 3 double, containing the CoP
         * - a list of 3 double, containing the force
         * - a list of 3 double, containing the moment
         * @param connection the connection to read from
         * @return true iff a iDynContact was read correctly
         */
        virtual bool read(yarp::os::ConnectionReader& connection);
        /**
         * Write iDynContact to a connection as a list of 4 elements, that are:
         * - a list of 3 int, containing contactId, bodyPart, linkNumber
         * - a list of 3 double, containing the CoP
         * - a list of 3 double, containing the force
         * - a list of 3 double, containing the moment
         * @param connection the connection to write to
         * @return true iff the iDynContact was written correctly
         */
        virtual bool write(yarp::os::ConnectionWriter& connection);


        /**
         * Convert this contact into a string. Useful to print some information.
         * @param precision number of decimal digits to use in the string representation
         * @return a string representation of this contact in this format:
         * "Contact id: "<< contactId<< "Link index: "<< linkIndex << ", Frame index: "<< frameIndex <<
         * ", CoP: "<< CoP<< ", spatial Force: "<< spatialF
         */
        virtual std::string toString(int precision=-1) const;
        /**
         * Set the verbosity level of comments during operations
         * @param verb level of verbosity
         */
        virtual void setVerbose(unsigned int verb = VERBOSE);
#endif
    };

}
#endif


