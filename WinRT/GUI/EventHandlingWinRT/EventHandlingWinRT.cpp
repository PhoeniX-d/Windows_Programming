#include "pch.h"
#include "EventHandlingWinRT.h"
#include "MyPage.h"

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
	MyPage^ mypage = ref new MyPage();
	Window::Current->Content = mypage;
	Window::Current->Activate();
}
