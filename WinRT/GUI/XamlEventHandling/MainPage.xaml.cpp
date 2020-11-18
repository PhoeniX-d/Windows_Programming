//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace XamlEventHandling;

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

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();
	Window::Current->CoreWindow->KeyDown += ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &MainPage::OnKeyDown);
}

void MainPage::OnKeyDown(CoreWindow^ sender, KeyEventArgs^ args)
{
	/*if (args->VirtualKey == VirtualKey::Space)
	{
		tb->Text = "Space Bar is Pressed!";
	}
	else
	{
		tb->Text = "Some Key is Pressed!";
	}*/
}

void MainPage::OnButtonClick(Object^ sender, RoutedEventArgs^ args)
{
	/*tb->Text = "Mouse is Clicked!";*/
}
