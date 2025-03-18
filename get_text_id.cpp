
#include "get_text_id.hpp"
#include "is_match.hpp"

namespace sam::binary_data {
auto getTextId(std::string const & name) -> Id
{
	if (name == "exit") return Id::Exit;
	if (name == "help") return Id::Help;
	if (name == "info") return Id::Info;
	if (name == "menu") return Id::Menu;
	if (name == "moreInfo") return Id::MoreInfo;
	if (name == "options") return Id::Options;
	if (name == "pause") return Id::Pause;
	if (name == "play") return Id::Play;
	if (name == "themeEditor") return Id::ThemeEditor;
	if (name == "balloons") return Id::Balloons;
	if (name == "buttonsLevel") return Id::ButtonsLevel;
	if (name == "platform") return Id::Platform;
	if (name == "shooter") return Id::Shooter;
	if (name == "memory") return Id::Memory;
	if (name == "colorSwipe") return Id::ColorSwipe;
	if (name == "back") return Id::Back;
	if (name == "areYouSure") return Id::AreYouSure;
	if (name == "confirm") return Id::Confirm;
	if (name == "custom") return Id::Custom;
	if (name == "customize") return Id::Customize;
	if (name == "enterName") return Id::EnterName;
	if (name == "example") return Id::Example;
	if (name == "loading") return Id::Loading;
	if (name == "max") return Id::Max;
	if (name == "maximum") return Id::Maximum;
	if (name == "min") return Id::Min;
	if (name == "minimum") return Id::Minimum;
	if (name == "name") return Id::Name;
	if (name == "no") return Id::No;
	if (name == "off") return Id::Off;
	if (name == "on") return Id::On;
	if (name == "preview") return Id::Preview;
	if (name == "profileName") return Id::ProfileName;
	if (name == "restart") return Id::Restart;
	if (name == "resume") return Id::Resume;
	if (name == "themeCurrent") return Id::ThemeCurrent;
	if (name == "value") return Id::Value;
	if (name == "yes") return Id::Yes;
	if (name == "action") return Id::Action;
	if (name == "audio") return Id::Audio;
	if (name == "availableLanguages") return Id::AvailableLanguages;
	if (name == "bgm") return Id::Bgm;
	if (name == "button") return Id::Button;
	if (name == "buttons") return Id::Buttons;
	if (name == "calibrate") return Id::Calibrate;
	if (name == "cancelChanges") return Id::CancelChanges;
	if (name == "channel") return Id::Channel;
	if (name == "controlIndex") return Id::ControlIndex;
	if (name == "controlLocation") return Id::ControlLocation;
	if (name == "controls") return Id::Controls;
	if (name == "currentValue") return Id::CurrentValue;
	if (name == "defaultx") return Id::Defaultx;
	if (name == "details") return Id::Details;
	if (name == "deviceName") return Id::DeviceName;
	if (name == "devices") return Id::Devices;
	if (name == "disabled") return Id::Disabled;
	if (name == "doesControlHaveLights") return Id::DoesControlHaveLights;
	if (name == "doesControlLightUp") return Id::DoesControlLightUp;
	if (name == "drawInBackground") return Id::DrawInBackground;
	if (name == "edit") return Id::Edit;
	if (name == "editChannel") return Id::EditChannel;
	if (name == "editName") return Id::EditName;
	if (name == "editResolution") return Id::EditResolution;
	if (name == "effects") return Id::Effects;
	if (name == "enabled") return Id::Enabled;
	if (name == "forceFeedback") return Id::ForceFeedback;
	if (name == "fullscreen") return Id::Fullscreen;
	if (name == "gamepad") return Id::Gamepad;
	if (name == "gameplay") return Id::Gameplay;
	if (name == "hapticResponse") return Id::HapticResponse;
	if (name == "inputDevice") return Id::InputDevice;
	if (name == "keyboard") return Id::Keyboard;
	if (name == "knob") return Id::Knob;
	if (name == "maxValue") return Id::MaxValue;
	if (name == "midi") return Id::Midi;
	if (name == "midiDeviceNotConfigured") return Id::MidiDeviceNotConfigured;
	if (name == "midiDevicesNotConfigured") return Id::MidiDevicesNotConfigured;
	if (name == "minValue") return Id::MinValue;
	if (name == "mouse") return Id::Mouse;
	if (name == "music") return Id::Music;
	if (name == "mute") return Id::Mute;
	if (name == "outputDevice") return Id::OutputDevice;
	if (name == "quality") return Id::Quality;
	if (name == "requestToConfigureDevice") return Id::RequestToConfigureDevice;
	if (name == "requestToConfigureDevices") return Id::RequestToConfigureDevices;
	if (name == "reset") return Id::Reset;
	if (name == "resolution") return Id::Resolution;
	if (name == "saveChanges") return Id::SaveChanges;
	if (name == "sfx") return Id::Sfx;
	if (name == "slider") return Id::Slider;
	if (name == "sound") return Id::Sound;
	if (name == "theme") return Id::Theme;
	if (name == "useDefault") return Id::UseDefault;
	if (name == "video") return Id::Video;
	if (name == "volume") return Id::Volume;
	if (name == "window") return Id::Window;
	if (name == "windowMode") return Id::WindowMode;
	if (name == "color") return Id::Color;
	if (name == "black") return Id::Black;
	if (name == "blackAndWhite") return Id::BlackAndWhite;
	if (name == "blue") return Id::Blue;
	if (name == "green") return Id::Green;
	if (name == "grayscale") return Id::Grayscale;
	if (name == "orange") return Id::Orange;
	if (name == "red") return Id::Red;
	if (name == "white") return Id::White;
	if (name == "yellow") return Id::Yellow;
	if (name == "language") return Id::Language;
	if (name == "confirmLanguage") return Id::ConfirmLanguage;
	if (name == "languageSelector") return Id::LanguageSelector;
	if (name == "backArrow") return Id::BackArrow;
	if (name == "forwardArrow") return Id::ForwardArrow;
	if (name == "minusSign") return Id::MinusSign;
	if (name == "plusSign") return Id::PlusSign;
	if (name == "checked") return Id::Checked;
	if (name == "unchecked") return Id::Unchecked;
	if (name == "background") return Id::Background;
	if (name == "onBackground") return Id::OnBackground;
	if (name == "onBackgroundAccent") return Id::OnBackgroundAccent;
	if (name == "onPrimary") return Id::OnPrimary;
	if (name == "onPrimaryAccent") return Id::OnPrimaryAccent;
	if (name == "onSecondary") return Id::OnSecondary;
	if (name == "onSecondaryAccent") return Id::OnSecondaryAccent;
	if (name == "onSurface") return Id::OnSurface;
	if (name == "onSurfaceAccent") return Id::OnSurfaceAccent;
	if (name == "primary") return Id::Primary;
	if (name == "primaryVariant") return Id::PrimaryVariant;
	if (name == "secondary") return Id::Secondary;
	if (name == "secondaryVariant") return Id::SecondaryVariant;
	if (name == "surface") return Id::Surface;
	if (name == "currentColor") return Id::CurrentColor;
	if (name == "newColor") return Id::NewColor;
	if (name == "selectColor") return Id::SelectColor;
	else return Id::None;
}
}
