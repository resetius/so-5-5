/*
 * SObjectizer-5
 */

/*!
 * \file
 * \brief Helper template function for doing initialization phase with
 * rollback on failure.
 *
 * \since
 * v.5.5.19
 */

#pragma once

#include <so_5/h/exception.hpp>

namespace so_5 {

namespace impl {

/*!
 * \brief Helper template function for doing initialization phase with
 * rollback on failure.
 *
 * \since
 * v.5.5.19
 */
template< typename INIT_FN, typename DEINIT_FN, typename NEXT_STAGE >
void
run_stage(
	const std::string & stage_name,
	INIT_FN && init_fn,
	DEINIT_FN && deinit_fn,
	NEXT_STAGE && next_stage )
{
	try
	{
		init_fn();
	}
	catch( const std::exception & x )
	{
		SO_5_THROW_EXCEPTION(
				rc_unexpected_error,
				stage_name + ": initialization failed, exception is: '" +
				x.what() + "'" );
	}

	try
	{
		next_stage();
	}
	catch( const std::exception & x )
	{
		try
		{
			deinit_fn();
		}
		catch( const std::exception & nested )
		{
			SO_5_THROW_EXCEPTION(
					rc_unexpected_error,
					stage_name + ": deinitialization failed during "
					"exception handling. Original exception is: '" + x.what() +
					"', deinitialization exception is: '" + nested.what() + "'" );
		}

		throw;
	}

	try
	{
		deinit_fn();
	}
	catch( const std::exception & x )
	{
		SO_5_THROW_EXCEPTION(
				rc_unexpected_error,
				stage_name + ": deinitialization failed, exception is: '" +
				x.what() + "'" );
	}
}

} /* namespace impl */

} /* namespace so_5 */

