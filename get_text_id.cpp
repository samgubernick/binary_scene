
#include "get_text_id.hpp"
#include "is_match.hpp"

namespace sam { namespace binary_data {
auto getTextId(std::string const & name) -> Id
{
	if (name == "exit") return Id::exit;
	if (name == "help") return Id::help;
	if (name == "info") return Id::info;
	if (name == "menu") return Id::menu;
	if (name == "moreInfo") return Id::moreInfo;
	if (name == "options") return Id::options;
	if (name == "pause") return Id::pause;
	if (name == "play") return Id::play;
	if (name == "balloons") return Id::balloons;
	if (name == "platform") return Id::platform;
	if (name == "shooter") return Id::shooter;
	if (name == "back") return Id::back;
	if (name == "areYouSure") return Id::areYouSure;
	if (name == "confirm") return Id::confirm;
	if (name == "custom") return Id::custom;
	if (name == "customize") return Id::customize;
	if (name == "enterName") return Id::enterName;
	if (name == "loading") return Id::loading;
	if (name == "max") return Id::max;
	if (name == "maximum") return Id::maximum;
	if (name == "min") return Id::min;
	if (name == "minimum") return Id::minimum;
	if (name == "name") return Id::name;
	if (name == "no") return Id::no;
	if (name == "off") return Id::off;
	if (name == "on") return Id::on;
	if (name == "profileName") return Id::profileName;
	if (name == "restart") return Id::restart;
	if (name == "resume") return Id::resume;
	if (name == "themeCurrent") return Id::themeCurrent;
	if (name == "yes") return Id::yes;
	if (name == "action") return Id::action;
	if (name == "audio") return Id::audio;
	if (name == "availableLanguages") return Id::availableLanguages;
	if (name == "bgm") return Id::bgm;
	if (name == "buttons") return Id::buttons;
	if (name == "controls") return Id::controls;
	if (name == "defaultx") return Id::defaultx;
	if (name == "details") return Id::details;
	if (name == "disabled") return Id::disabled;
	if (name == "drawInBackground") return Id::drawInBackground;
	if (name == "effects") return Id::effects;
	if (name == "enabled") return Id::enabled;
	if (name == "forceFeedback") return Id::forceFeedback;
	if (name == "fullscreen") return Id::fullscreen;
	if (name == "gamepad") return Id::gamepad;
	if (name == "hapticResponse") return Id::hapticResponse;
	if (name == "keyboard") return Id::keyboard;
	if (name == "mouse") return Id::mouse;
	if (name == "music") return Id::music;
	if (name == "mute") return Id::mute;
	if (name == "quality") return Id::quality;
	if (name == "resolution") return Id::resolution;
	if (name == "sfx") return Id::sfx;
	if (name == "sound") return Id::sound;
	if (name == "theme") return Id::theme;
	if (name == "video") return Id::video;
	if (name == "volume") return Id::volume;
	if (name == "window") return Id::window;
	if (name == "windowMode") return Id::windowMode;
	if (name == "color") return Id::color;
	if (name == "black") return Id::black;
	if (name == "blackAndWhite") return Id::blackAndWhite;
	if (name == "blue") return Id::blue;
	if (name == "green") return Id::green;
	if (name == "grayscale") return Id::grayscale;
	if (name == "orange") return Id::orange;
	if (name == "red") return Id::red;
	if (name == "white") return Id::white;
	if (name == "yellow") return Id::yellow;
	if (name == "language") return Id::language;
	if (name == "confirmLanguage") return Id::confirmLanguage;
	if (name == "languageSelector") return Id::languageSelector;
	if (name == "backArrow") return Id::backArrow;
	if (name == "minusSign") return Id::minusSign;
	if (name == "plusSign") return Id::plusSign;
	if (name == "checked") return Id::checked;
	if (name == "unchecked") return Id::unchecked;
	else return Id::none;
}
}}
