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

ref class MyPage sealed : public Page
{
private:

	TextBlock^ tb;

public:

	MyPage();
	void OnKeyDown(CoreWindow^ sender, KeyEventArgs^ args);
	void OnButtonClick(Object^ sender, RoutedEventArgs^ args);
};
