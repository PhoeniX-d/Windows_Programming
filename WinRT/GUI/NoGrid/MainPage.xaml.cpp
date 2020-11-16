//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"


using namespace NoGrid;
using namespace Windows::UI;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();
	Grid^ grid = ref new Grid();
	grid->Background = ref new SolidColorBrush(Colors::Black);
	TextBlock^ tb = ref new TextBlock();
	tb->Text = "Hello, World";
	tb->FontFamily = ref new Windows::UI::Xaml::Media::FontFamily("SeohUI");
	tb->FontSize = 120;
	tb->FontStyle = Windows::UI::Text::FontStyle::Normal;
	tb->FontWeight = Windows::UI::Text::FontWeights::Bold;
	tb->Foreground = ref new SolidColorBrush(Colors::Gold);
	tb->HorizontalAlignment = Xaml::HorizontalAlignment::Center;
	tb->VerticalAlignment = Xaml::VerticalAlignment::Center;

	grid->Children->Append(tb);
	this->Content = grid;
}
