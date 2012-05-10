/*    Copyright (c) 2010-2012 Delft University of Technology.
 *
 *    This software is protected by national and international copyright.
 *    Any unauthorized use, reproduction or modification is unlawful and
 *    will be prosecuted. Commercial and non-private application of the
 *    software in any form is strictly prohibited unless otherwise granted
 *    by the authors.
 *
 *    The code is provided without any warranty; without even the implied
 *    warranty of merchantibility or fitness for a particular purpose.
 *
 *    Changelog
 *      YYMMDD    Author            Comment
 *      110131    K. Kumar          First creation of code.
 *      110204    K. Kumar          Removed positionVector_, velocityVector_.
 *
 *    References
 *
 */

#ifndef TUDAT_CARTESIAN_POSITION_ELEMENTS_H
#define TUDAT_CARTESIAN_POSITION_ELEMENTS_H

#include <iostream>

#include "Tudat/Astrodynamics/States/state.h"

namespace tudat
{
namespace astrodynamics
{
namespace states
{

//! Cartesian position elements class.
/*!
 * This class contains the Cartesian position elements.
 */
class CartesianPositionElements : public State
{
public:

    //! Default constructor.
    /*!
     * Default constructor.
     */
    CartesianPositionElements( ) { state.setZero( 3 ); }

    //! Set Cartesian element: x.
    /*!
     * Sets the Cartesian element: x.
     * \param cartesianElementX Cartesian element: x.
     */
    void setCartesianElementX( const double cartesianElementX ) { state( 0 ) = cartesianElementX; }

    //! Set Cartesian element: y.
    /*!
     * Sets the Cartesian element: y.
     * \param cartesianElementY Cartesian element: y.
     */
    void setCartesianElementY( const double cartesianElementY ) { state( 1 ) = cartesianElementY; }

    //! Set Cartesian element: z.
    /*!
     * Sets the Cartesian element: z.
     * \param cartesianElementZ Cartesian element: z.
     */
    void setCartesianElementZ( const double cartesianElementZ ) { state( 2 ) = cartesianElementZ; }

    //! Get Cartesian element: x.
    /*!
     * Returns the Cartesian element: x.
     * \return Cartesian element: x.
     */
    double getCartesianElementX( ) { return state( 0 ); }

    //! Get Cartesian element: y.
    /*!
     * Returns the Cartesian element: y.
     * \return Cartesian element: y.
     */
    double getCartesianElementY( ) { return state( 1 ); }

    //! Get Cartesian element: z.
    /*!
     * Returns the Cartesian element: z.
     * \return Cartesian element: z.
     */
    double getCartesianElementZ( ) { return state( 2 ); }

    //! Overload ostream to print class information.
    /*!
     * Overloads ostream to print class information.
     * \param stream Stream object.
     * \param cartesianPositionElements CartesianPositionElements object.
     * \return Stream object.
     */
    friend std::ostream& operator<<( std::ostream& stream,
                                     CartesianPositionElements& cartesianPositionElements )
    {
        stream << "The state is set to: " << cartesianPositionElements.state << std::endl;
        return stream;
    }

protected:

private:
};

} // namespace states
} // namespace astrodynamics
} // namespace tudat

#endif // TUDAT_CARTESIAN_POSITION_ELEMENTS_H