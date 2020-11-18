#include "pch.h"
#include "MyPage.h"

MyPage::MyPage()
{
	Window::Current->CoreWindow->KeyDown += ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &MyPage::OnKeyDown);

	Grid^ grid = ref new Grid();

	tb = ref new TextBlock();
	tb->Text = "Event Handling";
	tb->FontFamily = ref new Windows::UI::Xaml::Media::FontFamily("Courier New");
	tb->FontSize = 80;
	tb->FontStyle = Windows::UI::Text::FontStyle::Normal;
	tb->FontWeight = Windows::UI::Text::FontWeights::Bold;
	tb->Foreground = ref new SolidColorBrush(Windows::UI::Colors::Gold);
	tb->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
	tb->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;

	grid->Children->Append(tb);

	Button^ button = ref new Button();
	button->Content = "Click Me..";
	button->Width = 200;
	button->Height = 100;
	button->BorderThickness = 8;
	button->BorderBrush = ref new SolidColorBrush(Colors::Red);
	button->FontFamily = ref new Media::FontFamily("Courier New");
	button->FontSize = 18;
	button->FontStyle = Text::FontStyle::Normal;
	button->FontWeight = FontWeights::Black;
	button->HorizontalAlignment = Xaml::HorizontalAlignment::Center;
	button->VerticalAlignment =Xaml:: VerticalAlignment::Bottom;
	button->Click += ref new RoutedEventHandler(this, &MyPage::OnButtonClick);

	grid->Children->Append(button);
	this->Content = grid;
}

void MyPage::OnKeyDown(CoreWindow^ sender, KeyEventArgs^ args)
{
	if (args->VirtualKey == VirtualKey::Space)
	{
		tb->Text = "Space Bar is Pressed!";
	}
	else
	{
		tb->Text = "Some Key is Pressed!";
	}
}

void MyPage::OnButtonClick(Object^ sender, RoutedEventArgs^ args)
{
	tb->Text = "Mouse is Clicked!";
}
