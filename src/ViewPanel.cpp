
#include "Controller.hpp"
#include "View.hpp"
#include "ViewPanel.hpp"
#include "Utils.hpp"

#include <set>
#include <sstream>

ViewPanel::ViewPanel(Controller & refController, View & refView) :
    _refController(refController),
    _refView(refView),
    _newButton("new"),
    _quitButton("quit"),
    _throwBallButton("   throw ball   ")
{
	pack_start(_newButton, Gtk::PACK_SHRINK);
	_newButton.signal_clicked().connect(
            sigc::mem_fun(*this, &ViewPanel::handleNew));

	pack_start(_quitButton, Gtk::PACK_SHRINK);
	_quitButton.signal_clicked().connect(
            sigc::mem_fun(_refView, &View::quit));

    packLabel("\n pitch:");
    _pitchSpin.set_range(-180, 180);
    _pitchSpin.set_increments(1, 5);
    _pitchSpin.set_value(45);
    pack_start(_pitchSpin, Gtk::PACK_SHRINK);
	_pitchSpin.signal_changed().connect(sigc::mem_fun(_refView, &View::update));
    packLabel(" yaw:");
    _yawSpin.set_range(-180, 180);
    _yawSpin.set_increments(1, 5);
    pack_start(_yawSpin, Gtk::PACK_SHRINK);
	_yawSpin.signal_changed().connect(sigc::mem_fun(_refView, &View::update));
    packLabel(" velocity:");
    _velocitySpin.set_digits(1);
    _velocitySpin.set_range(0, 10);
    _velocitySpin.set_increments(0.1, 5);
    _velocitySpin.set_value(5);
    pack_start(_velocitySpin, Gtk::PACK_SHRINK);

    pack_start(_throwBallButton, Gtk::PACK_SHRINK);
	_throwBallButton.signal_clicked().connect(
            sigc::mem_fun(*this, &ViewPanel::handleThrowBall));

    pack_start(_infoLabel, Gtk::PACK_SHRINK);
}

void ViewPanel::startAnimation()
{
    _throwBallButton.set_sensitive(false);
}

void ViewPanel::stopAnimation()
{
    _throwBallButton.set_sensitive(true);
    std::stringstream ss;
    ss << "\n remaining red  = " << _refController.getRemainingBallsRed();
    ss << "\n remaining blue = " << _refController.getRemainingBallsBlue();
    _infoLabel.set_label(ss.str());
}

void ViewPanel::handleNew()
{
    _refController.newGame();
    // TODO print jack position
    UTILS_INFO("new game");
}

void ViewPanel::handleThrowBall()
{
    // get velocity vector from the interface
    double radPitch = degToRad(getPitch());
    double radYaw = degToRad(getYaw());
    double velocity = getVelocity();
    double vx = velocity * cos(radPitch) * cos(radYaw);
    double vy = velocity * sin(radPitch);
    double vz = velocity * cos(radPitch) * sin(radYaw);

    // output log
    std::stringstream ss;
    ss << "throw ball, velocity=[" << vx << ' ' << vy << ' ' << vz << ']';
    UTILS_INFO(ss.str());

    // throw ball
    _refController.startThrow(vx, vy, vz);
}

void ViewPanel::packLabel(const char * str)
{
    Gtk::Label * ptrLabel = Gtk::manage(new Gtk::Label(str));
    ptrLabel->set_alignment(Gtk::ALIGN_START);
    pack_start(*ptrLabel, Gtk::PACK_SHRINK);
}

double ViewPanel::getPitch() const
{
    return _pitchSpin.get_value();
}

double ViewPanel::getYaw() const
{
    return _yawSpin.get_value();
}

double ViewPanel::getVelocity() const
{
    return _velocitySpin.get_value();
}

