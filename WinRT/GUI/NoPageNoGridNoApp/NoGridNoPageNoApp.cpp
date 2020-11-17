#include "pch.h"
#include "NoGridNoPageNoApp.h"

void MyCallbackMethod(Windows::UI::Xaml::ApplicationInitializationCallbackParams^ params)
{
	App^ app = ref new App();
}

int main(Array <String^>^ args)
{
	ApplicationInitializationCallback^ callback = ref new ApplicationInitializationCallback(MyCallbackMethod);
	Application::Start(callback);
	return 0;
}

void App::OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ args)
{
	TextBlock^ tb = ref new TextBlock();
	tb->Text = "Hello, World!!";
	tb->FontFamily = ref new Windows::UI::Xaml::Media::FontFamily("SeohUI");
	tb->FontSize = 120;
	tb->FontStyle = Windows::UI::Text::FontStyle::Normal;
	tb->FontWeight = Windows::UI::Text::FontWeights::Bold;
	tb->Foreground = ref new SolidColorBrush(Windows::UI::Colors::ForestGreen);
	tb->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
	tb->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;

	Window::Current->Content = tb;
	Window::Current->Activate();
}
