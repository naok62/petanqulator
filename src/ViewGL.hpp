
#ifndef _VIEWGL_HPP_
#define _VIEWGL_HPP_

#include "Chrono.hpp"

#include <gtkmm.h>
#include <gtkglmm.h>

class Controller;
class View;

class ViewGL : public Gtk::GL::DrawingArea 
{
    private:
        Controller & _refController;
        View & _refView;

        Glib::RefPtr< Gdk::Window > _window;
        Glib::RefPtr< Gdk::GL::Config > _glconfig;
        Glib::RefPtr< Gdk::GL::Context > _glcontext;
        Glib::RefPtr< Gdk::GL::Window > _glwindow;

        float _theta;
        float _thetaRef;
        float _phi;
        float _phiRef;
        bool _motionThetaPhi;

    public:
        ViewGL(Controller & refController, View & refView, 
                int & argc, char** argv);

        void init();
        void update();

        void startAnimation();
        void stopAnimation();

    private:
        // override signal handlers
        bool on_expose_event(GdkEventExpose * event);
        bool on_configure_event(GdkEventConfigure * event);
        bool on_button_press_event(GdkEventButton* event);
        bool on_button_release_event(GdkEventButton* event);
        bool on_motion_notify_event(GdkEventMotion * event);

        // new handlers
        Chrono _chrono;
        sigc::connection _timeoutConnection;
        bool handleTimeout();

        void setGlColor(GLenum type, std::array<float,4> colorv);
};

#endif

