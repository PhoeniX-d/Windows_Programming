using namespace Platform;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Text;

ref class MyStoreAppx sealed : public Application
{
public:

	virtual void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ args) override;
};

int main(Array <String^>^ args)
{
	Application::Start(ref new ApplicationInitializationCallback(
		[](Windows::UI::Xaml::ApplicationInitializationCallbackParams^ params)
		{
			MyStoreAppx^ mystoreappx = ref new MyStoreAppx();
		}
	));
	return 0;
}

void MyStoreAppx::OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ args)
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
