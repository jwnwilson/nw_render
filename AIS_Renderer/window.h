#pragma once
#ifndef __RDR_WINDOW__
#define __RDR_WINDOW__


#pragma warning( disable : 4290 )


#include <stdexcept>


namespace rdr
{

	class WindowImpl;

	// This class should only be used for debugging purposes.
	// It should not be used as a substitute for your own pixel buffers.
	class window
	{
	public:
		window  ( int width, int height ) throw ( std::runtime_error, std::invalid_argument );
		~window ( );
	public:
		void  set_pixel ( int x, int y, int r, int g, int b ) throw ( std::out_of_range );
	public:
		void  close  ( );
		int   height ( ) const;
		void  open   ( );
		void  update ( );
		void  wait   ( );
		int   width  ( ) const;
	private: // prohibited methods
		window  ( const window& ) {}
		void  operator= ( const window& ) {}
	private:
		WindowImpl*  _impl;
	};

}
//end namespace rdr


#endif // end #ifdef __RDR_WINDOW__
