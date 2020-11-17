//
// App.xaml.cpp
// Implementation of the App class.
//

#include "pch.h"

using namespace NoGridNoPage;
using namespace Platform;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

/// <summary>
/// Initializes the singleton application object.  This is the first line of authored code
/// executed, and as such is the logical equivalent of main() or WinMain().
/// </summary>
App::App()
{
    InitializeComponent();
    Suspending += ref new SuspendingEventHandler(this, &App::OnSuspending);
}

/// <summary>
/// Invoked when the application is launched normally by the end user.  Other entry points
/// will be used such as when the application is launched to open a specific file.
/// </summary>
/// <param name="e">Details about the launch request and process.</param>
void App::OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ e)
{
    Page^ page = ref new Page();
    Grid^ grid = ref new Grid();
    grid->Background = ref new SolidColorBrush(Windows::UI::Colors::Black);
    
    TextBlock^ tb = ref new TextBlock();
    tb->Text = "Hello, World!!!";
    tb->FontFamily = ref new Windows::UI::Xaml::Media::FontFamily("SeohUI");
    tb->FontSize = 120;
    tb->FontStyle = Windows::UI::Text::FontStyle::Oblique;
    tb->FontWeight = Windows::UI::Text::FontWeights::Bold;
    tb->Foreground = ref new SolidColorBrush(Windows::UI::Colors::LemonChiffon);
    tb->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
    tb->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;

    grid->Children->Append(tb);
    page->Content = grid;

    Window::Current->Content = page;
    Window::Current->Activate();
}

/// <summary>
/// Invoked when application execution is being suspended.  Application state is saved
/// without knowing whether the application will be terminated or resumed with the contents
/// of memory still intact.
/// </summary>
/// <param name="sender">The source of the suspend request.</param>
/// <param name="e">Details about the suspend request.</param>
void App::OnSuspending(Object^ sender, SuspendingEventArgs^ e)
{
    (void) sender;  // Unused parameter
    (void) e;   // Unused parameter

    //TODO: Save application state and stop any background activity
}

/// <summary>
/// Invoked when Navigation to a certain page fails
/// </summary>
/// <param name="sender">The Frame which failed navigation</param>
/// <param name="e">Details about the navigation failure</param>
void App::OnNavigationFailed(Platform::Object ^sender, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs ^e)
{
    throw ref new FailureException("Failed to load Page " + e->SourcePageType.Name);
}
