Name:           touchegg
Summary:        Multi-touch gesture recognizer
Url:            https://github.com/JoseExposito/touchegg
Version:        2.0.14
Release:        1
License:        GPLv3+
Group:          Applications/Productivity
Vendor:         José Expósito <jose.exposito89@gmail.com>
Packager:       José Expósito <jose.exposito89@gmail.com>

BuildRequires: git gcc gcc-c++ cmake rpm-build
BuildRequires: libudev-devel libinput-devel pugixml-devel cairo-devel
BuildRequires: libX11-devel libXtst-devel libXrandr-devel libXi-devel
BuildRequires: glib2-devel gtk3-devel

Autoreq:        1
Prefix:         %{_prefix}
Source0:        touchegg.tar.gz

%description
Touchégg is an app that runs in the background and transform the gestures you make in your touchpad into visible actions in your desktop.
For example, you can swipe up with 3 fingers to maximize a window or swipe left with 4 finger to switch to the next desktop.


%prep
%setup


%build
%cmake
%if 0%{?fedora} || 0%{?suse_version}
  %cmake_build
%else
  %make_build
%endif



%install
%if 0%{?fedora} || 0%{?suse_version}
  %cmake_install
%else
  %make_install
%endif


%check


%clean


%post

if [ "$1" -ge 1 ]; then
  systemctl daemon-reload
  systemctl reenable touchegg
  systemctl stop touchegg
  systemctl start touchegg
fi


%postun
%systemd_postun_with_restart touchegg.service


%pre


%preun
%systemd_preun touchegg.service


%files
%defattr(-,root,root,-)

%dir %{_datadir}/touchegg

%{_bindir}/touchegg
%{_datadir}/touchegg/touchegg.conf
%{_unitdir}/touchegg.service

%config %{_sysconfdir}/xdg/autostart/touchegg.desktop


%changelog

* Sat Apr 02 2022 José Expósito <jose.exposito89@gmail.com> - 2.0.14-1
- New COPR URL: https://copr.fedorainfracloud.org/coprs/joseexposito/touchegg/
- Performance improvements calculating the size of the animations
- Fix crash that might happen when multiple input devices are added and removed

* Sat Jan 08 2022 José Expósito <jose.exposito89@gmail.com> - 2.0.13-1
- Improve pinch detection when the fingers are placed horizontally or vertically
- Allow to run in multiple X displays
- Allow to configure the number of times a repeated action is executed

* Thu Oct 21 2021 José Expósito <jose.exposito89@gmail.com> - 2.0.12-1
- Improve pinch gesture detection on touchscreens
- Honor the XDG basedir specification

* Mon Jul 05 2021 José Expósito <jose.exposito89@gmail.com> - 2.0.11-1
- Allow to display any animation on SEND_KEYS/RUN_COMMAND
- Add cyclic option to CHANGE_DESKTOP
- Packages for CentOS (EPEL), Fedora and openSUSE available on COPR

* Mon Jun 07 2021 José Expósito <jose.exposito89@gmail.com> - 2.0.10-1
- Touchscreen: Use touch average to calculate deltas
- Simplify the build process in distros that don't support systemd
- libinput 1.18 support: Different deltas depending on libinput version

* Mon Apr 05 2021 José Expósito <jose.exposito89@gmail.com> - 2.0.9-1
- Use screen rotation to calculate touchscreen gestures direction

* Wed Feb 24 2021 José Expósito <jose.exposito89@gmail.com> - 2.0.8-1
- Added daily and stable PPA builds
- Fix animation when screens ot the same size are arranged vertically
- Fix crash caused by a g_variant not being referenced
- Handle the TOUCH_CANCEL event to avoid bugs
