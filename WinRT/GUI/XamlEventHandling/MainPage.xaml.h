//
// MainPage.xaml.h
// Declaration of the MainPage class.
//
#include "MainPage.g.h"
#pragma once
using namespace Platform;			/*for Object */
using namespace Windows::UI;		/* for Colors */
using namespace Windows::UI::Text;	/* for FontStyle */
using namespace Windows::UI::Xaml;	 /*for Alignments */
using namespace Windows::System;	/* for VirtualKey */
using namespace Windows::UI::Xaml::Controls;	/* for Page, Grid */
using namespace Windows::UI::Core;				 /* for CoreWindow and KeyEvenArgs */
using namespace Windows::Foundation;			/* for TypedEventHandler*/
using namespace Windows::UI::Xaml::Media; /* for SolidColorBrush*/


namespace XamlEventHandling
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();
		void OnKeyDown(CoreWindow^ sender, KeyEventArgs^ args);
		void OnButtonClick(Object^ sender, RoutedEventArgs^ args);
	};
}
